#ifndef EXPORT_H
#define EXPORT_H

#include <vector>
#include <iostream>



using namespace std;
typedef void(*PRINT)();



class Export{
public:
  Export(){

  }
  ~Export(){

  }
  void print(){
    if(pprint == nullptr){
      cout<<"pprint is null"<<endl;
    }
    else{
      pprint();
    }
  }
  void setCB(PRINT v_cb ){
    pprint =v_cb;
  }

private:
  //若回调函数为static 类型，则每一个类的回调函数是同一个
  //若回调函数为不是static类型，则不同实例化的对象可以设置不同的回调函数
   PRINT pprint;


};

#endif
