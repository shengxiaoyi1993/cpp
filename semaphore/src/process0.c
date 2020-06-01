// 加入信号量操作后的程序
#include "mysem.h"
#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main()
{
    int semid = create_sems(10); // 创建一个包含10个信号量的信号集
    init_sems(semid, 0, 1);  // 初始化编号为 0 的信号量值为1
// father
        while(1)
        {
            P(semid,0);
            printf("在");
            sleep(1);
            printf("吗");
            printf("?");
            fflush(stdout);
            V(semid, 0);
            time_t rawtime;
            struct tm * timeinfo;
            time ( &rawtime );
            timeinfo = localtime ( &rawtime );
            printf ( "当前系统时间: %s", asctime (timeinfo) ); 
        }
        wait(NULL);


    destroy_sems(semid);
    return 0;
}
