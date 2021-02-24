/// 验证
/// 1. pthread_mutex_lock必须有pthread_mutex_unlock来解锁，否则就会阻塞。有这一句是因为网上的错误例子
/// 2. 传递参数时，需要有在父程序中有相应的变量存在。或者直接传值
/// 3.




/*thread_mutex.c*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_NUMBER        3            /* 线程数 */
#define REPEAT_NUMBER        3            /* 每个线程的小任务数 */
#define DELAY_TIME_LEVELS 10.0         /*小任务之间的最大时间间隔*/
pthread_mutex_t mutex;

void *thrd_func(void *arg) {
     // int thrd_num = *((int*)arg);
     int thrd_num = (long)arg;

     int delay_time = 0, count = 0;
     int res;
     /* 互斥锁上锁 */
     res = pthread_mutex_lock(&mutex);
     if (res) {
          printf("Thread %d lock failed\n", thrd_num);
          pthread_exit(NULL);
     }
     printf("Thread %d is starting\n", thrd_num);
     for (count = 0; count < REPEAT_NUMBER; count++) {
         delay_time = (int)(rand() * DELAY_TIME_LEVELS/(RAND_MAX)) + 1;
         sleep(delay_time);
         printf("\tThread %d: job %d delay = %d\n",
                                      thrd_num, count, delay_time);
     }
     printf("Thread %d finished\n", thrd_num);
     pthread_mutex_unlock(&mutex);
     // pthread_exit(NULL);
}

int main(void) {
     pthread_t thread[THREAD_NUMBER];
     int para[THREAD_NUMBER];
     int no = 0, res;
     void * thrd_ret;


     srand(time(NULL));
     /* 互斥锁初始化 */
     pthread_mutex_init(&mutex, NULL);
     for (no = 0; no < THREAD_NUMBER; no++) {
        para[no]=no;
          // res = pthread_create(&thread[no], NULL, thrd_func, (void*)(&para[no]));
          res = pthread_create(&thread[no], NULL, thrd_func, (int*)no);

          if (res != 0) {
              printf("Create thread %d failed\n", no);
              exit(res);
          }
          else
          {
              printf("Create thread %d succeed\n", no);
              // exit(res);
          }
     }
     printf("Create treads success\n Waiting for threads to finish...\n");
     for (no = 0; no < THREAD_NUMBER; no++) {
          res = pthread_join(thread[no], &thrd_ret);
          if (!res) {
                printf("Thread %d joined\n", no);
          } else  {
              printf("Thread %d join failed\n", no);
          }
     }
     /****互斥锁解锁***/
     pthread_mutex_unlock(&mutex);
     pthread_mutex_destroy(&mutex);
     return 0;
}
