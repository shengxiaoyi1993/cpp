#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int main(void)
{
        int fd;
        char *rdbuf;
        rdbuf=(char *)malloc(10);
        memset(rdbuf,'\0',10);
        int i;

        for(i = 0; i < 10; i++)
        {
                printf("init mem[%d]:%c\n",i,*(rdbuf+i));
        }
        char *wrbuf = "butterfly";
        fd = open("/dev/mem",O_RDWR);
        if(fd< 0)
        {
                printf("open /dev/mem failed.\n");
                return 0;
        }
        else{
                printf("open /dev/mem succeed.\n");

        }

        ssize_t size=read(fd,rdbuf,10);
        printf("size:%d\n",size );
        printf("errno:%d\n",errno );

        // printf("strerror(errno):%s\n",strerror(errno) );

        for(i = 0; i < 10; i++)
        {
                printf("old mem[%d]:%c\n",i,*(rdbuf+i));
        }
        lseek(fd,5,0);
        ssize_t wrtsize=write(fd,wrbuf,10);
        printf("wrtsize:%d\n",wrtsize );
        printf("errno:%d\n",errno );

        lseek(fd,0,0);//move f_ops to the front
        read(fd,rdbuf,10);
        for(i = 0; i < 10; i++)
        {
                printf("new mem[%d]:%c\n",i,*(rdbuf+i));
        }
        return 0;
}
