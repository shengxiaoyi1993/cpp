#include <stdio.h>
#include <math.h>

#define PI 3.14159265

/// acos
/// asin
/// atan
/// atan2 (定象限)
/// cos
/// cosh 双曲余弦
/// sin
/// tanh
/// exp
/// frexp (x = mantissa * 2 ^ exponent ),结果是exponent
/// ldexp 返回 x 乘以 2 的 exponent 次幂
/// log()
/// log10()
/// modf 求浮点数的整数和小数部分
/// pow 返回 x 的 y 次幂。
/// sqrt
/// ceil 大于或等于x的最小整数
/// fabs 浮点数的绝对值
/// floor 返回小于或等于x的最大整数
/// fmod 返回x除以y的余数锁



int main(int argc, char *argv[])
{

//  double x, ret, val;

//  x = 0.9;
//  val = 180.0 / PI;

//  ret = acos(x) * val;
//  printf("%lf 的反余弦是 %lf 度", x, ret);

  double x = 1024, fraction;
    int e;

    fraction = frexp(x, &e);
    printf("x = %.2lf = %.2lf * 2^%d\n", x, fraction, e);

  return 0;
}
