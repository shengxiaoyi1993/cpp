#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    printf("main pid=%d\n", getpid());
    pid_t pid = fork();
    switch(pid)
    {
    case -1:
        perror("fork failed");
        exit(1);
        break;
    case 0:
        // 这是在子进程中，调用execlp切换为ps进程
        if(argc == 2){
          printf("------\n");
          execlp(argv[1],argv[1],nullptr,nullptr);// 1
          printf("------\n");

        }
        else{
          printf("para wrong!\n");
        }
        break;
    default:
        // 这是在父进程中，输出相关提示信息
        printf("Parent, ps Done\n");
        break;
    }
    exit(0);
}
