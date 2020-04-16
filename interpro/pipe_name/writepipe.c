#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>

#define PIPENAME "pipetest"

int main()
{
    // 创建管道
    if(mkfifo(PIPENAME, 0666) < 0)
    {
        perror("mkfifo");
        return -1;
    }

    // 写打开管道
    int fd = open(PIPENAME, O_WRONLY);
    if(-1 == fd)
    {
        perror("open");
        return -1;
    }

    unlink(PIPENAME);

    int i = 0;
    for(i = 0; i < 10000; i++)
    {
        write(fd, &i, sizeof(i));
        printf("%d\n", i);
        // sleep(1); // 这个是以秒为单位挂起
    }

    // 关闭管道
    close(fd);

    return 0;

}
