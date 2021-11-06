#include <stdio.h>

#include <string.h>

#include <stdlib.h>
#include "bf_search.h"
#include "jpeg_op.h"
#include <string>



// 全局变量：数据文件

const char FILE_NAME[]  = "/home/sxy/Desktop/20201230/rs_flmg/main/out.jpg";

const char TARGET_NAME[]  = "/home/sxy/Desktop/20201230/rs_flmg/main/out_target.jpg";
const char NEW_TARGET_NAME[]  = "/home/sxy/Desktop/20201230/rs_flmg/main/out_target_new.jpg";


void test_rm_rst();


int main(int argc, char *argv[])

{

    unsigned w;
    unsigned h;

    int re_getsize=jpeg_op::getJPEGSize(std::string(FILE_NAME),w,h);
    if (re_getsize == 0) {
      cout<<"getJPEGSize succeed"<<endl;
    }
    else{
      cout<<"getJPEGSize failed"<<endl;
      return 0;
    }

    printf("w:%d h:%d\n",w,h);

//    int ret_app= jpeg_op::appendJPEG(std::string(TARGET_NAME),std::string(FILE_NAME));
//    if (ret_app == 0) {
//      cout<<"appendJPEG succeed"<<endl;
//    }
//    else{
//      return 0;
//      cout<<"appendJPEG failed"<<endl;
//    }

    int ret_new= jpeg_op::appendJPEG(std::string(TARGET_NAME),
                                     std::string(FILE_NAME),
                                     std::string(FILE_NAME));
    if (ret_new == 0) {
      cout<<"appendJPEG succeed"<<endl;
    }
    else{
      cout<<"appendJPEG failed"<<endl;
      return 0;
    }



}



//! test
//! 测试在scan中删除一个/若干RST使RST乱序,观察其是否能正常打开
//! 1. 查寻出RST的顺序,决定删除哪个RST
//! 2. 将数据拷贝到另一文件,但是拷贝欲删除的文件
//!
const char RST0[2]={( char)0xFF, ( char)0XD0};
const char RST1[2]={( char)0xFF, ( char)0XD1};

void test_rm_rst(){
  string v_filename="/home/sxy/Desktop/jpeg_2_128.jpg";
  struct Position * findItemPositions=NULL;
  struct Position * p_op=NULL;
  struct Position * findItemPositions_rst1=NULL;

  char buffer[100];

  // 查找 RST0的偏离距离
  findItemPositions = searchItem(
        v_filename.c_str(),
        (char*)memcpy(buffer,RST0,sizeof(RST0)),
        sizeof(RST0)
        );
  findItemPositions_rst1 = searchItem(
        v_filename.c_str(),
        (char*)memcpy(buffer,RST1,sizeof(RST1)),
        sizeof(RST1)
        );

  //查找 RST0 失败
  if (findItemPositions == NULL) {
    cout<<"findItemPositions failed"<<endl;
    return ;
  }

  p_op=findItemPositions;
  string name_image;
  int index=0;
  while(p_op!=NULL){
    name_image=std::to_string(index)+"_rm.jpg";
    //    cout<<"start"<<p_op->start<<endl;
    //    cout<<"end:"<<p_op->end<<endl;
    //    if (p_op->next != NULL) {
    //      cout<<"interval:"<<p_op->end-p_op->next->end<<endl;
    //    }
    cout<<"interval rst01:"<<findItemPositions_rst1->start-p_op->end<<endl;
    rmAndCopy(name_image.c_str(),v_filename.c_str(),p_op->start,findItemPositions_rst1->start-1);
    p_op=p_op->next;
    findItemPositions_rst1=findItemPositions_rst1->next;
    index++;
    if (index>10) {
      return;
    }
  }


}
