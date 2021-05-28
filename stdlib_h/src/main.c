#include <stdlib.h>
#include <stdio.h>

///stdlib .h 头文件定义了四个变量类型、一些宏和各种通用工具函数
/// div_t
/// ldiv_t
/// [random_data]
/// []
/// []
/// []
/// []
/// []
/// []
/// []
///
///
///
///
/// [atof()]
///  - 所指向的字符串转换为一个浮点数
/// [atoi()]
///  -  str 所指向的字符串转换为一个整数（类型为 int 型）
/// [atol()]
/// [atoll()]
///
/// [strtod()]
///  - 把参数 str 所指向的字符串转换为一个浮点数（类型为 double 型）。如果 endptr 不为空，则指向转换中最后一个字符后的字符的指针会存储在 endptr 引用的位置
/// [strtof()]
///  -
/// [strtold()]
/// [strtol()]
///  - base 进制 说明有效字符 参数base的范围为2~36,和0
///   - 如果base为0，且字符串不是以0x(或者0X)开头，则按十进制进行转化。如果base为0或者16，
/// 并且字符串以0x（或者0X）开头，那么，x（或者X）被忽略，字符串按16进制转化。
/// 如果base不等于0和16，并且字符串以0x(或者0X)开头，那么x被视为非法字符。
///   - 当base为2时，合法字符为‘0’，‘1’；base为8时，合法字符为‘0’，‘1’，……‘7’；base为10时，
/// 合法字符为‘0’，‘1’，……‘9’；base 为16时，合法字符为‘0’，‘1’，……‘9’，‘a’，……‘f’；
/// base为24时，合法字符为‘0’，……‘9’，‘a’，……‘n’，base为36时，合法字符为‘0’，……‘9’，‘a’，……‘z’；等等
///
/// [strtoul()]
///
/// [strtoq()]
/// [strtouq()]
/// [strtoll()]
/// [strtoull()]
/// [l64a()]
/// - 64个字符与数字的对应关系
/// - 返回值是字符串
//'.'  represents a 0
//'/'  represents a 1
//0-9  represent  2-11
//A-Z  represent 12-37
//a-z  represent 38-63

/// [a64l()]
///  - 返回值是对应数字
/// [random()]
///  - Return a random long integer between 0 and RAND_MAX
/// [srandom()]
/// [initstate()]
//建立随机数状态数组；
//initstate()用来初始化random()所使用的数组，参数n为数组的大小，
//参数seed为初始化的随机数种子；
//返回调用initstate()前random()所使用的数组；
/// [setstate()]
///  - <>
/// [random_r()]
/// [srandom_r()]
/// [initstate_r()]
/// [setstate_r()]
/// [rand()]
/// [srand()]
///  - 同时嗯
/// [rand_r()]
/// [drand48()]
///  - 双精度浮点数 [0.0,1.0)
/// [erand48()]
///  -
/// [lrand48()]
/// [nrand48()]
/// /* Return non-negative, long integer in [0,2^31).  */

/// [mrand48()]
/// [jrand48()]
/// /* Return signed, long integers in [-2^31,2^31).  */

/// [srand48()]
/// [seed48()]
/// [lcong48()]
/// The lcong48(), seed48(), and srand48() functions are initialization functions,
///  one of which should be invoked before either the drand48(), lrand48() or mrand48() function is called.
/// [malloc()]
///  - malloc 函数其实就是在内存中：找一片指定大小的空间，然后将这个空间的首地址给一个指针变量，
/// 这里的指针变量可以是一个单独的指针，也可以是一个数组的首地址， 这要看malloc函数中参数size的具体内容。
/// 我们这里malloc分配的内存空间在逻辑上是连续的，而在物理上可以不连续
/// [calloc()]
///  - 分配所需的内存空间，并返回一个指向它的指针。
/// malloc 和 calloc 之间的不同点是，malloc 不会设置内存为零，而 calloc 会设置分配的内存为零。
/// [realloc()]
///  - 尝试重新调整之前调用 malloc 或 calloc 所分配的 ptr 所指向的内存块的大小
/// [free()]
/// [cfree()]
/// [valloc()]
/// - 使用函数valloc与使用函数 memalign 类似，函数valloc的内部实现里，使用页的大小作为对齐长度，使用memalign来分配内存
/// [posix_memalign()]
/// -  memalign 将分配一个由size指定大小，地址是boundary的倍数的内存块。
/// 参数boundary必须是2的幂！函数 memalign 可以分配较大的内存块，并且可以为返回的地址指定粒度。
/// [aligned_alloc()]
///  - ​ 第一个参数alignment规定了分配空间的起始地址对齐的位置，由于地址是二进制的因此alignment也必须是2的整数次方．
///  - ​ 第二个参数size为分配的具体空间大小．规定size必须为alignment的整数倍．
/// [abort()]
/// - 立即终止当前进程，产生异常程序终止
/// - 进程终止时不会销毁任何对象
/// [atexit()]
///  - Register a function to be called when `exit' is called
/// [at_quick_exit()]
///  - Register a function to be called when `quick_exit' is called.
/// [on_exit()]
///  - Register a function to be called with the status given to `exit' and the given argument
/// [exit()]
///  - 调用on_exit() atexit() 注册的函数，以他们被注册的顺序
///  - 执行stdio清理
///  - 以status中断当前程序
/// [quick_exit()]
///  - 想直接结束、但又不希望呼叫到对象的 destructor 时
/// [_Exit()]
/// [getenv()]
///  - 搜索 name 所指向的环境字符串，并返回相关的值给字符串
///  - set 或者 env 或者export -p 查看环境变量相关
///  - set 显示当前shell的变量，包括当前用户的变量
///  - env 显示当前用户的变量
///  - export 显示当前导出成用户变量的shell变量
///  - declare -x 设置永久的全局变量
///  - export 变量名称=变量的内容 设置临时的变量
/// [putenv()]
///  - 修改/增加/删除环境变量，当"NAME=VALUE" 没有=时删除变量
/// [setenv()]
///  - 当REPLACE is nonzero，修改一个已存在的环境变量
/// [unsetenv()]
/// ///  - 都是临时存放到env
/// [clearenv()]
/// [mktemp()]
///  - 该函数在centos下运行总是出错
/// [mkstemp()]
///
/// [mkstemps()]
/// [mkdtemp()]
///  - 上面三个函数 mktemp mkstemps mkdtemp 总是运行出错，使用root运行也出错
/// [system()]
///  - Execute the given line as a shell command.
///  - system（）会调用fork（）产生子进程，由子进程来调用/bin/sh-c string来执行参数string字符串所代表的命令，
/// 此命令执行完后随即返回原调用的进程。在调用system（）期间SIGCHLD 信号会被暂时搁置，SIGINT和SIGQUIT 信号则会被忽略。
///  - 如果fork（）失败 返回-1：出现错误
/// 如果exec（）失败，表示不能执行Shell，返回值相当于Shell执行了exit（127）
/// 如果执行成功则返回子Shell的终止状态
/// 如果system（）在调用/bin/sh时失败则返回127，其他失败原因返回-1。若参数string为空指针（NULL），仅当命令处理程序可用时，返回非零值，可以通过这一特征判断在一个给定的操作系统上是否支持system函数(当system函数返回值为0时，表明system函数无效，在UNIX系统中，system函数总是可用的)；。如果system（）调用成功则最后会返回执行shell命令后的返回值，但是此返回值也有可能为 system（）调用/bin/sh失败所返回的127，因此最好能再检查errno 来确认执行成功。
/// - 附加说明
/// 在编写具有SUID/SGID权限的程序时请勿使用system（），system（）会继承环境变量，通过环境变量可能会造成系统安全的问题。
/// - system（）和exec（）都可以执行进程外的命令，system是在原进程上开辟了一个新的进程，但是exec是用新进程（命令）覆盖了原有的进程
/// [realpath()]
///  - 返回文件名的最简绝对字符串
///  - 文件名超出PATH_MAX 或者文件不存在则返回NULL
///  - 去除多余的"../"
///  - 相对路径转换成绝对路径
///  - 文件与文件夹均适用
/// [bsearch()]
///  - 进行一个二分法查找
///  - __compar 是比较函数 ，
/// [qsort()]
///  - 进行排序
/// [abs()]
///  - Return the absolute value of X
/// [div()]
///  - 把 numer（分子）除以 denom（分母）
///  - 结果包含商和余数
/// [ldiv()]
/// [lldiv()]
/// [ecvt()]
///  - 将双精度浮点型值转换为字符串，转换结果中不包含十进制小数点
///  - __ndigit 保留的数值
///  - __decpt 整数位数值
///  - __sign 正负符号
///  - 0.XXX*10^(__decpt)
///
/// [fcvt()]
///  - __decpt  有效数值
///
/// [gcvt()]
/// 1.gcvt()所转换后的字符串包含小数点或正负符号
/// 2.ecvt()的转换结果中不包括十进制小数点
/// 3.fcvt()的转换结果中不包括十进制小数点
///
/// [qecvt()]
/// [qfcvt()]
/// [qgcvt()]
///  - 上面是long double类型的数据
///
/// [ecvt_r()]
/// [fcvt_r()]
/// [qfcvt_r()]
/// [qecvt_r()]
///
/// [mblen()]
///  -  返回参数 str 所指向的多字节字符的长度
///
/// [mbtowc()]
///  -  把一个多字节序列转换为一个宽字符
/// [wctomb()]
///  -  把一个宽字符转换为一个多字节序列
/// [mbstowcs()]
///  - 把参数 str 所指向的多字节字符的字符串转换为参数 pwcs 所指向的数组。
/// [wcstombs()]
/// [rpmatch()]
/// - 判断输入的字符串是肯定还是否定，"Y(ES)" "N(O)"
/// [getsubopt()]
/// - 解析应用程序携带的选项
/// [setkey()]
///  - 建立美国数据加密标准表
///  - <>
/// [posix_openpt()]
///  - 打开伪终端句柄,下面都是伪终端相关函数
/// [grantpt()]
/// <>
/// [unlockpt()]
/// <>
/// [ptsname()]
/// <>
/// [ptsname_r()]
///   - 伪终端<>
/// [getpt()]
///   -返回一个伪终端<>
/// [getloadavg()]
//函数功能：
//系统中不同时期的平均负载样本，连续存放在数组loadavg[]中,
//所获得的平均负载样本的个数最大为nelem个，但是，系统规定所能获取的样本数目最多为3个，分别是1分钟，5分钟，15分钟的平均负载。
//返回值：
//如果平均负载无法得到，返回-1，否则，返回实际得到的平均负载样本的个数

// random
//rand函数采用的是乘同余算法，这种算法比较简单，产生的随机数的不重复周期较短(一般小于2**sizeof(int))。
//而random函数采用的是“非线性增长-反馈”算法，此算法产生的随机数的不重复周期较长

//多字节字符与宽字节字符
//C++中表示字符的基本数据类型有两种：char，wchar_t
//char为多字节字符类型，占一个字节，之所以叫多字节字符是因为char在表示一个字符的时候，可能需要一个字节，也可能需要多个字节。
//如：表示字符's'，char只需要一个字节，表示字符'中'，char需要三个字节。
//wchar_t为宽字节字符，占两个字节，之所以叫宽字节字符是因为wchar_t在表示任意字符的时候，都需要两个字节。

void test_l64a();

void test_getenv();

void test_env();

void test_mktemp();

void test_mkstemp();

void test_mkstemps();

void test_realpath();

int test_ecvt(void);

#define _SVID_SOURCE
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int
test_rpmatch(int argc, char *argv[])
{
  if (argc != 2 || strcmp(argv[1], "--help") == 0) {
    fprintf(stderr, "%s response\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  setlocale(LC_ALL, "");
  printf("rpmatch() returns: %d\n", rpmatch(argv[1]));
  exit(EXIT_SUCCESS);
}


int main(int argc, char *argv[])
{

  //  test_l64a();
  //  test_getenv();
  //  test_env();
  //  test_mktemp();
  //  test_mkstemp();
  //  test_mkstemps();
  //  test_realpath();
  //  test_ecvt();
  test_rpmatch(argc,argv);
  return 0;
}

void test_l64a(){
  printf("l64a:%s\n",l64a(0));
  printf("l64a:%s\n",l64a(63));
  printf("a64l:%ld\n",a64l("SXY"));
}


void test_getenv(){
  printf("PATH : %s\n", getenv("PATH"));
  printf("HOME : %s\n", getenv("HOME"));
  printf("ROOT : %s\n", getenv("ROOT"));
  printf("ALL : %s\n", getenv(""));
}

void test_env(){
  printf("SXY : %s\n", getenv("SXY"));

  putenv("SXY=shengxiaoyi");
  printf("SXY : %s\n", getenv("SXY"));
  putenv("SXY");
  printf("SXY : %s\n", getenv("SXY"));

  setenv("SXY","shengxiaoyi",1);
  printf("SXY : %s\n", getenv("SXY"));

  setenv("SXY","shengxiaoyi1",0);

  printf("SXY : %s\n", getenv("SXY"));

  setenv("SXY","shengxiaoyi2",1);

  printf("SXY : %s\n", getenv("SXY"));

  unsetenv("SXY");

  printf("SXY : %s\n", getenv("SXY"));


}

int test_ecvt(void)
{
  char *string;
  double value;
  int dec, sign;

  //   clrscr();
  value = 9.876;
  int ndig = 10;
  string = ecvt(value, ndig, &dec, &sign);
  printf("string = %s      dec = %d \
         sign = %d\n", string, dec, sign);

      value = -123.45;
      ndig= 15;
  string = ecvt(value,ndig,&dec,&sign);
  printf("string = %s dec = %d sign = %d\n",
         string, dec, sign);


  value = 0.6789e5; /* scientific
   notation */
  ndig = 5;
  string = ecvt(value,ndig,&dec,&sign);
  printf("string = %s           dec = %d\
         sign = %d\n", string, dec, sign);


      value = 0.6789e-5; /* scientific
                   notation */
      ndig = 5;
  string = ecvt(value,ndig,&dec,&sign);
  printf("string = %s           dec = %d\
         sign = %d\n", string, dec, sign);

      value = 0.6789; /* scientific
                   notation */
      ndig = 5;
  string = ecvt(value,ndig,&dec,&sign);
  printf("string = %s           dec = %d\
         sign = %d\n", string, dec, sign);

      value = 0.6789e10; /* scientific
                   notation */
      ndig = 10;
  string = fcvt(value,ndig,&dec,&sign);
  printf("string = %s           dec = %d\
         sign = %d\n", string, dec, sign);


      char buf[256];
      value = 0.6789e5; /* scientific
               notation */
  ndig = 4;
  string = gcvt(value,ndig,buf);
  printf("string = %s      buf = %s\n", string, buf);

  return 0;
}


void test_mktemp(){
  char *tmp=mktemp("XXXXXX");
  //  if (tmp) {
  //    printf("%s\n",tmp);
  //  }
  //  else{
  //    printf("tmp is null\n");

  //  }
}

void test_mkstemp(){
  int fd_mkstemp= mkstemp("XXXXXX");
  printf("fd_mkstemp:%d\n",fd_mkstemp);

}

void test_mkstemps(){
  int fd_mkstemp= mkstemps("XXXXXX",6);
  printf("fd_mkstemp:%d\n",fd_mkstemp);
}


void test_realpath(){

  // char *path = realpath("./cmake_install.cmake",NULL);
  char *path = realpath("/home/sxy/Github/cpp/stdlib_h/build/build/../build",NULL);


  if (path) {
    printf("path:%s\n",path);
  }

}




