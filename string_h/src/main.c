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
/// [strcmp()]
/// [strncmp()]
/// [strcoll()]
/// [strxfrm()]
/// [strcoll_l()]
/// [strxfrm_l()]
/// [strdup()]
/// [strndup()]
/// [strchr()]
/// [strrchr()]
/// [strcspn()]
/// [strspn()]
/// [strpbrk()]
/// [strstr()]
/// [strtok()]
/// [__strtok_r()]
/// [strtok_r()]
/// [strlen()]
/// [strnlen()]
/// [strerror()]
/// [strerror_l()]
/// [__bzero()]
/// [bzero()]
/// [bcmp()]
/// [index()]
/// [rindex()]
/// [ffs()]
/// [strcasecmp()]
/// [strncasecmp()]
/// [strsep()]
/// [strsignal()]
/// [__stpcpy()]
/// [stpcpy()]
/// [stpncpy()]


int main(int argc, char *argv[])
{

  strcat("","");
  return 0;
}
