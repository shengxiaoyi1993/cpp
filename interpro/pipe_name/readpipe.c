#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>

#define PIPENAME "pipetest"

int main()
{
    // 读打开管道
    int fd = open(PIPENAME, O_RDONLY);
    if(-1 == fd)
    {
        perror("open");
        return -1;
    }

    int num = 0;
    int i = 0;
    for(i = 0; i < 10000; i++)
    {
        read(fd, &num, sizeof(int));
        printf("%d\n", num);
        fflush(stdout); // 强制刷新输出缓冲区
    }

    printf("\n");
    close(fd);

    return 0;

}
