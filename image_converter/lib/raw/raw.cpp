#include "raw.h"
#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstring>
#include "bayer_convert.h"
#include "../../lib/common/string_manipulation.hpp"

//#define DEBUG_RAW

RAW::RAW(const string &v_file,
         RAW::RAWType v_type,
         unsigned v_total_bits,
         unsigned int v_valid_bits,
         unsigned int  v_width,
         unsigned int v_height)
  :_type(v_type),
    _total_bits(v_total_bits),
    _valid_bits(v_valid_bits),
    _height(v_height),
    _width(v_width),
    _pdata(nullptr),
    _file(v_file)
{
  if(!(_type == RAWType_RGGB || _type==RAWType_gray)){
    throw string(__FUNCTION__)+string("Error: RAWType is not supported ");
  }

  if(!((_total_bits==8 || _total_bits==16) && _valid_bits<=_total_bits )){
    throw string(__FUNCTION__)+string("Error:bits wrong ");
  }

  int ret_load=loadFromFile(_file,_total_bits,_valid_bits,_width,_height);
  if(ret_load != 0){
    throw string(__FUNCTION__)+string("Error:Fail to load");
  }
  #ifdef DEBUG_RAW
  cout<<"[succeed]:"<<"Load Image:"<<v_file<<endl;
  #endif
}


RAW::~RAW(){
  delete [] _pdata;
}


int RAW::loadFromFile(
    const string &v_file,
    unsigned v_total_bits,
    unsigned int v_valid_bits,
    unsigned int v_width ,
    unsigned int v_height
    ){
  (void)v_valid_bits;
  ifstream infile(v_file,ios::in);   //输入流
  if(!infile.is_open()){
    cout<<"open failed"<<endl;
    return -1;
  }
  unsigned size=v_width*v_height;
  std::string str((std::istreambuf_iterator<char>(infile)),
                  std::istreambuf_iterator<char>());

  if(size*v_total_bits/8>str.size()){
    return -1;
  }

  _pdata = new unsigned short[size];


  //get data from buffer
  //assume that valid data is at first
  //assume
  //  if _total_bits == 8 ,the data should
  //  if _total_bits == 16 ,the data should copy directly

  if(v_total_bits == 8){
    for(unsigned i=0;i<size;i++){
      _pdata[i]= static_cast<unsigned short>(str[i]);
    }
  }
  else if(v_total_bits == 16){
    memcpy(_pdata,str.c_str(),size*sizeof (unsigned short));
    for(size_t i=0;i<size;i++){
      _pdata[i]=static_cast<unsigned short>(_pdata[i]<<8)
      |static_cast<unsigned short>(_pdata[i]>>8);
    }
  }
  else{
    return -1;
  }
  return 0;

}

int RAW::saveToFile(const string &v_file,int v_bits) const{

  if(v_bits == 8){
    unsigned buffersize= _width*_height;
    unsigned char* pdata_tmp=new unsigned char[buffersize];
    for(unsigned i=0;i<buffersize;i++){
      pdata_tmp[i]=static_cast<unsigned char>(_pdata[i]);
    }
    {
      ofstream outpufile(v_file,ios::binary);
      outpufile.write(static_cast<const char*>((char*)pdata_tmp),buffersize);
      outpufile.close();
    }
    delete []  pdata_tmp;
    pdata_tmp=nullptr;
  }
  else if (v_bits == 16){
    unsigned buffersize= _width*_height*2;
     char* pdata_tmp=new  char[buffersize];
    for(unsigned i=0;i<buffersize;i++){
      if(i%2==0){
        pdata_tmp[i]=static_cast< char>(_pdata[i/2]>>8);
      }
      else{
        pdata_tmp[i]=static_cast< char>(_pdata[i/2]);
      }
    }
    ofstream outpufile(v_file,ios::binary);
    outpufile.write(pdata_tmp,buffersize);
    outpufile.close();
  }
  else{
    throw string(__PRETTY_FUNCTION__)+string("Error:not support");
  }

#ifdef DEBUG_RAW
cout<<"[succeed]:"<<"Save Raw Image:"<<v_file<<endl;
#endif
  return 0;

}

unsigned short * RAW::getRGBData(unsigned int &v_width,unsigned int &v_height){
  if(_type != RAWType_RGGB){
    if(_type == RAWType_gray){
      cout<<"RAWType_gray only provide gray data"<<endl;
    }
    else{
      cout<<"RAWType not support"<<endl;
    }
    return nullptr;
  }

  unsigned short *bayer_dst_r = new unsigned short[_width*_height];
  unsigned short *bayer_dst_g= new unsigned short[_width*_height];
  unsigned short *bayer_dst_b= new unsigned short[_width*_height];
  unsigned short *bayer_dst_rgb= new unsigned short[_width*_height*3];

  bayer_cfa_7x7(_pdata,_width,_height,bayer_dst_r,bayer_dst_g,bayer_dst_b);
  for(unsigned i=0;i<_width*_height;i++){
    bayer_dst_rgb[3*i  ]=bayer_dst_r[i];
    bayer_dst_rgb[3*i+1]=bayer_dst_g[i];
    bayer_dst_rgb[3*i+2]=bayer_dst_b[i];
  }
  unsigned  offset=(16-_valid_bits);

  for(unsigned i=0;i<_width*_height*3;i++){
    bayer_dst_rgb[i]=static_cast<unsigned short>(bayer_dst_rgb[i]<<offset);
  }

  delete []  bayer_dst_r;
  bayer_dst_r=nullptr;
  delete []  bayer_dst_g;
  bayer_dst_g=nullptr;
  delete []  bayer_dst_b;
  bayer_dst_b=nullptr;
  v_width=_width;
  v_height=_height;
  return bayer_dst_rgb;

}


unsigned short * RAW::getGaryData(unsigned int &v_width, unsigned int &v_height){
  if(_type != RAWType_RGGB || _type != RAWType_gray){
    cout<<"RAWType not support"<<endl;
    return nullptr;
  }
  unsigned int size=_width*_height;
  unsigned short *pgray = new unsigned short[size];

  if(_type == RAWType_RGGB ){
   unsigned short * prgb= getRGBData(v_width,v_height);
   if(prgb != nullptr){
     for(size_t i=0;i<size;i++){
       pgray[i]=static_cast<unsigned short>(prgb[i*3]*0.3+prgb[i*3+1]*0.59+prgb[i*3+2]*0.11);
     }
   }
   else{
     delete []pgray;
     pgray = nullptr;
   }
  }
  else {
    memcpy(pgray,_pdata,sizeof (unsigned short)*size);
  }
  return pgray;




}
