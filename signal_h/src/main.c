#include <stdio.h>
#include <signal.h>

/// signal.h
/// 信号处理相关的函数
/// - 信号定义 /usr/include/bits/signum.h
//信号的处理有三种方法，分别是：忽略、捕捉和默认动作
//- 忽略信号，大多数信号可以使用这个方式来处理，但是有两种信号不能被忽略（分别是 SIGKILL和SIGSTOP）。因为他们向内核和超级用户提供了进程终止和停止的可靠方法，如果忽略了，那么这个进程就变成了没人能管理的的进程，显然是内核设计者不希望看到的场景
//- 捕捉信号，需要告诉内核，用户希望如何处理某一种信号，说白了就是写一个信号处理函数，然后将这个函数告诉内核。当该信号产生时，由内核来调用用户自定义的函数，以此来实现某种信号的处理。
//- 系统默认动作，对于每个信号来说，系统都对应由默认的处理动作，当发生了该信号，系统会自动执行。不过，对系统来说，大部分的处理方式都比较粗暴，就是直接杀死该进程。
//具体的信号默认动作可以使用man 7 signal来查看系统的具体定义。在此，我就不详细展开了，需要查看的，可以自行查看

/// [信号掩码]
//信号掩码用来表示哪些信号会被线程阻塞
//多线程中用pthread_sigmask(3)来设置信号掩码，传统单线程用sigprocmask(2)来设置掩码

/// 信号屏蔽与信号忽略
/// - 信号屏蔽是通过给指定信号设置添加到掩膜集合中，（此时的信号称为未决信号）；信号屏蔽会在不屏蔽之后进行处理（信号并未消失）
/// - 信号忽略是通过将特定信号的处理函数设置为SIG_IGN，该信号不会再进行处理
/// act.sa_handler = SIG_IGN;
/// signal(SIGINT, SIG_IGN);

//阻塞和未决的概念： A signal may be blocked, which means that it will not be delivered until it is later unblocked. Between the time when it is generated and when it is delivered a signal is said to be pending.详情见signal(7)
//阻塞就是被阻塞的信号不能被送达(delivered)给线程，除非解除阻塞(unblocked)
//未决就是信号处于信号生成(generated)状态和信号送达(delivered)状态之间，则称为未决信号，通俗的讲就是，信号已经产生了，但是还没有成功送达给线程处理

/// struct sigaction

//sa_handler此参数和signal()的参数handler相同，代表新的信号处理函数
//sa_mask 用来设置在处理该信号时暂时将sa_mask 指定的信号集搁置
//sa_flags 用来设置信号处理的其他相关操作，下列的数值可用。
//SA_RESETHAND：当调用信号处理函数时，将信号的处理函数重置为缺省值SIG_DFL
//SA_RESTART：如果信号中断了进程的某个系统调用，则系统自动启动该系统调用
//SA_NODEFER ：一般情况下， 当信号处理函数运行时，内核将阻塞该给定信号。但是如果设置了 SA_NODEFER标记， 那么在该信号处理函数运行时，内核将不会阻塞该信号

/// siginfo_t
/// - 描述信号
/// - 使用psiginfo可以打印
/// - 使用该信号获取


/// [sig_atomic_t]
///  - 原子操作的数据类型
/// [sigset_t]
///  - 信号集用来描述信号的集合，linux所支持的所有信号可以全部或部分的出现在信号集中，主要与信号阻塞相关函数配合使用。下面是为信号集操作定义的相关函数：
///  - 实际上公有64个信号类型，sigset_t是一个 unsigned long int 的数组，每添加一个信号时将第n位置1（n为信号的序号值），删除信号就置0
/// [pid_t]
///  - 进程号
/// [uid_t]
///  - 用户id  getuid 返回当前进程的用户
/// [signal()]
///  - 设置信号的处理函数
/// [kill]
/// pid：接收信号的进程（组）的进程号
/// pid>0：发送给进程号为pid的进程
/// pid=0：发送给当前进程所属进程组里的所有进程
/// pid=-1：发送给除1号进程和自身以外的所有进程
/// pid<-1：发送给属于进程组-pid的所有进程
/// [killpg()]
/// - 发送信号 sig 给进程组 pgrp。见 signal(7) 里的可用信号列表。
/// - 如果 pgrp 是 0，killpg() 发送信号给调用进程的进程组。(POSIX 说：如果 pgrp 是小于或等于 1，其行为是未定义的。)
///
/// [raise()]
///  - 产生某个信号
/// [ssignal]
///  -
/// [gsignal]
///  -
/// [psignal]
///  -
///  - psignal(2,"SIGINT error");
///
/// [psiginfo]
///  - https://pubs.opengroup.org/onlinepubs/9699919799/functions/psignal.html
///
/// [sigblock]
///
/// [sigsetmask]
/// [siggetmask]
///
/// ！对信号集进行操作
/// [sigemptyset]
/// [sigfillset]
/// [sigaddset]
/// [sigdelset]
/// [sigismember]
///
/// [sigprocmask]
///  - 获取或者改变被阻塞信号的集合
///  - 其操作依参数how来决定，如果参数oldset不是NULL指针，那么目前的信号屏蔽字会由此指针返回。如果set是一个非空指针，则参数how指示
///  - 如何修改当前信号屏蔽字。每个进程都有一个用来描述哪些信号递送到进程时将被阻塞的信号集，该信号集中的所有信号在递送到进程后都将被阻塞。
///  - 参数how的取值不同，带来的操作行为也不同，该参数可选值如下：
/// 1．SIG_BLOCK:　该值代表的功能是将newset所指向的信号集中所包含的信号加到当前的信号掩码中，作为新的信号屏蔽字(原有信号屏蔽字 + set屏蔽字)。
/// 2．SIG_UNBLOCK:将参数newset所指向的信号集中的信号从当前的信号掩码中移除。
/// 3．SIG_SETMASK:设置当前信号掩码为参数newset所指向的信号集中所包含的信号
///  -
///
/// [sigsuspend]
///  - 如果在等待信号发生时希望去休眠，则使用sigsuspend函数是非常合适的
///  - 将进程的信号屏蔽字设置为由sigmask指向的值。在捕捉到一个信号或发生了一个会终止该进程的信号之前，该进程被挂起。
///  - 如果捕捉到一个信号而且从该信号处理程序返回，则sigsuspend返回，并且将该进程的信号屏蔽字设置为调用sigsuspend之前的值。
///  - 注意，此函数没有成功返回值。如果它返回到调用者，则总是返回-1，并将errno设置为EINTR（表示一个被中断的系统调用）。
///
/// [sigaction]
///  - 获取或者设置信号的行为 struct sigaction
///  - 给指定信号提供信号处理函数
///  - 处理该信号时可以屏蔽指定信号
///  - <>?中断系统调用时，重新调用系统调用
/// [sigpending]
///  - 获取未决信号
/// [sigwait]
///  - 等待信号集合中的任意信号出现
/// [sigwaitinfo]
///  - psiginfo
/// [psiginfo]
///  - 打印
/// [sigtimedwait]
/// [sigqueue]
///  - sigqueue发送的信号可以由sigtimedwait捕获，__val 复制到siginfo_t的si_value
///  - sigqueue与kill:sigqueue可以发送额外参数，kill不可以.

/// [struct sigvec]
/// [sigvec()]
///  - 为兼容 historical BSD signal API提供
///  - 新版本中应该使用 (sigaction(), sigprocmask())
/// [sigreturn()]
///  - return from signal handler and cleanup stack frame
///  - only to allow the implementation of signal handlers.  It should never be called directly
///  - <>?struct sigcontext
/// [siginterrupt()]
///  - __interrupt不为零，使信号中断系统调用
///
///  - __interrupt为0，使系统调用在信号处理后重新调用
/// [sigstack()]
///  - 被淘汰，许多平台没有实现
///  - 在ss中执行信号处理函数，若__oss！=NULL，动机保存原有的signal stack status
/// [sigaltstack()]
///  - 比sigstack更受人欢迎
///  - signaltstack 函数最常见的用法是处理普通程序因为栈溢出而触发的 SIGSEGV 信号的处理过程，在这种情况下 SIGSEGV 信号处理函数不能在进程栈中执行，想要处理这种情况，必须使用一个可选的信号处理栈。
/// - 创建一个可选的信号函数执行栈对于那些预期可能会耗尽标准栈的程序非常有用。这种情况是可能发生的，例如因为栈增长的过大触及到了向上增长的堆空间或者栈空间触及到了 setrlimit(RLIMIT_STACK, &rlim) 设定的限制外的内存空间等。

/// ！线程中的信号
/// 每个线程都有自己的信号屏蔽字，但是信号的处理是进程中所有线程共享的。这意味着单个线程可以阻止某个信号，但是当某个线程修改了一个信号的处理行为，那么所有线程都会共享这个改变。
/// 进程中的信号是递送到单个线程的。如果一个信号和硬件故障相关，那么该信号一般会被发送到引起该事件的线程中去，而其他的信号会被发送到任意的线程中。
///

//=================================test sigaltstack================================
void test_sigaltstack(){
  stack_t ss;

  ss.ss_sp = malloc(SIGSTKSZ);
  if (ss.ss_sp == NULL) {
    perror("malloc");
    exit(1);
  }

  ss.ss_size = SIGSTKSZ;
  ss.ss_flags = 0;
  if (sigaltstack(&ss, NULL) == -1) {
    perror("sigaltstack");
    exit(1);
  }

}




//=================================测试 siginfo_t======================================
//union sigval {
//      int   sival_int;
//      void *sival_ptr;
//  };
// 该组合体是一个4字节整数值或者是一个指针
// 如何使用由使用者进行约定


//typedef struct {
//	int si_signo;  //信号编号
//	int si_code;
//	union sigval si_value;
//	int si_errno;
//	pid_t si_pid; //发出信号的进程id
//	uid_t si_uid; // 发出信号的userid
//	void *si_addr;
//	int si_status; //<>?
//	int si_band; //<>?
//} siginfo_t;


//si_signo:896
//si_code:896
//si_errno:896
//si_pid:2
//si_uid:0
//si_status:14
//si_band:2
//^\hello: Quit (Signal sent by the kernel 0 0)
//si_signo:3
//si_code:128
//si_errno:0
//si_pid:0
//si_uid:0
//si_status:14
//si_band:0


void test_sigwaitinfo(){
  sigset_t sst;

  sigemptyset(&sst);
  sigaddset(&sst,SIGQUIT);
  siginfo_t kk;

  printf("si_signo:%d\n",kk.si_signo);
  printf("si_code:%d\n",kk.si_code);
  printf("si_errno:%d\n",kk.si_errno);
  printf("si_pid:%d\n",kk.si_pid);
  printf("si_uid:%d\n",kk.si_uid);
  printf("si_status:%d\n",kk.si_status);
  printf("si_band:%d\n",kk.si_band);


  //  kk.si_code;
  //  kk._sifields;
  //  kk.si_errno;
  //  kk.si_signo;

  sigwaitinfo(&sst,&kk);
  psiginfo(&kk,"hello");


  printf("si_signo:%d\n",kk.si_signo);
  printf("si_code:%d\n",kk.si_code);
  printf("si_errno:%d\n",kk.si_errno);
  printf("si_pid:%d\n",kk.si_pid);
  printf("si_uid:%d\n",kk.si_uid);
  printf("si_status:%d\n",kk.si_status);
  printf("si_band:%d\n",kk.si_band);

}




//HUP     1    终端断线
//INT       2    中断（同 Ctrl + C）
//QUIT    3    退出（同 Ctrl + \）
//TERM    15    终止
//KILL      9    强制终止
//CONT   18    继续（与STOP相反， fg/bg命令）
//STOP    19    暂停（同 Ctrl + Z）

//void signal_catchfunc(int);

//int main(int argc, char *argv[])
//{
//    int ret;

//    SIGHUP;

//   ret = signal(SIGINT, signal_catchfunc);

//   if( ret == SIG_ERR)
//   {
//      printf("错误：不能设置信号处理程序。\n");
//      exit(0);
//   }
//   printf("开始生成一个信号\n");
//   ret = raise(SIGINT);
//   if( ret !=0 )
//   {
//      printf("错误：不能生成 SIGINT 信号。\n");
//      exit(0);
//   }

//   printf("退出...\n");
//   return(0);
//}

//void signal_catchfunc(int signal)
//{
//   printf("!! 信号捕获 !!\n");
//}







//volatile sig_atomic_t    quitflag;    /* set nonzero by signal handler */

//static void
//sig_int(int signo)    /* one signal handler for SIGINT and SIGQUIT */
//{
//  if (signo == SIGINT)
//    printf("/ninterrupt/\n");
//  else if (signo == SIGQUIT)

//    quitflag = 1;    /* set flag for main loop */
//}

//void print_sigset_t(sigset_t v){
//  int i;
//  for ( i=0;i<_SIGSET_NWORDS;i++) {
//    printf("%lu ",v.__val[i]);
//  }
//  printf("\n");
//}

void test_sigaction(){
  struct sigaction z;

  //  z.__sigaction_handler;
  z.sa_flags;
  z.sa_mask;
  z.sa_restorer;


}

//int
//main(void)
//{

//  sigset_t    newmask, oldmask, zeromask;

//  if (signal(SIGINT, sig_int) == SIG_ERR)
//    printf("signal(SIGINT) error\n");
//  if (signal(SIGQUIT, sig_int) == SIG_ERR)
//    printf("signal(SIGQUIT) error\n");

//  sigemptyset(&zeromask);
//  sigemptyset(&newmask);
//  sigaddset(&newmask, SIGQUIT);

//  printf("_SIGSET_NWORDS:%d\n",_SIGSET_NWORDS);

//  /*
//     * Block SIGQUIT and save current signal mask.
//     */

//  if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
//    printf("SIG_BLOCK error");

//  printf("quitflag:%d\n",quitflag);

//  while (quitflag == 0)
//    sigsuspend(&zeromask);// 睡眠，不屏蔽任何信号


//  /*
//     * SIGQUIT has been caught and is now blocked; do whatever.
//     */
//  quitflag = 0;

//  /*
//     * Reset signal mask which unblocks SIGQUIT.
//     */
//  if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
//    printf("SIG_SETMASK error");

//  exit(0);
//}



#include <signal.h>
#include <unistd.h>
#include <stdio.h>
static void int_hander(int s)
{
  printf("Catch a signal sigint\n");
}
int
main(void)
{
  test_sigwaitinfo();
}


