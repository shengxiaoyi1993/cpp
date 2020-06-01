// 加入信号量操作后的程序
#include "mysem.h"
#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main()
{
// child
  int sem_id = get_sems();
        while(1)
        {
            P(sem_id, 0); // 对该信号量集中的0号信号  做P操作
            printf("你");
            fflush(stdout);
            sleep(1);
            printf("好");
            printf(":");
            fflush(stdout);
            sleep(1);
            V(sem_id, 0);
            time_t rawtime;
            struct tm * timeinfo;
            time ( &rawtime );
            timeinfo = localtime ( &rawtime );
            printf ( "当前系统时间: %s", asctime (timeinfo) );
        }

    return 0;
}
