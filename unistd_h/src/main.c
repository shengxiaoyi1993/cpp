#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
// https://www.cnblogs.com/kunhu/p/3608109.html
// pipe()
// 管道是一种把两个进程之间的标准输入和标准输出连接起来的机制，从而提供一种让多个进程间通信的方法，
// 当进程创建管道时，每次都需要提供两个文件描述符来操作管道。其中一个对管道进行写操作，另一个对管道进行读操作。
// 对管道的读写与一般的IO系统函数一致，使用write()函数写入数据，使用read()读出数据。
// 返回值：成功，返回0，否则返回-1。参数数组包含pipe使用的两个文件的描述符。fd[0]:读管道，fd[1]:写管道。
// 必须在fork()中调用pipe()，否则子进程不会继承文件描述符。两个进程不共享祖先进程，就不能使用pipe。
// 但是可以使用命名管道。
// 当管道进行写入操作的时候，如果写入的数据小于128K则是非原子的，如果大于128K字节，缓冲区的数据将被连续地写入
// 管道，直到全部数据写完为止，如果没有进程读取数据，则将一直阻塞



char * getDirectory( char * buf, int count)
{
  int i;
  int rslt = readlink("/proc/self/exe", buf, count - 1);
  if (rslt < 0 || (rslt >= count - 1))
  {
    return NULL;
  }
  buf[rslt] = '\0';
  for (i = rslt; i >= 0; i--)
  {
    if (buf[i] == '/')
    {
      buf[i + 1] = '\0';
      break;
    }
  }
  return buf;
}

void test_pipe();


int main(int argc, char ** argv)
{
  //    char path[1024];
  //    printf("%s\n", getDirectory(path, 1024));
  test_pipe();
  return 0;


}


/// 建立匿名通道
/// fork出一个子进程B
/// 主进程A 发送"OK"
/// 子进程 隔30s读取一次数据，
///  若判断"OK"，则返回 "get OK"
///  否则返回" not get OK"
///
void test_pipe(){

  int pids[2];
  if(pipe(pids) != 0){
    perror("pipe()");
    return ;
  }

  __pid_t childpid;

  childpid=fork();

  if(childpid == 0){
    fcntl( pids[0], F_SETFL, O_NONBLOCK);

    printf("this is child!\n");

//    printf("child");
    while (1) {
//      printf(">");

      char data[10];
      ssize_t size_read=  read( pids[0],data,10);
      if (size_read>0) {
        printf("\n");
        printf("child read:%s\n",data);
        if (strncmp(data,"OK",2) == 0 ) {
          ssize_t size_write=  write( pids[1],"GET OK",10);
          if (size_write >0) {
            printf("child write:%s\n","GET OK");
          }
          else{
            printf("Fail to child write\n");
          }
        }
        else{
          ssize_t size_write=  write( pids[1],"NOT GET OK",strlen("NOT GET OK")+1);
          if (size_write >0) {
            printf("child write:%s\n","NOT GET OK");
          }
          else{
            perror("write()");
            printf("Fail to child write\n");
          }
        }
        //        sleep(1);
        //        exit(0);
        fflush(stdout);

        return ;
      }
      else{
//        printf("Fail to child read\n");
//        perror("read()");
        fflush(stdout);

      }

    }

  }
  else if(childpid>0){
    fcntl( pids[0], F_SETFL, O_NONBLOCK);

    printf("this is parent!\n");
    sleep(5);
    ssize_t size_write= write(pids[1], "OK", 2);
    if (size_write >0) {
      printf("parent write:%s\n","OK");
    }
    else{
      perror("write()");

      printf("Fail to parent write\n");
    }

    fflush(stdout);

    while (1) {

      char data[10];
      ssize_t size_read=  read( pids[0],data,10);
      if (size_read>0) {
        printf("\n");
        printf("parent read:%s\n",data);
        fflush(stdout);
        return ;
      }
    }

  }
  else{
    perror("pichildpidpe()\n");
    return ;
  }



}
