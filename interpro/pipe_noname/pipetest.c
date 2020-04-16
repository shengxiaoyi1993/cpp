#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

int main()
{
    int fd[2]; // 用来保存文件描述符
    pipe(fd);

    pid_t pid = fork();// 创建进程
    if(pid > 0)
    {
        // 父进程写管道，需要关闭读端
        close(fd[0]);
        int i = 0;
        for(i=10; i<20; i++)
        {
            write(fd[1], &i, sizeof(int));
            sleep(1);
        }

        close(fd[1]);// 关闭写端
        exit(0);
    }

    // 子进程读管道
    close(fd[1]); // 先关闭写端
    int x;
    int i = 0;
    for(; i<10; i++)
    {
        read(fd[0], &x, sizeof(int));
        printf("%d ", x);
        setbuf(stdout, NULL);
    }
    close(fd[0]);
    printf("\n");

    return 0;
}
