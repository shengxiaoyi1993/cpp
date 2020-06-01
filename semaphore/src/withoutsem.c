// 未加信号量的测试代码
#include "mysem.h"
#include <stdio.h>
#include <unistd.h>

int main()
{

    pid_t id = fork(); // 创建子进程
    if( id < 0)
    {
        perror("fork");
        return -1;
    }
    else if (0 == id)
    {// child
        int sem_id = get_sems();
        while(1)
        {
            printf("你");
            fflush(stdout);
            sleep(1);
            printf("好");
            printf(":");
            fflush(stdout);
            sleep(1);
        }
    }
    else
    {// father
        while(1)
        {
            printf("在");
            sleep(1);
            printf("吗");
            printf("?");
            fflush(stdout);
        }
        wait(NULL);
    }

    return 0;
}
