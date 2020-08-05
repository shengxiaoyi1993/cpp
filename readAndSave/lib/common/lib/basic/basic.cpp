#include "basic.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <dirent.h>
#include<fcntl.h>
#include<string.h>
#include<sys/stat.h>
#include <unistd.h>

using namespace std;



int close_all_fd(int ppid)
{
    DIR *dir;
    struct dirent *entry, _entry;
    int retval, rewind, fd;
    string ppfd="/proc/" +integerToString(ppid)+ "/fd";

    dir = opendir(ppfd.c_str());
    if (dir == NULL)
        return -1;

    rewind = 0;
    while (1) {
        retval = readdir_r(dir, &_entry, &entry);
        if (retval != 0) {
            errno = -retval;
            retval = -1;
            break;
        }
        if (entry == NULL) {
            if (!rewind)
                break;
            rewinddir(dir);
            rewind = 0;
            continue;
        }
        if (entry->d_name[0] == '.')
            continue;

        //遍历的时候分析下描述符对应的软连接是不是指向一个socket，以免错杀无辜的描述符

        {
            char link_name[1024] = {0};
            int ret_link = 0;
            ret_link = readlink(entry->d_name,link_name ,1024);
            if((ret_link == 0) && (strcmp(link_name,"socket:") == 0))
            {
                continue;
            }
        }
        fd = atoi(entry->d_name);
        if (dirfd(dir) == fd)
            continue;
      //  if (fd < 3) /***jump root dev**/
      //      continue;
        retval = close(fd);
        if (retval != 0)
            break;
        rewind = 1;
    }

    closedir(dir);

    return retval;
}



void saveFile(char* content,std::string file_dst) {

    FILE *fp = NULL;
    fp = fopen(file_dst.c_str(),"w");
    if(fp!=NULL){
        fprintf(fp,content);
        fclose(fp);
    }

    return ;
}

std::string integerToString(int num){
    stringstream ss;
    ss.clear();
    ss.str("");
    string tmps;
    ss<<num;
    ss>>tmps;
    return tmps;
}


int getStringFromFile(std::string dirpath,char** content){
    int v_size;
    return getStringFromFile(dirpath,content,v_size);
    // 输出到标准输出

}


int getStringFromFile(std::string dirpath,char** content,int & v_size){
    filebuf *pbuf;
    ifstream filestr;

    // 要读入整个文件，必须采用二进制打开
    filestr.open (dirpath.c_str(), ios::binary);
    // 获取filestr对应buffer对象的指针
    pbuf=filestr.rdbuf();

    // 调用buffer对象方法获取文件大小
    v_size=pbuf->pubseekoff (0,ios::end,ios::in);
    pbuf->pubseekpos (0,ios::in);
    if(v_size<=0){
        return -1;
    }

    // 分配内存空间
    *content=new char[v_size];
    // 获取文件内容
    pbuf->sgetn (*content,v_size);

    filestr.close();
    return 0;

    // 输出到标准输出
}
