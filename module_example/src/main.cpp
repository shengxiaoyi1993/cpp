#include <iostream>
#include <regex>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <bits/stdc++.h>
#include <map>
#define linux
#ifdef linux
#include <unistd.h>
#include <dirent.h>
#endif
#ifdef WIN32
#include <direct.h>
#include <io.h>
#endif
using namespace std;


/**
 * @function: 获取cate_dir目录下的所有文件名
 * @param: cate_dir - string类型
 * @result：vector<string>类型
*/
vector<string> getFiles(string cate_dir)
{
	vector<string> files;//存放文件名

#ifdef WIN32
	_finddata_t file;
	long lf;
	//输入文件夹路径
	if ((lf=_findfirst(cate_dir.c_str(), &file)) == -1) {
		cout<<cate_dir<<" not found!!!"<<endl;
	} else {
		while(_findnext(lf, &file) == 0) {
			//输出文件名
			//cout<<file.name<<endl;
			if (strcmp(file.name, ".") == 0 || strcmp(file.name, "..") == 0)
				continue;
			files.push_back(file.name);
		}
	}
	_findclose(lf);
#endif

#ifdef linux
	DIR *dir;
	struct dirent *ptr;
	char base[1000];

	if ((dir=opendir(cate_dir.c_str())) == NULL)
        {
		perror("Open dir error...");
                exit(1);
        }

	while ((ptr=readdir(dir)) != NULL)
	{
		if(strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0)    ///current dir OR parrent dir
		        continue;
		else if(ptr->d_type == 8)    ///file
			//printf("d_name:%s/%s\n",basePath,ptr->d_name);
			files.push_back(ptr->d_name);
		else if(ptr->d_type == 10)    ///link file
			//printf("d_name:%s/%s\n",basePath,ptr->d_name);
			continue;
		else if(ptr->d_type == 4)    ///dir
		{
			files.push_back(ptr->d_name);
			/*
		        memset(base,'\0',sizeof(base));
		        strcpy(base,basePath);
		        strcat(base,"/");
		        strcat(base,ptr->d_nSame);
		        readFileList(base);
			*/
		}
	}
	closedir(dir);
#endif

	//排序，按从小到大排序
	sort(files.begin(), files.end());
	return files;
}




int main(){
  string dir_path="/storage/image_subgroup/imagegather_line1/1_80/";

  vector<string>  list_file=getFiles(dir_path);
  cout<<"size: "<<list_file.size()<<endl;
  for (size_t i = 0; i < list_file.size(); i++) {
    std::cout << "i " << i << ' '<<list_file[i]<<endl;

      regex pattern(".*blockcut_(.*)_(.*)_(.*).jpg");
    	string s = list_file[i];
    	smatch result;
    	bool ismatch = regex_match(s, result, pattern);

    	if (ismatch)
    	{
    		cout << "匹配成功:" << result[0] << endl;
    		cout << result.size()<<endl;
    		for (int i = 1; i <= result.size(); i++){
          cout << result[i] << " " << endl;
          string strtmp=result[i];
          cout << "strtmp: " << strtmp << endl;

          int ot = atoi(strtmp.c_str());
          cout<<"ot="<<ot<<endl;
        }
    	}
    	else
    		cout << "匹配失败" << endl;
  }

  return 0;
}
