/**
 * 功能:创建一个守护进程
 *
 * 守护进程编写规则:
 * (1)调用umask(0) --取消umask的功能
 * umask是个函数,用来限制(屏蔽)一些文件权限的.
 * (2)fork()一个子进程出来,然后父进程退出;固定套路.
 *
 * 守护进程虽然可以通过终端启动，但是和终端不挂钩
 * 守护进程是在后台运行，它不应该从键盘上接收任何东西,也不应该把输出结果打印到屏幕或者终端上来.
 *
 * 守护进程不会收到来自内核的 SIGINT(ctrl+c) ,SIGWINCH(终端窗口大小改变)信号.
 *
 * 守护进程和后台进程的区别:
 * 1.守护进程和终端不挂钩,后台进程能往终端上输出东西
 * 2.守护进程和关闭终端时不受影响,后台进程会随着终端的退出而退出.
 */

/*
 * comment by sxy 20210312
 * 1. 该程序启动后成为守护进程
 * 2. 但是没有对怎样对个程序监听和重新启动
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include <sys/stat.h>
#include <fcntl.h>



int ngx_daemon()
{
    int fd;

    switch(fork())
    {
    case -1:
        //创建子进程失败,这里可以写日志......
        return -1;
    case 0:
        //子进程,走到这里直接break
        break;
    default:
        //父进程直接退出
        printf("父进程直接退出\n" );
        exit(0);
    }

    // 只有子进程流程才能走到这里.

    if (setsid() == -1)   //给子进程设置一个新的会话(这样终端退出时就不会杀死子进程)
    {
        //记录错误日志......
        return -1;
    }

    umask(0);   //设置为0,不要让它来限制文件权限

    //守护进程运行于后台,屏蔽从键盘上的输入消息
    fd = open("/dev/null",O_RDWR);          //打开黑洞设备,读写方式
    if(fd == -1)
    {
        // 记录错误日志......
        return -1;
    }

    if(dup2(fd,STDIN_FILENO) == -1) // 重定向键盘输入到黑洞
    {
        return -1;
    }

    if(dup2(fd,STDOUT_FILENO) == -1) // 重定向输出到黑洞
    {
        return -1;
    }

    if (fd > STDERR_FILENO)
    {
        if(close(fd) == -1)
        {
            return -1;
        }
    }

    return 1;
}


int main()
{
    if(ngx_daemon() != 1)
    {

        //创建守护进程失败
        printf("创建守护进程失败 end");
        return 1;
    }

    //守护进程创建成功.
    for(;;)
    {
        sleep(1);
        printf("休息一秒,进程id=%d \n", getpid());
    }

    return 0;
}
