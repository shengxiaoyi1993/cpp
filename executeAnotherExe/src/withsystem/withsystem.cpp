#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    printf("Running ps with system\n");
    printf("main pid=%d\n", getpid());

    // ps进程结束后才返回，才能继续执行下面的代码
    if(argc == 2){
      printf("------\n");
      system(argv[1]);// 1
      printf("------\n");

    }
    else{
      printf("para wrong!\n");

    }
    printf("ps Done\n");
    exit(0);
}
