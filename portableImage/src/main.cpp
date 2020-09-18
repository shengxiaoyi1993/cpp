#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "pnm/pnm.h"

//tset case
//to test the convertion of pnm image
//1. load image (PGM-BI PPM-BI 2~16 bits)
//2. save image (PGM-BI PPM-BI 2~16 bits)
void test_pnmconvert();
void test_loadP4();
void test_saveP4();
void use_getimage();

using namespace std;
int main() {

  // test_pnmconvert();
//      test_loadP4();
  //  test_saveP4();
  use_getimage();

  return 0;
}

void use_getimage(){
  //读取图片 4096*4096 rgb unsigned char
  //转换成图片 unsigned short
  //保存成图片

  string path_buffer="/home/sxy/Share/tftp/imagerecord_0_7.txt";
  string path_buffer_save="/home/sxy/Share/tftp/imagerecord_0_7.ppm";


  ifstream infile(path_buffer,ios::in);   //输入流
  //load all data from file
  std::string str((std::istreambuf_iterator<char>(infile)),
                  std::istreambuf_iterator<char>());

std::cout << "size_buffer:"<< str.size()<< '\n';
if(str.size()<4096*4096*3){
  std::cout << "imagebuffer is broken" << '\n';
}
else{
  unsigned short *pdata=new unsigned short[4096*4096*3];
  for (size_t i = 0; i < 4096*4096*3; i++) {
    pdata[i]=static_cast<unsigned short>(str[i]);
    pdata[i]<<=8;
    // pdata[i]=pdata[i]<255?pdata[i]:255;
  }

// //以16个元素作为一个单元进行反转
//   for (size_t i = 0; i < 4096*4096*3/16; i++) {
//     for (size_t j = 0; j < 16/2; j++) {
//       unsigned short tmp=pdata[i*16+16-j-1];
//       pdata[i*16+16-j-1]=pdata[i*16+j];
//       pdata[i*16+j]=tmp;
//     }
//     // pdata[i]=pdata[i]<255?pdata[i]:255;
//   }



  PNM::saveDataToFile(path_buffer_save,PNM::DataType_rgb,PNM::MagicNumber_p6,
                      pdata,4096,4096,255);

}




}


void test_loadP4(){
  try {
    string path_p4="../resources/pbm_bi_from_gimp.pbm";
    string path_gray_fromp4="../resources/pgm_8_bi_fromp4.pgm";
    string path_p4_fromp4="../resources/p4_fromp4.pbm";

    PNM pnm_p4(path_p4);
    PNM::saveDataToFile(path_gray_fromp4,PNM::DataType_gray,PNM::MagicNumber_p5,
                        pnm_p4._data,pnm_p4._width,pnm_p4._height,255);
    pnm_p4.saveToFile(path_p4_fromp4,PNM::MagicNumber_p4,255);
  } catch (string msg) {
    cout<<"msg:"<<msg<<endl;
  }

}

void test_saveP4(){
  try {
    string path_p6="../resources/ppm_8_bi.ppm";

    string path_p6_16="../resources/ppm_16_bi.ppm";
    string path_p5="../resources/pgm_8_bi.pgm";
    string path_p4="../resources/pbm_bi.pbm";

    string path_p4_fromp6="../resources/p4_fromp6.pbm";
    string path_p4_fromp5="../resources/p4_fromp5.pbm";
    string path_p4_fromp4="../resources/p4_fromp4.pbm";


    PNM pnm_p6(path_p6);
    pnm_p6.saveToFile(path_p5,PNM::MagicNumber_p5,255);
    cout<<"pnm_p6.saveToFile(path_p5,PNM::MagicNumber_p5,255)"<<endl;
    pnm_p6.saveToFile(path_p4,PNM::MagicNumber_p4,255);
    cout<<"pnm_p6.saveToFile(path_p4,PNM::MagicNumber_p4,255)"<<endl;
    pnm_p6.saveToFile(path_p6_16,PNM::MagicNumber_p6,65535);
    cout<<"pnm_p6.saveToFile(path_p6_16,PNM::MagicNumber_p6,65535)"<<endl;

    PNM pnm_p5(path_p5);
    pnm_p5.saveToFile(path_p4_fromp5,PNM::MagicNumber_p4,255);
    cout<<"pnm_p5.saveToFile(path_p4_fromp5,PNM::MagicNumber_p4,255)"<<endl;

    PNM pnm_p4(path_p4);
    pnm_p4.saveToFile(path_p4_fromp4,PNM::MagicNumber_p4,255);
    cout<<"pnm_p4.saveToFile(path_p4_fromp4,PNM::MagicNumber_p4,255)"<<endl;


  } catch (string msg) {
    cout<<"msg:"<<msg<<endl;

  }

}



//v_dirpath must has '/' ar end
string getPath0(const string & v_dirpath,const string &v_type,int v_bits){
  return v_dirpath+v_type+"_"+PNM::stringFromNumber(v_bits)+"_init."+v_type;
}
string getPath1(const string & v_dirpath,const string &v_type,int v_bits,
                const string &v_type_src,int bits_src){
  return v_dirpath+v_type+"_"+PNM::stringFromNumber(v_bits)+"_from_"
      +v_type_src+"_"+PNM::stringFromNumber(bits_src)+"."+v_type;
}
unsigned getRange(unsigned int v_num){
  unsigned ret=1;
  for (size_t i = 0; i < v_num; i++) {
    ret*=2;
  }
  return (ret-1);
}
void test_pnmconvert(){
  vector<int> list_type(3);
  list_type[0]=5;
  list_type[1]=6;
  list_type[2]=4;

  vector<string> list_type_name(3);
  list_type_name[0]="pgm";
  list_type_name[1]="ppm";
  list_type_name[2]="pbm";

  vector<int> list_bits;
  for (size_t i = 2; i <=16; i++) {
    list_bits.push_back(i);
    /* code */
  }

  try{
    //1. genetate all kinds of image firstly from one image
    //"[type]_[bits]_init.[type]"
    //2. from all kinds of image generate all kinds of image again
    //"[type]_[bits]_from_[type2]_[bits2].[type]"

    //1
    string path_dir="../../test_result/";
    string path_image="../../resources/ppm_8_bi.ppm";
    PNM pnm_init(path_image);
    for (size_t i = 0; i < list_type.size(); i++) {
      for (size_t j = 0; j < list_bits.size(); j++) {
        string tmppnm=getPath0(path_dir,list_type_name[i],list_bits[j]);
        pnm_init.saveToFile(tmppnm,
                            (PNM::MagicNumber)list_type[i],getRange(list_bits[j]));

        //2
        PNM pnm_tmp(tmppnm);
        for (size_t k = 0; k < list_type.size(); k++) {
          for (size_t l = 0; l < list_bits.size(); l++) {
            string tmppnm_from=getPath1(path_dir,list_type_name[k],list_bits[l],
                                        list_type_name[i],list_bits[j]
                                        );
            pnm_tmp.saveToFile(tmppnm_from,
                               (PNM::MagicNumber)list_type[k],getRange(list_bits[l]));
          }
        }
      }
    }

    cout<<"[end]:result is saved in "<<path_dir <<endl;


  }
  catch (string err_msg) {
    cout<<"err_msg:"<<err_msg<<endl;

  }
  return;






}
