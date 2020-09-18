#include "ImageConverter.hpp"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "pnm.h"
#include "jpge.h"
#include "jpgd.h"



ImageConverter::ImageConverter(const string&v_path,ImageType v_imagetype):
  _pimagebufer(nullptr)
{

  switch ( v_imagetype ) {
    case ImageType_JPEG:{
      loadFromJPEG(v_path);
      break;
    }
    case ImageType_PNM:{
      loadFromPNM(v_path);

      break;
    }
    default:
      break;
  }

}


ImageConverter::ImageConverter(const string& v_path,
                               ImageType v_imagetype,
                               unsigned int v_channels,
                               unsigned v_total_bits,
                               unsigned int v_valid_bits,
                               unsigned int v_width,
                               unsigned int v_height
                               ):
  _pimagebufer(new ImageBuffer(v_channels,v_total_bits,v_valid_bits,v_width,v_height))
{
  if(v_imagetype == ImageType_RAW){
    loadFromRaw(v_path,RAW::RAWType_RGGB,v_total_bits,v_valid_bits,v_width,v_height);
  }
  else{
    throw string(__PRETTY_FUNCTION__)+"Error:wrong Constructor, only support RAW,please use another Constructor";
  }

  if(v_channels != 3){
    throw string(__PRETTY_FUNCTION__)+"Error:only support RAW,3 channels";
  }


}

ImageConverter::~ImageConverter(){
  delete  _pimagebufer;
}





int ImageConverter::loadFromJPEG(const string & v_file){

  int width;
  int height;
  int actual_comps;
  int req_comps=3;
  unsigned char* pdata= jpgd::decompress_jpeg_image_from_file(v_file.c_str(),
                                                              &width,
                                                              &height,
                                                              &actual_comps,
                                                              req_comps
                                                              );
  if(pdata == nullptr){
    return -1;
  }else
  {
    cout<<"succeed to load jpg"<<endl;
  }

  _pimagebufer=new ImageBuffer(
        actual_comps,
        8,
        16,
        width,
        height);

  unsigned int size=_pimagebufer->_width*_pimagebufer->_height*_pimagebufer->_channels;
  _pimagebufer->_pdata=new unsigned short[size];
  for(size_t i=0;i<size;i++){
        _pimagebufer->_pdata[i]=static_cast<unsigned short>(static_cast<unsigned short>(pdata[i])<<8);
  }

  return 0;
}


int ImageConverter::saveToPNM(const string & v_file, PNM::MagicNumber v_mn,unsigned v_range) const{
  PNM::saveDataToFile(v_file,
                      PNM::DataType::DataType_rgb,
                      v_mn,
                      _pimagebufer->_pdata,
                      _pimagebufer->_width,
                      _pimagebufer->_height,
                      v_range
                      );

  return 0;
}

int ImageConverter::saveToJPEG(const string & v_file) const{
  unsigned int size=_pimagebufer->_width*_pimagebufer->_height*_pimagebufer->_channels;

  unsigned char* pdata=new unsigned char[size];
  for(size_t i=0;i<size;i++){
    pdata[i]=static_cast<unsigned char>(_pimagebufer->_pdata[i]>>8);
  }


  jpge::compress_image_to_jpeg_file(v_file.c_str(),
                              _pimagebufer->_width,
                              _pimagebufer->_height,
                              _pimagebufer->_channels,
                              pdata
                              );
  delete []pdata;


  return 0;
}
int ImageConverter::loadFromPNM(const string & v_file){
  PNM tmppnm(v_file);

  unsigned int ch;
  switch (tmppnm._magic_number) {
    case 5:{
      ch=1;
      break;
    }
    case 6:{
      ch=3;
      break;
    }
    default:
      throw string(__FUNCTION__)+string("not support");
      //          break;
  }
  _pimagebufer=new ImageBuffer( tmppnm._data,
                                ch,
                                tmppnm._range,
                                tmppnm._width,
                                tmppnm._height);
  return 0;

}

int ImageConverter::loadFromOutputFile(const string & v_file){
  throw string(__FUNCTION__)+" not support";
  return 0;
}


int ImageConverter::loadFromRaw(const string & v_file,
                                RAW::RAWType v_type,
                                unsigned v_total_bits,
                                unsigned int v_valid_bits,
                                unsigned int v_height,
                                unsigned int v_width){
  RAW  rawdata(v_file,v_type,v_total_bits,v_valid_bits,v_width,v_height);
  unsigned int width;
  unsigned int height;
  unsigned short *prgb=rawdata.getRGBData(width,height);
  memcpy(_pimagebufer->_pdata,prgb,sizeof (unsigned short)*_pimagebufer->_width*_pimagebufer->_height*3);
  delete [] prgb;
  return 0;

}

int ImageConverter::saveToOutputFile(const string & v_file) const{
  throw string(__FUNCTION__)+" not support";
}
