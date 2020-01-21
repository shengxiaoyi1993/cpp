
#include "basic.h"
#include <iostream>
#include <fstream>


using namespace std;

namespace basic{
  int getStringFromFile(std::string dirpath,char** content){
      filebuf *pbuf;
      ifstream filestr;
      long size;
      // 要读入整个文件，必须采用二进制打开
      filestr.open (dirpath.c_str(), ios::binary);
      // 获取filestr对应buffer对象的指针
      pbuf=filestr.rdbuf();

      // 调用buffer对象方法获取文件大小
      size=pbuf->pubseekoff (0,ios::end,ios::in);
      pbuf->pubseekpos (0,ios::in);

      if(size<=0){
          return -1;
      }
      cout<<size<<endl;
      // 分配内存空间
      *content=new char[size];

      // 获取文件内容
      pbuf->sgetn (*content,size);

      filestr.close();
      
      return 0;
  }
}
