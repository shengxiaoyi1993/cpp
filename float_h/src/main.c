#include <float.h>
#include <stdio.h>

//FLT_ROUNDS	定义浮点加法的舍入模式，它可以是下列任何一个值：
//-1 - 无法确定

//0 - 趋向于零

//1 - 去最近的值

//2 - 趋向于正无穷

//3 - 趋向于负无穷

//FLT_RADIX 2	这个宏定义了指数表示的基数。基数 2 表示二进制，基数 10 表示十进制，基数 16 表示十六进制。

//这些宏定义了 FLT_RADIX 基数中的位数。
//FLT_MANT_DIG

//DBL_MANT_DIG

//LDBL_MANT_DIG


//这些宏定义了舍入后不会改变表示的十进制数字的最大值（基数 10）。
//FLT_DIG 6

//DBL_DIG 10

//LDBL_DIG 10

//这些宏定义了基数为 FLT_RADIX 时的指数的最小负整数值。
//FLT_MIN_EXP

//DBL_MIN_EXP

//LDBL_MIN_EXP

//这些宏定义了基数为 10 时的指数的最小负整数值。
//FLT_MIN_10_EXP -37

//DBL_MIN_10_EXP -37

//LDBL_MIN_10_EXP -37

//这些宏定义了基数为 FLT_RADIX 时的指数的最大整数值。

//FLT_MAX_EXP

//DBL_MAX_EXP

//LDBL_MAX_EXP

//这些宏定义了基数为 10 时的指数的最大整数值。
//FLT_MAX_10_EXP +37

//DBL_MAX_10_EXP +37

//LDBL_MAX_10_EXP +37


//这些宏定义最大的有限浮点值。
//FLT_MAX 1E+37

//DBL_MAX 1E+37

//LDBL_MAX 1E+37

//这些宏定义了可表示的最小有效数字。
//FLT_EPSILON 1E-5

//DBL_EPSILON 1E-9

//LDBL_EPSILON 1E-9

//这些宏定义了最小的浮点值。
//FLT_MIN 1E-37

//DBL_MIN 1E-37

//LDBL_MIN 1E-37





int main(int argc, char *argv[])
{

  //定义浮点加法的舍入模式，它可以是下列任何一个值
  printf("FLT_ROUNDS = %d\n", FLT_ROUNDS);
//1 到最近的值




  //这个宏定义了指数表示的基数。基数 2 表示二进制，基数 10 表示十进制，基数 16 表示十六进制
  printf("FLT_RADIX = %d\n", FLT_RADIX);

  printf("FLT_MANT_DIG = %d\n", FLT_MANT_DIG);
  printf("DBL_MANT_DIG = %d\n", DBL_MANT_DIG);
  printf("LDBL_MANT_DIG = %d\n", LDBL_MANT_DIG);

  printf("The maximum value of float = %.10e\n", FLT_MAX);

  printf("The minimum value of float = %.10e\n", FLT_MIN);

  printf("The number of digits in the number = %.10e\n", FLT_MANT_DIG);

  return 0;
}
