#include "jpeg_op.h"
#include "bf_search.h"
#include <assert.h>

const char SOF0_JPEG[2]={( char)0xFF, ( char)0XC0};
const unsigned int OFFSET_WIDTH_SOF0_START=7;
const unsigned int OFFSET_WIDTH_SOF0_END=8;

const unsigned int OFFSET_HEIGHT_SOF0_START=5;
const unsigned int OFFSET_HEIGHT_SOF0_END=6;

const char EOI_JPEG[2]={( char)0xFF, ( char)0XD9};

const char SOS_JPEG[2]={( char)0xFF, ( char)0XDA};


namespace jpeg_op {


/// 分别读取对应位置的数据
///
int getJPEGSize(const string &v_filename,unsigned &v_width,unsigned & v_height){
  struct Position * findItemPositions=NULL;

  char buffer[100];

  // 查找 SOF0的偏离距离
  findItemPositions = searchItem(
        v_filename.c_str(),
        (char*)memcpy(buffer,SOF0_JPEG,sizeof(SOF0_JPEG)),
        sizeof(SOF0_JPEG)
        );

  //查找SOF0失败
  if (findItemPositions == NULL) {
    cout<<"findItemPositions failed"<<endl;
    return -1;
  }

  //查找成功则根据定义的width height的离SOF0的偏离距离获取值
  char c_width[2];
  int ret_getw= getValue(v_filename.c_str(),c_width,2,OFFSET_WIDTH_SOF0_START+findItemPositions->start);
  if (ret_getw != 0) {
    cout<<"ret_getw failed"<<endl;

    return -1;
  }
  v_width=(c_width[0]<<8)+c_width[1];
  // v_width=(c_width[1]<<8)+c_width[0];



  char c_height[2];
  int ret_geth= getValue(v_filename.c_str(),c_height,2,OFFSET_HEIGHT_SOF0_START+findItemPositions->start);
  if (ret_geth != 0) {
    cout<<"ret_geth failed"<<endl;

    return -1;
  }
  v_height=(c_height[0]<<8)+c_height[1];
  //v_height=(c_height[1]<<8)+c_height[0];


  //printf("w:%d h:%d\n",v_width,v_height);

  return 0;

}


/// 查找SOF0位置
/// 分别根据偏移量将值写入目标值
/// 读取目标位置的值以确认是否正确写入
int setJPEGSize(const string &v_filename,unsigned &v_width,unsigned &v_height){
  struct Position * findItemPositions=NULL;

  char buffer[100];

  // 查找 SOF0的偏离距离
  findItemPositions = searchItem(
        v_filename.c_str(),
        (char*)memcpy(buffer,SOF0_JPEG,sizeof(SOF0_JPEG)),
        sizeof(SOF0_JPEG)
        );

  //查找SOF0失败
  if (findItemPositions == NULL) {
    cout<<"findItemPositions failed"<<endl;
    return -1;
  }

  char c_width[2]={(char)((v_width&0xff00)>>8),(char)(v_width&0x00ff)};
  int ret_setw= setValue(v_filename.c_str(),c_width,2,OFFSET_WIDTH_SOF0_START+findItemPositions->start);
  if (ret_setw != 0) {
    cout<<"ret_setw failed"<<endl;
    return -1;
  }

  char c_height[2]={(char)((v_height&0xff00)>>8),(char)(v_height&0x00ff)};
  int ret_seth= setValue(v_filename.c_str(),c_height,2,OFFSET_HEIGHT_SOF0_START+findItemPositions->start);
  if (ret_seth != 0) {
    cout<<"ret_seth failed"<<endl;
    return -1;
  }

  return 0;
}


/// 创建v_file_target文件,将v_file_src文件拷贝到v_file_target
/// 调用函数进行粘贴 appendJPEG
int appendJPEG(const string &v_file_target,const string &v_file_src,const string &v_file_app){


  FILE* fp_target=fopen(v_file_target.c_str(),"wb+");
  if (fp_target == NULL) {
    perror("fopen()");
    cout<<__func__<<": Fail to fopen"<<v_file_target<<endl;
    return -1;
  }

  FILE* fp_src=fopen(v_file_src.c_str(),"rb");
  if (fp_src == NULL) {
    perror("fopen()");
    cout<<__func__<<": Fail to fopen"<<v_file_src<<endl;
    return -1;
  }

  fseek(fp_src,0L,SEEK_END);
  size_t intsize=ftell(fp_src);

  fseek(fp_src,0L,SEEK_SET);

  char *buffer_src=(char*)malloc(intsize*sizeof (char));
  assert(buffer_src);

  size_t size_read_src=fread(buffer_src,sizeof (char),intsize,fp_src);
  if (size_read_src != intsize) {
    perror("fread()");
    cout<<__func__<<": Fail to fread"<<endl;
    cout<<__func__<<" size_read_src:"<<size_read_src<<endl;
    cout<<__func__<<" intsize:"<<intsize<<endl;
    free(buffer_src);
    buffer_src=NULL;
    fclose(fp_target);
    fp_target=NULL;
    fclose(fp_src);
    fp_src=NULL;
    return -1;
  }

  size_t size_write_src=fwrite(buffer_src,sizeof (char),intsize,fp_target);
  if (size_write_src != intsize) {
    perror("fwrite()");
    cout<<__func__<<": Fail to fwrite"<<endl;
    cout<<__func__<<" size_write_src:"<<size_write_src<<endl;
    cout<<__func__<<" intsize:"<<intsize<<endl;
    free(buffer_src);
    buffer_src=NULL;
    fclose(fp_target);
    fp_target=NULL;
    fclose(fp_src);
    fp_src=NULL;
    return -1;
  }

  free(buffer_src);
  buffer_src=NULL;
  fclose(fp_target);
  fp_target=NULL;
  fclose(fp_src);
  fp_src=NULL;

  return appendJPEG(v_file_target,v_file_app);

}



/// 读取SOF0信息 width height 判断两张图片是否能够拼接
/// 查看最后一个RST7l与RST0l的位置,判断RST7l>RST0l时才能正常拼接,否则会出现图片间隙
/// 清除v_file_target的结束标识,修改width height
/// 获取v_file_app的图片数据端,复制到buffer
/// 将buffer中的数据append到v_file_target末尾
/// 给v_file_target追加帧结束标识
int appendJPEG(const string &v_file_target,const string &v_file_app){
  unsigned int w_target,h_target;
  int ret_getsize_target=getJPEGSize(v_file_target,w_target,h_target);
  if (ret_getsize_target != 0) {
    cout<<__func__<<": Fail to getJPEGSize"<<v_file_target<<endl;
    return -1;
  }

  unsigned int w_app,h_app;
  int ret_getsize_app=getJPEGSize(v_file_app,w_app,h_app);
  if (ret_getsize_app != 0) {
    cout<<__func__<<": Fail to getJPEGSize"<<v_file_app<<endl;
    return -1;
  }


  if (w_target!=w_app  ) {
    cout<<__func__<<": size don't match"<<endl;
  }

  //改写target中的height
  unsigned int height_combine= h_app+h_target;
  int re_setsize=setJPEGSize(v_file_target,w_target,height_combine);
  if (re_setsize == 0) {
    cout<<"setJPEGSize succeed"<<endl;
  }
  else{
    return -1;
    cout<<"setJPEGSize failed"<<endl;
  }

  struct Position * findItemPositions=NULL;

  char buffer[100];


  // 查找target的EOI_JPEG的位置,写入数据时覆盖该位
  findItemPositions = searchItemReverse(
        v_file_target.c_str(),
        (char*)memcpy(buffer,EOI_JPEG,sizeof(EOI_JPEG)),
        sizeof(EOI_JPEG)
        );

  //查找SOF0失败
  if (findItemPositions == NULL) {
    cout<<"findItemPositions EOI_JPEG failed"<<endl;
    return -1;
  }

  long wpos_target=findItemPositions->start;
  freePosition(findItemPositions);


  // 获取需要追加的内容
  //  - 获取起始位置
  //  - 获取终止位置

  //=========================mutli ecs===================================//

  ///sos
  findItemPositions = searchItem(
        v_file_app.c_str(),
        (char*)memcpy(buffer,SOS_JPEG,sizeof(SOS_JPEG)),
        sizeof(SOS_JPEG)
        );
  //查找SOF0失败
  if (findItemPositions == NULL) {
    cout<<"findItemPositions SOS_JPEG failed"<<endl;
    return -1;
  }
  char c_component[1];
  int ret_getcomponent= getValue(v_file_app.c_str(),c_component,1,findItemPositions->start+4);
  if(ret_getcomponent != 0){
    cout<<__func__<<": Fail to ret_getcomponent"<<endl;
  }
  //  数据起始位置距起始位置的偏移量
  long offset_data_start=findItemPositions->start+5+2*c_component[0]+3;

  //=========================mutli ecs===================================//


  //  //=========================mutli scans===================================//
  //  ///组成多scan的图片,将scan前面的数据一起追加到基础数据scan的后面
  //  ///寻找包含表定义的帧
  //  findItemPositions = searchItem(
  //        v_file_app.c_str(),
  //        (char*)memcpy(buffer,SOF0_JPEG,sizeof(SOF0_JPEG)),
  //        sizeof(SOF0_JPEG)
  //        );

  //  //查找SOF0失败
  //  if (findItemPositions == NULL) {
  //    cout<<"findItemPositions SOS_JPEG failed"<<endl;
  //    return -1;
  //  }

  //  char c_component[2];
  //  int ret_getcomponent= getValue(v_file_app.c_str(),c_component,2,findItemPositions->start+2);
  //  if(ret_getcomponent != 0){
  //    cout<<__func__<<": Fail to ret_getcomponent"<<endl;
  //  }


  //  int length_sof0=(c_component[0]<<8)+c_component[1];

  //  //  //设置起始位置
  //  long offset_data_start=findItemPositions->start+2+length_sof0;
  //  //=========================mutli scans===================================//



  freePosition(findItemPositions);

  FILE *fp_app=fopen(v_file_app.c_str(),"rb");
  if(fp_app == NULL){
    perror("fopen()");
    cout<<__func__<<": Fail to fopen"<<v_file_app<<endl;
    return -1;
  }

  fseek(fp_app,0L,SEEK_END);
  long offset_data_end=ftell(fp_app);
  fseek(fp_app,0L,SEEK_SET);

  long size=offset_data_end-offset_data_start;

  char *c_data=(char*)malloc(size*sizeof(char));
  if(c_data == NULL){
    cout<<__func__<<": Fail to malloc"<<endl;
    return -1;
  }


  fseek(fp_app,offset_data_start,SEEK_SET);
  long size_read_data= fread(c_data,sizeof(char),size,fp_app);
  if(size_read_data != size){
    perror("fread()");
    cout<<__func__<<" size:"<<size
       <<" size_read_data:"<<size_read_data<<endl;

    cout<<__func__<<": Fail to fread "<<v_file_app<<endl;
    return -1;
  }
  fclose(fp_app);




  //将复制的数据写到之前的文件
  FILE *fp_target=fopen(v_file_target.c_str(),"rb+");
  if(fp_target == NULL){
    perror("fopen()");
    cout<<__func__<<": Fail to fopen"<<v_file_target<<endl;
    return -1;
  }

  fseek(fp_target,wpos_target,SEEK_SET);

//  char c_rst7[2]={(char)0xff,(char)0xd7};
//  long size_write_rst7=fwrite(c_rst7,sizeof(char),2,fp_target);



  long size_write=fwrite(c_data,sizeof(char),size,fp_target);

  if(size_write != size){
    perror("fwrite()");
    cout<<__func__<<": Fail to fwrite"<<v_file_target<<endl;
    return -1;
  }
  fclose(fp_target);

  return 0;
}





}




