#include <stddef.h>
#include<stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

/// 各种变量的宏和定义
/// [size_t]  long unsigned int
/// [wchar_t] int
/// [NULL] ((void *)0)
/// [ptrdiff_t] long int
/// [offsetof()]
/// [max_align_t] 是对齐要求至少和其他任何一种标量类型一样严格（一样大）的类型。



struct address {
  char name[50];
  char street[50];
  int phone;
};

struct datastruct{

  double d0;
  int i0;

  double d1;
  int i1;
};


/// 调用失败
//void test_max_align_t(){
//  size_t a = _Alignof( max_align_t);
//  printf("Alignment of max_align_t is %zu (%#zx)\n", a, a);

//  void *p = malloc(123);
//  printf("The address obtained from malloc(123) is %#" PRIxPTR"\n",
//          (uintptr_t)p);
//  free(p);
//}


void test_offsetof();

int main(int argc, char *argv[])
{

  test_offsetof();

  return(0);
}

void test_offsetof(){
  printf("address 结构中的 name 偏移 = %d 字节。\n",
         offsetof(struct address, name));

  printf("address 结构中的 street 偏移 = %d 字节。\n",
         offsetof(struct address, street));

  printf("address 结构中的 phone 偏移 = %d 字节。\n",
         offsetof(struct address, phone));


  /// 字节对齐
  printf("d0:%d,d1:%d,i0:%d,i1:%d\n",
         offsetof(struct datastruct, d0),
         offsetof(struct datastruct, d1),
         offsetof(struct datastruct, i0),
         offsetof(struct datastruct, i1)
         );
}
