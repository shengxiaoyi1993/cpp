#include <ctype.h>
#include <stdio.h>



/// locale_t
///  - 根据计算机用户所使用的语言，所在国家或者地区，以及当地的文化传统所定义的一个软件运行时的语言环境。
///  - inux下可以在 /usr/share/i18n/locales 查看
///  - locale表达方式是 [语言[_地域][.字符集] [@修正值]


/// ctype.h
/// 用于测试和映射字符。
///  - 是否是某种类型的字符
/// 这些函数接受 int 作为参数，它的值必须是 EOF 或表示为一个无符号字符
///

//1	int isalnum(int c)
//该函数检查所传的字符是否是字母和数字。
//2	int isalpha(int c)
//该函数检查所传的字符是否是字母。
//3	int iscntrl(int c)
//该函数检查所传的字符是否是控制字符。
//4	int isdigit(int c)
//该函数检查所传的字符是否是十进制数字。
//5	int isgraph(int c)
//该函数检查所传的字符是否有图形表示法。
//6	int islower(int c)
//该函数检查所传的字符是否是小写字母。
//7	int isprint(int c)
//该函数检查所传的字符是否是可打印的。
//8	int ispunct(int c)
//该函数检查所传的字符是否是标点符号字符。
//9	int isspace(int c)
//该函数检查所传的字符是否是空白字符。
//10	int isupper(int c)
//该函数检查所传的字符是否是大写字母。
//11	int isxdigit(int c)
//该函数检查所传的字符是否是十六进制数字


//1	int tolower(int c)
//该函数把大写字母转换为小写字母。
//2	int toupper(int c)
//该函数把小写字母转换为大写字母。

/// 注：以上函数都有一个xxx_l()版本的函数，指定locale


int main(int argc, char *argv[])
{


  printf("__isascii:%d\n",__isascii(44));
  // 1
  printf("__toascii:%x\n",__toascii(0x666));


  // 未知会崩溃
  //  locale_t l;
  //  isalnum_l(88,l);
  //  printf("isalnum_l(88,l):%d\n",isalnum_l(88,l));




  return 0;
}
