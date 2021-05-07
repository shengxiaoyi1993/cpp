#include <assert.h>

/// __BEGIN_DECLS/__END_DECLS 用于声明函数也可以在时c++中符使用，相当于extern "c" {...
///

/// assert.h
/// [__assert_fail()]:打印错误信息（给定的字符串），文件，所在行，锁在列
/// [__assert_perror_fail()]:打印错误信息(错误码)，文件，所在行，锁在列
/// [assert()]
///  - 在调试结束后，可以通过在包含 #include 的语句之前插入 #define NDEBUG 来禁用 assert 调用
///  - 编写时应将多个条件进行拆分
///  - 用于发现非法情况，而非错误情况
///  - 仅在debug版本起作用，编译为 Release 版本则被忽略。
void test___assert_fail(void);

///
void test___assert_perror_fail(void);

void test___assert(void);

void test_assert(void);




 int main(int argc, char *argv[])
{

//   test___assert_fail();
//   test___assert_perror_fail();
//   test___assert();
   test_assert();
  return 0;
}

 void test___assert_fail(void){
//   __assert_fail("__assertion","__file",__LINE__,"__function");
   __assert_fail(__ASSERT_FUNCTION,__FILE__,__LINE__,__FUNCTION__);
 }
//myproj: /home/sxy/Github/cpp/assert_h/src/main.c:30: test___assert_fail: Assertion `test___assert_fail' failed.


 void test___assert_perror_fail(void){
   __assert_perror_fail(1,__FILE__,__LINE__,__FUNCTION__);
 }
//myproj: /home/sxy/Github/cpp/assert_h/src/main.c:35: test___assert_perror_fail: Unexpected error: Operation not permitted.



 void test___assert(void){
   __assert("err for __assert",__FILE__,__LINE__);

 }
 // myproj: /home/sxy/Github/cpp/assert_h/src/main.c:42: Assertion `err for __assert' failed.


 void test_assert(void){
//   assert(1); //无输出
     assert(0); //输出且配退出程序
 }
//myproj: /home/sxy/Github/cpp/assert_h/src/main.c:55: test_assert: Assertion `0' failed.
