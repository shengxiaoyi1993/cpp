#include<iostream>
#include "export.h"
#include<stdarg.h>

using namespace std;
void print1(){cout<<1<<endl;}
void print2(){cout<<2<<endl;}


int findMax(int n,...)
{
    va_list arg;//相当于char *p
    int i = 0,M = 0;
    va_start(arg, n);//相当于char *p = &n
    for(i=0; i<n; i++)
    {
        int m = va_arg(arg,int);
        if(m > M)
        {
            M = m;
        }
    }
    return M;
    va_end(arg);//相当于p = NULL
}

int getNumList(const char* v_data,int num[]){
  va_list arg;
}

 int main() {
//   Export ff;
//   ff.setCB(print1);
//   ff.print();

//   Export ff1;
//   ff1.setCB(print2);
//   ff1.print();
//   ff.print();


   const char* str="1 0 0 0ac 0b8 0bc 0b8 0c0 0bc 0c0 0d0 0c0 0c4";

   int nums[256];
   int i=0;
   while (i<256) {
     sscanf(str,"%x",&nums[i]);
     printf("%d: 0x%x\n",i,nums[i]);
     fflush(stdout);
     i++;
   }



//   int num_size=getNumList(str,nums);
//   for(int i=0;i<num_size;i++){
//     printf("%d: 0x%x",i,nums[i]);
//   }


  return 0;
}
