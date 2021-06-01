#include "string.h"

/// [memcpy()]
///  - Copy N bytes of SRC to DEST
///  - SRC 与 DEST 应避免指向同一区域
/// [memmove()]
///  - 同memcpy(),但允许SRC 与 DEST有重叠的部分
/// [memccpy()]
///  - 拷贝时，若查找到__c字符，则退出
/// [memset()]
///  - 将一片内存置为__c
/// [memcmp()]
///  - 比较两片内存中的数据
/// [memchr()]
///  - 从buf所指内存区域的前count个字节查找字符ch。
/// [strcpy()]
///  - Copy SRC to DEST
/// [strncpy()]
///  - Copy no more than N characters of SRC to DEST
/// [strcat()]
///  - Append SRC onto DEST
/// strcat() 函数把 strSource 所指向的字符串追加到 strDestination 所指向的字符串的结尾，
/// 所以必须要保证 strDestination 有足够的内存空间来容纳两个字符串，否则会导致溢出错误。
/// 注意：strDestination 末尾的\0会被覆盖，strSource 末尾的\0会一起被复制过去，最终的字符串只有一个\0。
/// [strncat()]
///  - 把 src 所指向的字符串追加到 dest 所指向的字符串的结尾，直到 n 字符长度为止
/// [strcmp()]
///  - 把 str1 所指向的字符串和 str2 所指向的字符串进行比较
/// [strncmp()]
///  - 把 str1 所指向的字符串和 str2 所指向的字符串进行比较(指定字符数)
/// [strcoll()]
///  - 把 str1 和 str2 进行比较，结果取决于 LC_COLLATE 的位置设置
///  - 对于设置了 LC_COLLATE 语言环境的情况下，则根据 LC_COLLATE 设置的语言排序方式进行比较。
///  - 例如，汉字会根据拼音进行比较
/// [strxfrm()]
///  - 根据程序当前的区域选项中的 LC_COLLATE 来转换字符串 src 的前 n 个字符，并把它们放置在字符串 dest 中。
/// [strcoll_l()]
/// [strxfrm_l()]
/// [strdup()]
///  - strdup()在内部调用了malloc()为变量分配内存，不需要使用返回的字符串时，需要用free()释放相应的内存空间，否则会造成内存泄漏。
/// [strndup()]
///  - strndup 同上，指定数量
/// [strchr()]
///  - 参数 str 所指向的字符串中搜索第一次出现字符 c（一个无符号字符）的位置
/// [strrchr()]
///  - 在参数 str 所指向的字符串中搜索最后一次出现字符 c（一个无符号字符）的位置
/// [strcspn()]
///  - 检索字符串 str1 开头连续有几个字符都不含字符串 str2 中的字符（其中的任意一个字符）
/// [strspn()]
///  - 检索字符串 str1 中第一个不在字符串 str2 中出现的字符下标。
/// [strpbrk()]
/// - 检索字符串 str1 中第一个匹配字符串 str2 中字符的字符，不包含空结束字符。
/// - 也就是说，依次检验字符串 str1 中的字符，当被检验字符在字符串 str2 中也包含时，则停止检验，并返回该字符位置。
/// [strstr()]
///  - 在字符串 haystack 中查找第一次出现字符串 needle 的位置，不包含终止符 '\0'。
/// [strtok()]
///  - 根据字符串分割字符串
///  - strtok函数第一次调用时会把s字符串中所有在delim中出现的字符替换为NULL。然后通过依次调用strtok(NULL, delim)得到各部分子串
/// [__strtok_r()]
/// [strtok_r()]
/// [strlen()]
///  - 计算字符串 str 的长度，直到空结束字符，但不包括空结束字符。
/// [strnlen()]
///  - 获取字符串s中实际字符个数，不包括结尾的'\0'；如果实际个数 <= maxlen，则返回n，否则返回第二个参数
/// [strerror()]
///  - 从内部数组中搜索错误号 errnum，并返回一个指向错误消息字符串的指针。strerror 生成的错误字符串取决于开发平台和编译器。
/// [strerror_l()]
/// [__bzero()]
/// [bzero()]
///  - 将字符串s的前n个字节置为0，一般来说n通常取sizeof(s),将整块空间清零
///  - 同memset 单是可以，可以置为非零值
/// [bcmp()]
///  - 比较字符串s1和s2的前n个字节是否相等
/// [index()]
///  - :查找字符串并返回首次出现的位置
/// [rindex()]
///  - 用来找出参数s字符串中最后一个出现的参数c 地址，然后将该字符出现的地址返回
/// [ffs()]
///  -  ffs()函数用于查找一个整数中的第一个置位值(也就是bit为1的位)
/// [strcasecmp()]
///  - strcasecmp()用来比较参数s1 和s2 字符串，比较时会自动忽略大小写的差异
/// [strncasecmp()]
///
/// [strsep()]
///  - https://www.cnblogs.com/devilmaycry812839668/p/6353912.html
///  - strtok时子串中间没有出现换行，而strsep却有多个换行
///  - 如果输入的串的有连续的多个字符属于delim，（此例source中的逗号+空格，感叹号+空格等就是这种情况），
/// strtok会返回NULL，而strsep会返回空串  ""。
/// 因而我们如果想用strsep函数分割字符串必须进行返回值是否是空串的判断
/// [strsignal()]
///  - 答应描述信号的字符串
/// [__stpcpy()]
/// [stpcpy()]
///  - 拷贝字符串
/// [stpncpy()]
///


void test_strxfrm();
void test_token () ;
void test_index();

char string[] ="A string\tof ,,tokens\nand some  more tokens";
char seps[]   =" ,\t\n";
char *token, *s;
int test_strsep( void );

int main(int argc, char *argv[])
{

  //  strcat("","");
  //  test_strxfrm();
  //  test_token();
//  test_index();
  test_strsep();
  return 0;
}

void test_index(){
  char *s = "0123456789012345678901234567890";
  char *p;
  p = index(s, '5');
  printf("%s\n", p);
}


void test_token () {
  char str[80] = "This is - www.runoob.com - website";
  const char s[2] = "-";
  char *token;

  /* 获取第一个子字符串 */
  token = strtok(str, s);

  /* 继续获取其他的子字符串 */
  while( token != NULL ) {
    printf( "%s\n", token );

    token = strtok(NULL, s);
  }

}

int test_strsep( void )
{
   printf( "%s\n\nTokens:\n", string );
/* Establish string and get the first token: */
   s=string;
   token = strsep( &s, seps );
while( token != NULL )
   {
/* While there are tokens in "string" */
      printf( " %s\n", token );
/* Get next token: */
      token = strsep( &s, seps );
   }
return 0;
}


void test_strxfrm()
{
  char dest[20];
  char src[20];
  int len;

  strcpy(src, "W3C School");
  len = strxfrm(dest, src, 20);

  printf("字符串 |%s| 的长度是： |%d|", dest, len);

}
