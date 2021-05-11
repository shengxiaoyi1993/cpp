#include <stdio.h>
#include <locale.h>
#include <time.h>
/// <>比较生僻,碰到例程后进行分析
/// <>? locale的使用场景
/// <>? 各个函数联系
/// <>? locale的理解,每个进程一个?,那么线程呢?


/// [lconv] 给定数字和货币的符号
///
//非货币数值格式化参数
//char* decimal_point

//用作小数点的字符
//(公开成员对象)

//char* thousands_sep
//用于在小数点前分隔数位组的字符
//(公开成员对象)

//char* grouping
//字符串，其元素指示数位组的大小
//(公开成员对象)

//货币数值格式化参数
//char* mon_decimal_point
//用作小数点的字符

//(公开成员对象)
//char* mon_thousands_sep
//用于在小数点前分隔数位组的字符

//(公开成员对象)
//char* mon_grouping
//字符串，其元素指示数位组的大小

//(公开成员对象)
//char* positive_sign
//用于指示非负货币量的字符串

//(公开成员对象)
//char* negative_sign
//用于指示负货币量的字符串

//(公开成员对象)
//本地货币数值格式化参数
//char* currency_symbol
//当前 C 本地环境中用于通货的符号

//(公开成员对象)
//char frac_digits

//货币量中小数点后显示的位数
//(公开成员对象)
//char p_cs_precedes

//若 currency_symbol 置于非负值前则为 1 ，于其后则为 ​0​
//(公开成员对象)
//char n_cs_precedes

//若 currency_symbol 置于负值前则为 1 ，于其后则为 ​0​
//(公开成员对象)
//char p_sep_by_space

//指示 currency_symbol 、 positive_sign 及非负货币值的分隔
//(公开成员对象)
//char n_sep_by_space

//指示 currency_symbol 、 positive_sign 及负货币值的分隔
//(公开成员对象)
//char p_sign_posn

//指示非负货币值中 positive_sign 的位置
//(公开成员对象)
//char n_sign_posn

//指示负货币值中 negative_sign 的位置
//(公开成员对象)
//国际货币数值格式化参数
//char* int_curr_symbol

//当前 C 本地环境中用作国际通货名的字符串
//(公开成员对象)
//char int_frac_digits

//国际货币量中小数点后显示的位数
//(公开成员对象)
//char int_p_cs_precedes

//(C99)

//若 int_curr_symbol 置于非负值前则为 1 ，于其后则为 ​0​
//(公开成员对象)
//char int_n_cs_precedes

//(C99)

//若 int_curr_symbol 置于负值前则为 1 ，于其后则为 ​0​
//(公开成员对象)
//char int_p_sep_by_space

//(C99)

//指示 int_curr_symbol 、 positive_sign 及非负国际货币值的分隔
//(公开成员对象)
//char int_n_sep_by_space

//(C99)

//指示 int_curr_symbol 、 positive_sign 及负国际货币值的分隔
//(公开成员对象)
//char int_p_sign_posn

//(C99)

//指示非负国际货币值中 positive_sign 的位置
//(公开成员对象)
//char int_n_sign_posn

//(C99)

//指示负国际货币值中 positive_sign 的位置
//(公开成员对象)

/// [setlocale]
/// - 作用于当前进程,其他进程不会发生变化;线程重新启动需要重新设置
//category -- 这是一个已命名的常量，指定了受区域设置影响的函数类别。

//LC_ALL 包括下面的所有选项。
//LC_COLLATE 字符串比较。参见 strcoll()。
//LC_CTYPE 字符分类和转换。例如 strtoupper()。
//LC_MONETARY 货币格式，针对 localeconv()。
//LC_NUMERIC 小数点分隔符，针对 localeconv()。
//LC_TIME 日期和时间格式，针对 strftime()。
//LC_MESSAGES 系统响应。
//locale -- 如果 locale 是 NULL 或空字符串 ""，则区域名称将根据环境变量值来设置，其名称与上述的类别名称相同。
///  - linux下可以在 /usr/share/i18n/locales 查看
///  - locale表达方式是 [语言[_地域][.字符集] [@修正值]

/// [duplocale]:
///
/// [freelocale]: 释放一个__locale_t(由duplocale/newlocale返回的)
///
/// [uselocale]:同时应用于所有线程


void test_lconv(void);
void test_setlocale();

//返回一个locale的数据集,符合要求的
// 创建或者修改原有的locale成一个新的locale,取决于__base,__base==0则创建,否则就创建
void test_newlocale();





int main ()
{
  test_setlocale();


  return(0);
}


void test_lconv(void){
  printf("Locale is: %s\n", setlocale(LC_ALL, ""));
  struct lconv *  lc=localeconv();
  printf("decimal_point:%s\n",lc->decimal_point);
  printf("thousands_sep:%s\n",lc->thousands_sep);
  printf("grouping:%s\n",lc->grouping);
  printf("int_curr_symbol:%s\n",lc->int_curr_symbol);
  printf("currency_symbol:%s\n",lc->currency_symbol);
  printf("mon_decimal_point:%s\n",lc->mon_decimal_point);
  printf("mon_thousands_sep:%s\n",lc->mon_thousands_sep);
  printf("mon_grouping:%s\n",lc->mon_grouping);
  printf("positive_sign:%s\n",lc->positive_sign);
  printf("negative_sign:%s\n",lc->negative_sign);

  printf("int_frac_digits:%c\n",lc->int_frac_digits);
  printf("frac_digits:%c\n",lc->frac_digits);
  printf("p_cs_precedes:%c\n",lc->p_cs_precedes);
  printf("p_sep_by_space:%c\n",lc->p_sep_by_space);
  printf("n_cs_precedes:%c\n",lc->n_cs_precedes);
  printf("n_sep_by_space:%c\n",lc->n_sep_by_space);
  printf("p_sign_posn:%c\n",lc->p_sign_posn);
  printf("n_sign_posn:%c\n",lc->n_sign_posn);
  printf("int_p_cs_precedes:%c\n",lc->int_p_cs_precedes);
  printf("int_p_sep_by_space:%c\n",lc->int_p_sep_by_space);
  printf("int_n_cs_precedes:%c\n",lc->int_n_cs_precedes);
  printf("int_n_sep_by_space:%c\n",lc->int_n_sep_by_space);
  printf("int_p_sign_posn:%c\n",lc->int_p_sign_posn);
  printf("int_n_sign_posn:%c\n",lc->int_n_sign_posn);
}

void test_setlocale(){

  //  在Linux/Unix环境下，通常以下面格式表示locale名称：
  //  language[_territory][.codeset][@modifier]，
  //  language 为 ISO 639 中规定的语言代码，
  //http://www.loc.gov/standards/iso639-2/php/code_list.php?__cf_chl_jschl_tk__=114adb41753862bf8b6069343e00e538ee8b90fb-1620735155-0-ASYP_DdceSMDwylld-bV6BNmDQQB-S9w3JoPwyxoAXMJz9q-4d-H9z_pN8kkJUeEJQpISTgwmWBDLF0tyG_GqXErVneoyskMNi8Oco3wApFG-YcP5Dfdsu8GmtKA8FenBDovGRqykRGjlxFeJCs9_Jyu0UrQ-seyCWd8ix7OnkYec2pwog6ZP6CmySbGRet_mwvn-Ai9FNtEe45cQsTEDL3DuAffVcj3ynyvTz0JJdrNmeCDETJY3E7MvMSL04GaBn3tbElTcLyDEHq9ibWoG5JyBr5YBIAO4Eu5uB7cpLmhQfU4pRIVijr2GFierNoI34Gn7USlGD9pK-Ektye_FGez2t997JgJOkaVk5pzGOuzE_oy89jg2OMO_OsY_EKN4PI4iQCiAnOPyeMcOo8BFSgqEoajtGy_Gh0uAe9H8kEiFKceGA8GZYWOqpzrkFYnNA
  //  territory 为 ISO 3166 中规定的国家/地区代码，
  //https://www.iso.org/obp/ui/#iso:pub:PUB500001:en
  //  codeset 为字符集名称。

  time_t currtime;
  struct tm *timer;
  char buffer[80];

  time( &currtime );
  timer = localtime( &currtime );

//  printf("Locale is: %s\n", setlocale(LC_ALL, "en_GB.UTF-8"));
//  strftime(buffer,80,"%c", timer );
//  printf("Date is: %s\n", buffer);


//  printf("Locale is: %s\n", setlocale(LC_ALL, "de_DE.UTF-8"));
//  strftime(buffer,80,"%c", timer );
//  printf("Date is: %s\n", buffer);

  printf("Locale is: %s\n", setlocale(LC_ALL, ""));
  strftime(buffer,80,"%c", timer );
  printf("Date is: %s\n", buffer);
//  Locale is: en_US.UTF-8
//  Date is: Tue 11 May 2021 08:35:21 PM CST
}


void test_newlocale(){

//  int argc;
//  char **argv;
//  char buf[100];
//  time_t t;
//  size_t s;
//  struct tm *tm;
//  locale_t loc, nloc;

//  if (argc < 2) {
//      fprintf(stderr, "Usage: %s locale1 [locale2]\n", argv[0]);
//      exit(EXIT_FAILURE);
//  }

//  /* Create a new locale object, taking the LC_NUMERIC settings
//     from the locale specified in argv[1]. */

//  loc = newlocale(LC_NUMERIC_MASK, argv[1], (locale_t) 0);
//  if (loc == (locale_t) 0)
//      errExit("newlocale");

//  /* If a second command-line argument was specified, modify the
//     locale object to take the LC_TIME settings from the locale
//     specified in argv[2]. We assign the result of this newlocale()
//     call to 'nloc' rather than 'loc', since in some cases, we might
//     want to preserve 'loc' if this call fails. */

//  if (argc > 2) {
//      nloc = newlocale(LC_TIME_MASK, argv[2], loc);
//      if (nloc == (locale_t) 0)
//          errExit("newlocale");
//      loc = nloc;
//  }

//  /* Apply the newly created locale to this thread. */

//  uselocale(loc);

//  /* Test effect of LC_NUMERIC. */

//  printf("%8.3f\n", 123456.789);

//  /* Test effect of LC_TIME. */

//  t = time(NULL);
//  tm = localtime(&t);
//  if (tm == NULL)
//      errExit("time");

//  s = strftime(buf, sizeof(buf), "%c", tm);
//  if (s == 0)
//      errExit("strftime");

//  printf("%s\n", buf);

//  /* Free the locale object. */

//  uselocale(LC_GLOBAL_HANDLE);    /* So 'loc' is no longer in use */
//  freelocale(loc);

//  exit(EXIT_SUCCESS);
}
