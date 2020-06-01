#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include <dirent.h>
#include <sstream>
#include <string>

using namespace std;

std::string integerToString(int num){
    stringstream ss;
    ss.clear();
    ss.str("");
    string tmps;
    ss<<num;
    ss>>tmps;
    return tmps;
}

//关闭某一进程的文件描述符



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
        if (fd < 3) /***jump root dev**/
            continue;
        retval = close(fd);
        if (retval != 0)
            break;
        rewind = 1;
    }

    closedir(dir);

    return retval;
}


int print_all_fd(int v_pid){
  return 0;
}


int  main(int argc, char const *argv[]){
    int fd=open("fdwithfork.txt",O_RDWR|O_CREAT,0664);
    if(fork()){
        printf("partent:getpid:%d\n",getpid());
        char buffer1[]="acde";
        write(fd,buffer1,strlen(buffer1));
        close(fd);
    }
    else{
        printf("child:getpid:%d\n",getpid());
        printf("child:getppid:%d\n",getppid());
        fflush(stdout);

        close_all_fd(getppid());
        char buffer2[]="1234";
        write(fd,buffer2,strlen(buffer2));

        close(fd);
    }
    return 0;
}
