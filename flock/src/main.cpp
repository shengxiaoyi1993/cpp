/*
 * #说明
 * - 该程序用于说明linux系统中运行唯一的实例
 *
 * LOCK_SH 建立共享锁定。多个进程可同时对同一个文件作共享锁定。
 * LOCK_EX 建立互斥锁定。一个文件同时只有一个互斥锁定。
 * LOCK_UN 解除文件锁定状态。
 * LOCK_NB 无法建立锁定时，此操作可不被阻断，马上返回进程。通常与LOCK_SH或LOCK_EX 做OR(|)组合。
 *
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>

int main()
{
  int lock_file = open("/tmp/single_proc.lock", O_CREAT|O_RDWR, 0666);
  int rc = flock(lock_file, LOCK_EX|LOCK_NB);

  if (rc)
  {
    if (EWOULDBLOCK == errno)
    {
      printf("该实例已经运行!\nExit...");
    }
  }
  else
  {
    char buffer[64];
    sprintf(buffer, "pid:%d\n", getpid());
    write(lock_file, buffer, strlen(buffer));
    printf("已启动新实例，输入任何字符退出...\n");

    scanf("%s",buffer);
    printf("Exit\n",buffer);
    close(lock_file); // 不要忘记释放文件指针
  }
  exit(0);

}
