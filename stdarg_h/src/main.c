#include <stdarg.h>
#include<stdio.h>

/// va_list,va_arg 和va_end三个宏，这三个宏可用于在参数个数未知（即参数个数可变）时获取函数中的参数
/// - 原理是c的参数方法
/// - 常用方法（使用自定义规则实现不同的功能）
///   - count+count个相同类类型的数据
///   - 规定参数都是字符串，且最后一个字符串以""截尾
///   - 使用同一数据类型规定类型，使用时【类型+一个该类型的数据】
///



#define _INTSIZEOF(n)   ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )


const int INT_TYPE = 100000;
const int STR_TYPE = 100001;
const int CHAR_TYPE = 100002;
const int LONG_TYPE = 100003;
const int FLOAT_TYPE = 100004;
const int DOUBLE_TYPE = 100005;
///  count+count个相同类类型的数据
void arg_cnt(int cnt, ...);
/// 使用同一数据类型规定类型，使用时【类型+一个该类型的数据】
void arg_type(int cnt, ...);
/// 测试c函数中参数在内存中的排列
void arg_test(int i, ...);
/// 规定参数都是字符串，且最后一个字符串以""截尾
void var_str(char *format, ...);

int main(int argc,char *argv[])
{
    int int_size = _INTSIZEOF(int);
    printf("int_size=%d\n", int_size);
    arg_test(0, 4);


    arg_cnt(4,1,2,3,4);
    return 0;
}

void var_str(char *format, ...)
{
    va_list list;
    va_start(list,format);

    char *ch;
    while(1)
    {
         ch = va_arg(list, char *);

         if(strcmp(ch,"") == 0)
         {
               printf("\n");
               break;
         }
         printf("%s ",ch);
     }
     va_end(list);
}

void arg_test(int i, ...)
{
    int j=0;
    va_list arg_ptr;

    va_start(arg_ptr, i);
    printf("&i = %p\n", &i);//打印参数i在堆栈中的地址
    printf("arg_ptr = %p\n", arg_ptr);
    //打印va_start之后arg_ptr地址,
    //应该比参数i的地址高sizeof(int)个字节
    //这时arg_ptr指向下一个参数的地址

    j=*((int *)arg_ptr);
    printf("%d %d\n", i, j);
    j=va_arg(arg_ptr, int);
    printf("arg_ptr = %p\n", arg_ptr);
    //打印va_arg后arg_ptr的地址
    //应该比调用va_arg前高sizeof(int)个字节
    //这时arg_ptr指向下一个参数的地址
    va_end(arg_ptr);
    printf("%d %d\n", i, j);
}

void arg_type(int cnt, ...)
{
    int arg_type = 0;
    int int_value=0;
    int i=0;
    int arg_cnt=cnt;
    char *str_value = NULL;
    va_list arg_ptr;
    va_start(arg_ptr, cnt);
    for(i = 0; i < cnt; i++)
    {
        arg_type = va_arg(arg_ptr,int);
        switch(arg_type)
        {
            case INT_TYPE:
                int_value = va_arg(arg_ptr,int);
                printf("value%d=%d\n", i+1, int_value);
                break;
            case STR_TYPE:
                str_value = va_arg(arg_ptr,char*);
                printf("value%d=%d\n", i+1, str_value);
                break;
            default:
                break;
        }
    }
}

void arg_cnt(int cnt, ...)
{
    int value=0;
    int i=0;
    int arg_cnt=cnt;
    va_list arg_ptr;
    va_start(arg_ptr, cnt);
    for(i = 0; i < cnt; i++)
    {
        value = va_arg(arg_ptr,int);
        printf("value%d=%d\n", i+1, value);
    }
}
