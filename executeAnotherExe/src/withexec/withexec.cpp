#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    printf("main pid=%d\n", getpid());
    printf("Running ps with execlp\n");
        if(argc == 2){
          printf("------\n");
          execlp(argv[1],argv[1],nullptr,nullptr);// 1
          printf("------\n");

        }
        else{
          printf("para wrong!\n");

        }
        printf("ps Done\n");
        exit(0);
    // execlp("ps", "ps", "au", (char*)0);
    printf("ps Done");
    exit(0);
}
