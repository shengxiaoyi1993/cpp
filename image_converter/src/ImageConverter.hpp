#ifndef IMAGECONVERTER_HPP
#define IMAGECONVERTER_HPP

#include <iostream>

using namespace std;

enum ImageType{
  ImageType_JPEG=0,
  ImageType_PPM,
  ImageType_PGM
};

class ImageConverter
{
public:
  explicit ImageConverter(const string& v_path,ImageType v_imagetype);
  ~ImageConverter();
  int saveToFile(const string&v_path,ImageType v_imagetype);
  int loadFromPPM(const string & v_file);
  int loadFromPGM(const string & v_file);
  int loadFromJPEG(const string & v_file);
  int saveToPPM(const string & v_file) const;
  int saveToPGM(const string & v_file) const;
  int saveToJPEG(const string & v_file) const;

private:
  short* _pr;
  short* _pg;
  short* _pb;
  short* _prgb;
  short* _py;
  short* _pu;
  short* _pv;

};


#endif
