#include <stdio.h>
#include <setjmp.h>

//setjmp/longjmp的典型用途是例外处理机制的实现：利用longjmp恢复程序或线程的状态，甚至可以跳过栈中多层的函数调用。

/// setjmp
/// - 保存环境变量到ENV,信号模板也进行保存
/// - 第一次返回0,以后返回longjmp设置的值
///
/// [longjmp]
///  - 跳转到之前设置(setjmp)处

/// [sigsetjmp()]
//sigsetjmp()会保存目前堆栈环境，然后将目前的地址作一个记号，
//而在程序其他地方调用siglongjmp()时便会直接跳到这个记号位置，然后还原堆栈，继续程序的执行。
//参数env为用来保存目前堆栈环境，一般声明为全局变量
//参数savesigs若为非0则代表搁置的信号集合也会一块保存
//当sigsetjmp()返回0时代表已经做好记号上，若返回非0则代表由siglongjmp（）跳转回来。

//void test_setjmp();
//void test_sigsetjmp();
//int main(int argc, char *argv[])
//{

//  //test_setjmp();
//  test_sigsetjmp();


//  return 0;
//}

//void test_setjmp(){
//  jmp_buf env;
//  int val;
//  int val2;


//  val=setjmp(env);
//  printf("env\n");


//  jmp_buf env2;
//  val2=setjmp(env2);
//  printf("env2\n");

//  printf ("val is %d\n",val);


//  val++;
//  if (val<10) longjmp(env, val);

//  val++;
//  if (val<20) longjmp(env, val);


//  //  printf ("val2 is %d\n",val2);
//  //  val2++;
//  //  if (val2<10) longjmp(env2, val2);
//}




//void test_sigsetjmp(){
//  //  sigsetjmp();
//  jmp_buf env;
//  int val;
//  int val2;


//  val=sigsetjmp(env,1);
//  printf("env\n");


//  jmp_buf env2;
//  val2=setjmp(env2);
//  printf("env2\n");

//  printf ("val is %d\n",val);


//  val++;
//  if (val<10) siglongjmp(env, val);

//  val++;
//  if (val<20) siglongjmp(env, val);
//}


/// 向某一程序发送信号
/// kill -s SIGRTMIN+15 [pid]
/// <>等学习信号相关知识后再进行理解


#include <stdio.h>
#include <signal.h>
#include <setjmp.h>

#define ENV_UNSAVE 0
#define ENV_SAVED 1

int flag_saveenv = ENV_UNSAVE;
jmp_buf env;  //保存待跳转位置的栈信息

void hand_min15(int);


int main()
{
    switch(sigsetjmp(env, 1))
    {
        case 0:
        {
            printf("sigsetjmp\n");
            flag_saveenv = ENV_SAVED;
            break;
        }
        case 1:
        {
            printf("return from min+15\n");
            break;
        }
        default:
            break;
    }

    signal(SIGRTMIN+15, hand_min15);


    printf("wait for signal\n");
    while(1);

    return 0;
}

void hand_min15(int sig_num)
{
    if (flag_saveenv = ENV_UNSAVE)
    {
        return;
    }

    sleep(10);
    printf("after sleep\n");
    siglongjmp(env, 1);
    printf("recv min+15\n");
    return;
}
