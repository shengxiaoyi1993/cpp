#include"max.h"
#include<iostream>

using namespace std;

int main(){
  auto max_int=::max(45,78);
  cout<<"::max(45,78):"<<::max(45,78)<<endl;
  cout<<"::max(\"abc\",\"123\"):"<<::max("abc","123")<<endl;
  cout<<"::max(12.6,67.6):"<<::max(12.6,67.6)<<endl;

  char* str0="asd";
  char* str1="agf";
  cout<<"::max(12.6,67.6):"<<::max(str1,str0)<<endl;
  char v0[]="asd";
  char v1[]="agf";
  cout<<"::max(12.6,67.6):"<<::max(v0,v1)<<endl;


  return 0;
}
