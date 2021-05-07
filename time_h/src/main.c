#include <stdio.h>
#include <string.h>
#include <time.h>
#include <signal.h>


/// 关键字__restrict：该关键字修饰的指针不会出现“两个指针指向同一个地址”的情况
/// cancellation point:?
/// __THROW:
///   -  #define __THROW __attribute__ ((__nothrow__ __LEAF))
///  - 意思时不会抛出异常 参数不会被修改

/// http://www.cplusplus.com/reference/ctime/strftime/
/// 概念
/// [clock_t]:程序开始运行后花费的时间;<>据说多线程中clock_t获取的的是多个核心一共走过的时间
/// [time_t]:时间戳
/// [struct tm]:时间格式化描述
/// [struct itimerspec]: 时间片段，精确到ns
/// [clockid_t] ：时钟类型
/// CLOCK_REALTIME:系统实时时间,随系统实时时间改变而改变,即从UTC1970-1-1 0:0:0开始计时,中间时刻如果系统时间被用户该成其他,则对应的时间相应改变
/// CLOCK_MONOTONIC:从系统启动这一刻起开始计时,不受系统时间被用户改变的影响
/// CLOCK_PROCESS_CPUTIME_ID:本进程到当前代码系统CPU花费的时间
/// CLOCK_THREAD_CPUTIME_ID:本线程到当前代码系统CPU花费的时间
/// timer_t :定时器，可以定义发送信号，再通过信号处理函数可以实现定期调用某个函数
/// [time_t <> time_t] :difftime()
/// [>>time_t ]:time()
/// [clock()]:
///  - >>clock_t
/// [ mktime()]/[timelocal()]/timegm():
///  - struct tm >> time_t
///  - timegm切换成标准时间
///  - mktime()]/[timelocal()等效切换为本地时间
///
/// [strftime() ]:
///  - struct tm >> char*
///  - 格式化输出日期字符串（global locale），strftime_l（provided locale）
///
/// [gmtime()]/[gmtime_r()]:
///  - const time_t * >> struct tm*
///
/// [localtime()]/[localtime_r()] :
///  - const time_t * >> struct tm*
///
/// [asctime()]/[asctime_r()]:
///  - struct tm * >> char *
///  - "Day Mon dd hh:mm:ss yyyy\n"
///
/// [ctime()]/[ctime_r()]:
///  -  time_t * >> char *
///  - Equivalent to `asctime (localtime (timer))'.
///
/// [tzset()]
///  - 设置环境变量中的TZ到
///
/// [stime()]
///  - 修改系统时间
///  - 需要切换为root用户才能生效
/// [dysize()]
///  - the number of days in YEAR
///
/// [nanosleep()]
///  - 当前线程睡眠一定时间,直到睡眠指定时间或者当前线程被信号唤醒（调用信号处理函数或者中断该线程）
///  - __requested_time：希望睡眠时间
///  - __remaining：睡眠剩余时间
///  - rerturn
///   -0 ：请示的时间间隔结束。
///   -1：信号中断或失败，并设置errno
///
/// [clock_nanosleep()]
///  - 指定时钟进行睡眠
///  - 可以指定相对时间与绝对时间进行睡眠 0(相对时间) TIMER_ABSTIME(绝对时间)
///
/// [clock_getcpuclockid()]
///
/// [timer_create()]:创建定时器，但不会自动启动
/// [timer_delete()]:删除定时器
/// [timer_settime()]:启动定时器
/// [timer_gettime()]:获取定时器
/// [timer_getoverrun()]:获取超时计数

void test_asctime(void);

void explain_name(void);

int test_timer(void);

void test_convert(void);

void test_printDef(void);

///切换为root后执行
void test_stime();

void test_clockid(void);

int main()
{

  //  test_timer();
  //  test_asctime();
  //  test_convert();

  //  test_printDef();
  //  test_stime();
  test_clockid();


  return(0);
}


void test_clockid(void){
  struct timespec tsp;
  printf("clock_getres:\n");
  clock_getres(CLOCK_MONOTONIC,&tsp);
  printf("CLOCK_MONOTONIC:%lds %ldns\n",tsp.tv_sec,tsp.tv_nsec);
  clock_getres(CLOCK_PROCESS_CPUTIME_ID,&tsp);
  printf("CLOCK_PROCESS_CPUTIME_ID:%lds %ldns\n",tsp.tv_sec,tsp.tv_nsec);
  clock_getres(CLOCK_REALTIME,&tsp);
  printf("CLOCK_REALTIME:%lds %ldns\n",tsp.tv_sec,tsp.tv_nsec);
  clock_getres(CLOCK_THREAD_CPUTIME_ID,&tsp);
  printf("CLOCK_THREAD_CPUTIME_ID:%lds %ldns\n",tsp.tv_sec,tsp.tv_nsec);

  printf("clock_gettime:\n");
  clock_gettime(CLOCK_MONOTONIC,&tsp);
  printf("CLOCK_MONOTONIC:%lds %ldns\n",tsp.tv_sec,tsp.tv_nsec);
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tsp);
  printf("CLOCK_PROCESS_CPUTIME_ID:%lds %ldns\n",tsp.tv_sec,tsp.tv_nsec);
  clock_gettime(CLOCK_REALTIME,&tsp);
  printf("CLOCK_REALTIME:%lds %ldns\n",tsp.tv_sec,tsp.tv_nsec);
  clock_gettime(CLOCK_THREAD_CPUTIME_ID,&tsp);
  printf("CLOCK_THREAD_CPUTIME_ID:%lds %ldns\n",tsp.tv_sec,tsp.tv_nsec);


}


void test_stime(){

  //  time_t time_read=time(NULL);
  //  int ret=stime(time_read+2600);
  //  printf("ret:%d",ret);

  long int t = 111111111;

  printf("设置系统时间前的时间是：");
  fflush(stdout);
  system("date");

  stime(&t);

  printf("设置系统时间后的时间是：");
  fflush(stdout);
  system("date");




}




void test_printDef(void){
  printf("__tzname[0]:%s\n",__tzname[0]);
  printf("__tzname[1]:%s\n",__tzname[1]);
  printf("__daylight:%d\n",__daylight);
  printf("__timezone:%ld\n",__timezone);

  printf("tzname[0]:%s\n",tzname[0]);
  printf("tzname[1]:%s\n",tzname[1]);

  setenv("TZ", "GMT-8", 1);


  tzset();

  printf("__tzname[0]:%s\n",__tzname[0]);
  printf("__tzname[1]:%s\n",__tzname[1]);
  printf("__daylight:%d\n",__daylight);
  printf("__timezone:%ld\n",__timezone);

  printf("tzname[0]:%s\n",tzname[0]);
  printf("tzname[1]:%s\n",tzname[1]);




}

void test_convert(){
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
  return;

}


void  TimeEvent(void);



/// c语言定时器，每个线程单独拥有
int test_timer(void)

{

  struct sigevent evp;

  struct itimerspec ts;

  timer_t timer;

  int ret;

  evp.sigev_value.sival_ptr = &timer; //连接IO请求与信号处理的必要步骤

  evp.sigev_notify = SIGEV_SIGNAL; //SIGEV_SIGNAL表示以信号的方式通知，满足条件时就会发送信号

  evp.sigev_signo = SIGUSR1; //SIGUSR1是自己设定的信号  到期要发送的信号

  signal(SIGUSR1, TimeEvent); //第一个参数需要处理的信号值，第二个参数是处理函数

  ret = timer_create(CLOCK_REALTIME, &evp, &timer);

  if (ret)

    perror("CreateTimeEvent fail\r\n");

  else

  {

    ts.it_interval.tv_sec = 1;

    ts.it_interval.tv_nsec = 0; //设置初始时间为1秒，精确到1纳秒

    ts.it_value.tv_sec = 1;

    ts.it_value.tv_nsec = 0; //it_value指当前定时器剩下的到期时间，定时器记时时从1s减到0

    ret = timer_settime(timer, 0, &ts, NULL); //设置时间事件，将itimerspec的设置放到定时器中，这是开启一个定时器

    if (ret)

      perror("timer_settime");

  }

}

void  TimeEvent() //定时器到1s之后的动作

{

  printf("1s time coming\n");

}


//void
//
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


