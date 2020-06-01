#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

int func(int argc, char const *argv[]){
  pid_t pid = fork();
  switch(pid)
  {
  case -1:
      perror("fork failed");
      // exit(1);
      return 0;
      // break;
  case 0:
      // 这是在子进程中，调用execlp切换为ps进程
      if(argc == 1){
        printf("------\n");
        // execlp(argv[1],argv[1],nullptr);// 1
        execlp("sh","sh","/home/sxy/Github/cpp/executeAnotherExe/bin/launch_cycleapp.sh",nullptr);// 1

        printf("------\n");

      }
      else{
        printf("para wrong!\n");
      }
      return 1;

      // break;
  default:
      // 这是在父进程中，输出相关提示信息
      printf("Parent, ps Done\n");
      // break;
      return 2;
  }
}




int main(int argc, char const *argv[])
{
    printf("main pid=%d\n", getpid());
    int flag=func(argc,argv);
    std::cout<<"flag:"<<flag<<std::endl;
    return 0;
    // exit(0);
}
