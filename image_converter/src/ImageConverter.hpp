#ifndef IMAGECONVERTER_HPP
#define IMAGECONVERTER_HPP

#include <iostream>

using namespace std;

enum ImageType{
  ImageType_JPEG=0,
  ImageType_PNM,
  ImageType_RAW,
  ImageType_OUTPUT
};

class ImageBuffer{
public:
  /**
   * @brief 1 or 3 _channels quanentity of channels to form the data
   * 1 channel :gray or single color channel
   */
  unsigned int _channels;
  /**
   * @brief integer >0 And <=16 _valid image data is save in  unsigned short ,
   * valid bits is at first bits of pixel
   */
  unsigned int _valid;
  /**
   * @brief _pdata data is saved in this pointer
   */
  unsigned short * _pdata;

  unsigned int _width;
  unsigned int _height;

  explicit ImageBuffer(unsigned int v_channels,
              unsigned int v_valid,
              unsigned int v_width,
              unsigned int v_height):
    _pdata(nullptr),_channels(v_channels),
    _valid(v_valid),_width(v_width),_height(v_height)
  {
    if(!(_channels == 1 || _channels == 3)&&(v_valid>0&&v_valid<=16)){
      throw string(__FUNCTION__)+":wrong param";
    }

    _pdata=new unsigned short[v_width*v_height*v_channels];

  }
  ~ImageBuffer(){
    delete[] _pdata;

  }



};

class ImageConverter
{
public:
  explicit ImageConverter(const string& v_path,ImageType v_imagetype);
  ~ImageConverter();
  int saveToFile(const string&v_path,ImageType v_imagetype);
  int loadFromPNM(const string & v_file);
  int loadFromOutputFile(const string & v_file);
  int loadFromRaw(const string & v_file);

  int loadFromPPM(const string & v_file);
  int loadFromPGM(const string & v_file);
  int loadFromJPEG(const string & v_file);
  int saveToPPM(const string & v_file) const;
  int saveToPGM(const string & v_file) const;
  int saveToJPEG(const string & v_file) const;

private:
  ImageBuffer *_pimagebufer;


};


#endif
