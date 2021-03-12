/**
 *
 * supervisor
 *
 * author: liyangguang (liyangguang@software.ict.ac.cn)
 *
 * date: 2011-01-21 21:04:01
 *
 * changes
 * 1, execl to execv
 */

/*
 * # modified by sxy
 * 1. 父进程在创建子进程后就退出，子进程仍然持续运行
 * 2. 子进程创建孙子进程管理/和自动启动目标进程
 *
 * # 使用方法
 * - `./myproc path`,path为目标程序的绝对路径
 *
 * # 测试通过
 * # 几项技术
 * - pstree 查看进程和子进程
 * - ps -ef查看具体进程
 * - 进程会在/proc/ 创建相应的文件夹,具体有什么用<有待学习>
 * - /var/run 的*.pid为可以在启动单一程序时起全局控制作用<未测试>
 *
 *
 *
*/

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/fs.h>
#include <sys/stat.h>


int
main(int argc, char **argv)
{
  int ret, i, status;
  char *child_argv[100] = {0};
  pid_t pid;
  if (argc < 2) {

    fprintf(stderr, "Usage:%s <exe_path> <args...>\n", argv[0]);
    return -1;
  }
  for (i = 1; i < argc; ++i) {
    child_argv[i-1] = (char *)malloc(strlen(argv[i])+1);
    strncpy(child_argv[i-1], argv[i], strlen(argv[i]));
    child_argv[i-1][strlen(argv[i])] = '\0';
  }

  pid = fork();
  if (pid == -1) {
    fprintf(stderr, "fork() error.errno:%d error:%s\n", errno, strerror(errno));
  }
  if (pid == 0) {
    // 只有子进程流程才能走到这里.
    fprintf(stderr, "child pid:%d\n",getpid());

    ///<>若父进程未关闭，仍为父进程的子进程
    if (setsid() == -1)   //给子进程设置一个新的会话(这样终端退出时就不会杀死子进程)
    {
      //记录错误日志......
      return -1;
    }

    umask(0);   //设置为0,不要让它来限制文件权限

    if (chdir ("/") == -1)
      return -1;
    //      for (i = 0; i < NR_OPEN; i++)
    //      close (i);

    //守护进程运行于后台,屏蔽从键盘上的输入消息
    int fd;
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



    while(1){
      /// 孙进程实现对目标进程的监控和自动启动

      if((pid=fork())>0){
        pid = wait(&status);
        fprintf(stderr, "grand child close.restart...\n");
      }
      else if(pid< 0){
        fprintf(stderr, "fail to create grand child...\n");
        exit(1);//fork失败，退出
      }
      else{
        fprintf(stderr, "grand child pid:%d\n",getpid());

        ret = execv(child_argv[0], (char **)child_argv);
        if (ret < 0) {
          fprintf(stderr, "fail to execv grand cheld :%d errno:%d error:%s\n", ret, errno, strerror(errno));
//          continue;
          exit(EXIT_FAILURE);
        }
        else{
          fprintf(stderr, "execv end \n");
        }

      }
    }

    // exit(0);
  }

  if (pid > 0) {

    fprintf(stdout, "parent pid:%d\n",getpid());
    // pid = wait(&status);
    fprintf(stdout, "wait return\n");
    exit(EXIT_SUCCESS);
  }

  return 0;
}


//通过fork()创建的子进程以父进程的名称
//excel 启动的程序继承原有名称<?>
