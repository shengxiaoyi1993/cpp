#include <float.h>
#include <stdio.h>

///
/// 范围：最小值～最大值
/// 表达方式（科学计数法）： 有效数字，基数，指数




//FLT_ROUNDS	定义浮点加法的舍入模式，它可以是下列任何一个值：
//-1 - 无法确定

//0 - 趋向于零

//1 - 去最近的值

//2 - 趋向于正无穷

//3 - 趋向于负无穷

//FLT_RADIX 2	这个宏定义了指数表示的基数。基数 2 表示二进制，基数 10 表示十进制，基数 16 表示十六进制。

//这些宏定义了 FLT_RADIX 基数中的位数。
///定义基数为FLT_RADIX的尾数中的数字数。 <>?

//FLT_MANT_DIG

//DBL_MANT_DIG

//LDBL_MANT_DIG


//这些宏定义了舍入后不会改变表示的十进制数字的最大值（基数 10）。
/// 10进制浮点数中，在近似后最多不会发生改变的位数。
//FLT_DIG 6

//DBL_DIG 10

//LDBL_DIG 10

//这些宏定义了基数为 FLT_RADIX 时的指数的最小负整数值。
/// FLT_RADIX进制浮点数中，最小的负指数值。
//FLT_MIN_EXP

//DBL_MIN_EXP

//LDBL_MIN_EXP

//这些宏定义了基数为 10 时的指数的最小负整数值。
///
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





//%d 十进制有符号整数
//%u 十进制无符号整数
//%f 浮点数  %Lf(long double)
//%s 字符串
//%c 单个字符
//%p 指针的值
//%e 指数形式的浮点数
//%x, %X 无符号以十六进制表示的整数
//%0 无符号以八进制表示的整数
//%g 自动选择合适的表示法  输出long double类型时会被转换成double 输出

/// %[-][a][.][b][flag]
/// [-] -左对齐，否则右对齐
/// [a] 输出总长度
/// [.] 小数点
/// [b] 小数点后多少位
/// [flag] 见上


//\n 换行
//\f 清屏并换页
//\r 回车
//\t Tab符
//\xhh 表示一个ASCII码用16进表示,
//其中hh是1到2个16进制数

int main(int argc, char *argv[])
{

  //定义浮点加法的舍入模式，它可以是下列任何一个值
  printf("FLT_ROUNDS = %d\n", FLT_ROUNDS);
//1 到最近的值


  //这个宏定义了指数表示的基数。基数 2 表示二进制，基数 10 表示十进制，基数 16 表示十六进制
  printf("FLT_RADIX = %d\n", FLT_RADIX);
  ///FLT_RADIX = 2

  printf("float:%d\n",sizeof (float));
  printf("double:%d\n",sizeof (double));
  printf("long double:%d\n",sizeof (long double));
//  float:4
//  double:8
//  long double:16

  printf("FLT_MANT_DIG = %d\n", FLT_MANT_DIG);
  printf("DBL_MANT_DIG = %d\n", DBL_MANT_DIG);
  printf("LDBL_MANT_DIG = %d\n", LDBL_MANT_DIG);
//  FLT_MANT_DIG = 24
//  DBL_MANT_DIG = 53
//  LDBL_MANT_DIG = 64

  printf("FLT_DIG = %d\n", FLT_DIG);
  printf("DBL_DIG = %d\n", DBL_DIG);
  printf("LDBL_DIG = %d\n", LDBL_DIG);
//  FLT_DIG = 6
//  DBL_DIG = 15
//  LDBL_DIG = 18


  // FLT_RADIX进制浮点数中，最小的负指数值。
  printf("FLT_MIN_EXP = %d\n", FLT_MIN_EXP);
  printf("DBL_MIN_EXP = %d\n", DBL_MIN_EXP);
  printf("LDBL_MIN_EXP = %d\n", LDBL_MIN_EXP);
//  FLT_MIN_EXP = -125
//  DBL_MIN_EXP = -1021
//  LDBL_MIN_EXP = -16381

  printf("FLT_MAX_EXP = %d\n", FLT_MAX_EXP);
  printf("DBL_MAX_EXP = %d\n", DBL_MAX_EXP);
  printf("LDBL_MAX_EXP = %d\n", LDBL_MAX_EXP);
//  FLT_MAX_EXP = 128
//  DBL_MAX_EXP = 1024
//  LDBL_MAX_EXP = 16384

  printf("FLT_MIN_10_EXP = %d\n", FLT_MIN_10_EXP);
  printf("DBL_MIN_10_EXP = %d\n", DBL_MIN_10_EXP);
  printf("LDBL_MIN_10_EXP = %d\n", LDBL_MIN_10_EXP);
//  FLT_MIN_10_EXP = -37
//  DBL_MIN_10_EXP = -307
//  LDBL_MIN_10_EXP = -4931

//  以10为底数的最大指数值。
  printf("FLT_MAX_10_EXP = %d\n", FLT_MAX_10_EXP);
  printf("DBL_MAX_10_EXP = %d\n", DBL_MAX_10_EXP);
  printf("LDBL_MAX_10_EXP = %d\n", LDBL_MAX_10_EXP);
//  FLT_MAX_10_EXP = 38
//  DBL_MAX_10_EXP = 308
//  LDBL_MAX_10_EXP = 4932



  //FLT_EPSILON 1E-5

  //DBL_EPSILON 1E-9

  //LDBL_EPSILON 1E-9

  printf("FLT_EPSILON = %.40f\n", FLT_EPSILON);
  printf("DBL_EPSILON = %.40f\n", DBL_EPSILON);
  printf("LDBL_EPSILON = %.40Lf\n", LDBL_EPSILON);
//  FLT_EPSILON = 0.0000001192092895507812500000000000000000
//  DBL_EPSILON = 0.0000000000000002220446049250313080847263
//  LDBL_EPSILON = 0.0000000000000000001084202172485504434007
  printf("FLT_EPSILON = %.10e\n", FLT_EPSILON);
  printf("DBL_EPSILON = %.10e\n", DBL_EPSILON);
  printf("LDBL_EPSILON = %.10Le\n", LDBL_EPSILON);
//  FLT_EPSILON = 1.1920928955e-07
//  DBL_EPSILON = 2.2204460493e-16
//  LDBL_EPSILON = 1.0842021725e-19

//  printf("FLT_EPSILON = %g\n", FLT_EPSILON);
//  printf("DBL_EPSILON = %g\n", DBL_EPSILON);
//  printf("LDBL_EPSILON = %g\n", LDBL_EPSILON);

  printf("The maximum value of float = %.10e\n", FLT_MAX);
  printf("The minimum value of float = %.10e\n", FLT_MIN);
  printf("The number of digits in the number = %.10e\n", FLT_MANT_DIG);

  return 0;
}