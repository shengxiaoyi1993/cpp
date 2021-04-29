#include <stdio.h>
#include <string.h>
#include <time.h>

/// 概念
/// clock_t:程序开始运行后花费的时间;<>据说多线程中clock_t获取的的是多个核心一共走过的时间
/// time_t:时间戳
/// struct tm:时间格式化描述
/// struct itimerspec:



void test_asctime(void);

void explain_name(void);

int main()
{
  test_asctime();



  clock_t  clt_start=clock();

  printf("clt_start:%ld\n",clt_start);

  time_t tt=time(NULL);
  printf("tt:%ld\n",tt);

  time_t tt_1=time(NULL);
  printf("tt_1:%ld\n",tt_1);


  double tdif= difftime (tt_1, tt);

  printf("tdif:%lf\n",tdif);

//  time_t tt_mk= mktime (struct tm *__tp)

  struct tm *tm_g= gmtime (&tt);

  puts(asctime (tm_g));

//  getchar();

  long i = 10000000L;
  while (i--) {

  }

  clock_t  clt_end=clock();

  printf("clt_end:%ld\n",clt_end);



 double duration = (double)(clt_end - clt_start) / CLOCKS_PER_SEC;
 printf("duration:%lf\n",duration);


   return(0);
}


//void

void test_asctime(){
  struct tm t;

  t.tm_sec    = 10;
  t.tm_min    = 10;
  t.tm_hour   = 6;
  t.tm_mday   = 25;
  t.tm_mon    = 2;
  t.tm_year   = 89;
  t.tm_wday   = 6;

  char *pt=asctime(&t);

  puts(pt);

}

void explain_name(){

  /* Returned by `clock'.  */
  clock_t  clt;

//  /* Returned by `time'.  */
//  typedef __time_t time_t;
  time_t tt;

//  /* Clock ID used in clock and timer functions.  */
  clockid_t cld;

  /* Timer ID returned by `timer_create'.  */
  timer_t trt;


//  /* POSIX.1b structure for a time value.  This is like a `struct timeval' but
//     has nanoseconds instead of microseconds.  */
//  struct timespec
//    {
//      __time_t tv_sec;		/* Seconds.  */
//      __syscall_slong_t tv_nsec;	/* Nanoseconds.  */
//    };
  struct timespec ts;


  /* Used by other time functions.  */
  struct tm  v_tm;

  struct itimerspec  its;





}


