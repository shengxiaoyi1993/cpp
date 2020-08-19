#include "ImageConverter.hpp"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "../lib/portable/pnm.hpp"

 ImageConverter::ImageConverter(const string&v_path,ImageType v_imagetype):
 _prgb(nullptr),_py(nullptr),_pu(nullptr),_pv(nullptr)
{
  switch ( v_imagetype ) {
    case ImageType_JPEG:{
      loadFromJPEG(v_path);
      break;
    }
    case ImageType_PPM:{
      loadFromPPM(v_path);
      break;
    }
    case ImageType_PGM:{
      loadFromPGM(v_path);
      break;
    }
    default:
    break;
  }

}

ImageConverter::~ImageConverter(){

}


int ImageConverter::saveToFile(const string&v_path,ImageType v_imagetype){
  switch ( v_imagetype ) {
    case ImageType_JPEG:{
      saveToJPEG(v_path);
      break;
    }
    case ImageType_PPM:{
      saveToPPM(v_path);
      break;
    }
    case ImageType_PGM:{
      saveToPGM(v_path);
      break;
    }
    default:
    break;
  }
  return 0;
}

int ImageConverter::loadFromPPM(const string & v_file){
  PNM::Info info;
  std::ifstream( v_file, std::ios_base::binary ) >> PNM::load( _prgb, info );
  if( true == info.valid() )
 {
  std::cout << "width   = "  << info.width ()    << std::endl;
  std::cout << "height  = "  << info.height()    << std::endl;
  std::cout << "max     = "  << info.max()       << std::endl;
  std::cout << "channel = "  << info.channel()   << std::endl;
  std::cout << "type    = "  << (int)info.type() << std::endl;
  // data contain valid information allocated by my_allocator
 }
  return 0;
}
int ImageConverter::loadFromPGM(const string & v_file){
  return 0;
}
int ImageConverter::loadFromJPEG(const string & v_file){

  return 0;
}
int ImageConverter::saveToPPM(const string & v_file) const{
  return 0;
}
int ImageConverter::saveToPGM(const string & v_file) const{
  return 0;
}
int ImageConverter::saveToJPEG(const string & v_file) const{
  return 0;
}
