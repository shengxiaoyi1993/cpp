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




int  main(int argc, char const *argv[]){
  int flag=vfork() ;

  if (flag==0) {

    // while (true) {
    //   printf("%s\n", "child----------- ");
    //   printf("child pid:%d\n", getpid() );
    //     }

    printf("%s\n", "child----------- ");
    printf("child pid:%d\n", getpid() );
      _exit(0);
    // exit(0);

    // printf("%s\n", "child----------- ");
  }
  else if(flag<0){
    printf("parent pid:%d\n", getpid() );
    printf("%s\n", "vfork error!");

  }
  else{
    printf("parent pid:%d\n", getpid() );
    printf("%s\n", "parent done!");

  }
    return 0;
}
