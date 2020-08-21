#include "ImageConverter.hpp"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "../lib/pnm/pnm.h"

 ImageConverter::ImageConverter(const string&v_path,ImageType v_imagetype):
   _pimagebufer(nullptr)
{

  switch ( v_imagetype ) {
    case ImageType_JPEG:{
      loadFromJPEG(v_path);
      break;
    }
    case ImageType_PNM:{
      PNM tmppnm(v_path);
      _pimagebufer=new ImageBuffer(tmppnm._range,tmppnm._range,tmppnm._width,tmppnm._height);

      loadFromPPM(v_path);
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
    case ImageType_PNM:{
      saveToPPM(v_path);
      break;
    }

    default:
    break;
  }
  return 0;
}

int ImageConverter::loadFromPPM(const string & v_file){

  return 0;
}
int ImageConverter::loadFromPGM(const string & v_file){
  throw string(__FUNCTION__)+" not support";
  return 0;
}
int ImageConverter::loadFromJPEG(const string & v_file){
  throw string(__FUNCTION__)+" not support";

  return 0;
}
int ImageConverter::saveToPPM(const string & v_file) const{
  throw string(__FUNCTION__)+" not support";

  return 0;
}
int ImageConverter::saveToPGM(const string & v_file) const{
  throw string(__FUNCTION__)+" not support";

  return 0;
}
int ImageConverter::saveToJPEG(const string & v_file) const{
  throw string(__FUNCTION__)+" not support";

  return 0;
}
int loadFromPNM(const string & v_file){
  throw string(__FUNCTION__)+" not support";
  return 0;


}

int loadFromOutputFile(const string & v_file){
  throw string(__FUNCTION__)+" not support";
  return 0;
}

int loadFromRaw(const string & v_file){
  throw string(__FUNCTION__)+" not support";
  return 0;
}
