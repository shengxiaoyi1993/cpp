// #include <unistd.h>
// #include <sys/types.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <iostream>
// #include<sys/stat.h>
// #include<fcntl.h>
// #include<string.h>
// #include <dirent.h>
// #include <sstream>
// #include <string>
//
// using namespace std;
//
//
//
//
// int  main(int argc, char const *argv[]){
//
//   if (vfork() == 0) {
//     printf("%s\n", "child----------- ");
//
//     printf("%s\n", "child----------- ");
//   }
//   else{
//     printf("%s\n", "parent done!");
//
//   }
//
//
//     return 0;
// }


#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include<fcntl.h>
#include<sys/stat.h>


using namespace std ;


std::string integerToString(int num){
    stringstream ss;
    ss.clear();
    ss.str("");
    string tmps;
    ss<<num;
    ss>>tmps;
    return tmps;
}


int main(void)
{
    // DIR* dirp;
    // struct dirent *dp1=(struct dirent *)malloc(sizeof(struct dirent));
    // struct dirent *dp2=(struct dirent *)malloc(sizeof(struct dirent));
    // string ppfd="/proc/" +integerToString(getpid())+ "/fd";
    // dirp = opendir(ppfd.c_str());
    //
    // // dirp=opendir(".");
    // while(1)
    // {
    //     if((readdir_r(dirp,dp1,&dp2))!=0)
    //     {
    //         perror("readdir_r");
    //         exit(EXIT_FAILURE);
    //     }
    //     if(dp2==NULL)
    //         break;
    //     if(dp2->d_name[0]=='.')
    //         continue;
    //     printf("inode=%d\t",dp2->d_ino);
    //     printf("reclen=%d\t",dp2->d_reclen);
    //     printf("name=%s\n",dp2->d_name);
    // }
    // closedir(dirp);
    // free(dp1);
    // free(dp2);
    // return 0;

// setvbuf(stdout, (char *)NULL, _IONBF, 0);
// setbuf(stdout, NULL);
    close(1);
    int fd = open("1.txt", O_RDWR|O_CREAT);
    if(fd == -1)
         perror("open 1.txt");
    string error="fd:"+integerToString(fd);
    perror(error.c_str());
    printf("printf hello world\n");
    // fflush(stdout);
    char buf[24] = "write fd hello world";
    write(1, buf, strlen(buf));
    // fflush(stdout);

    close(fd);

}
