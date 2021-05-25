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
/// [atexit()]
/// [at_quick_exit()]
/// [on_exit()]
/// [exit()]
/// [quick_exit()]
/// [_Exit()]
/// [getenv()]
/// [putenv()]
/// [setenv()]
/// [unsetenv()]
/// [clearenv()]
/// [mktemp()]
/// [mkstemp()]
/// [mkstemps()]
/// [mkdtemp()]
/// [system()]
/// [realpath()]
/// [bsearch()]
/// [qsort()]
/// [abs()]
/// [div()]
/// [ldiv()]
/// [lldiv()]
/// [ecvt()]
/// [fcvt()]
/// [gcvt()]
/// [qecvt()]
/// [qfcvt()]
/// [qgcvt()]
/// [ecvt_r()]
/// [fcvt_r()]
/// [qfcvt_r()]
/// [qecvt_r()]
/// [mblen()]
/// [mbtowc()]
/// [wctomb()]
/// [mbstowcs()]
/// [wcstombs()]
/// [rpmatch()]
/// [getsubopt()]
/// [getloadavg()]



// random
//rand函数采用的是乘同余算法，这种算法比较简单，产生的随机数的不重复周期较短(一般小于2**sizeof(int))。
//而random函数采用的是“非线性增长-反馈”算法，此算法产生的随机数的不重复周期较长

void test_l64a();

int main(int argc, char *argv[])
{

  test_l64a();
  return 0;
}

void test_l64a(){
  printf("l64a:%s\n",l64a(0));
  printf("l64a:%s\n",l64a(63));
  printf("a64l:%ld\n",a64l("SXY"));


}

