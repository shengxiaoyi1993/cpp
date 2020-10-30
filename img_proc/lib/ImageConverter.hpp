#ifndef IMAGECONVERTER_HPP
#define IMAGECONVERTER_HPP

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "pnm.h"
#include "raw.h"


using namespace std;

enum ImageType{
  ImageType_JPEG=0,
  ImageType_PNM,
  ImageType_RAW,
  ImageType_OUTPUT
};

//class to save data and information of image
//this class should be initialized with correct params,otherwise Exception will be thrown out
class ImageBuffer{
public:
  /**
   * @brief 1 or 3 _channels quanentity of channels to form the data
   * 1 channel :gray or single color image
   * 3 channel :rgb image
   */
  unsigned int _channels;
  /**
   * @brief integer >0 And <=16 ;_valid image data is save in  [unsigned short] ,
   * valid bits is at first bits of pixel
   */
  unsigned int _valid;
  /**
   * @brief _total: only use to support raw image
   * when data is saved in file, one pix channel occupys how many bits
   */
  unsigned int _total;

  /**
   * @brief _pdata data is saved in this pointer
   */
  unsigned short * _pdata;


  unsigned int _width;
  unsigned int _height;


  explicit ImageBuffer(unsigned int v_channels,
                       unsigned int _total,
                       unsigned int v_valid,
                       unsigned int v_width,
                       unsigned int v_height):
    _pdata(nullptr),_channels(v_channels),_total(v_valid),
    _valid(v_valid),_width(v_width),_height(v_height)
  {
    if(!(_channels == 1 || _channels == 3)&&(v_valid>0&&v_valid<=16)){
      throw string(__FUNCTION__)+":wrong param";
    }

    _pdata=new unsigned short[v_width*v_height*v_channels];

  }

  explicit ImageBuffer(
      unsigned short * v_pdata,
      unsigned int v_channels,
      unsigned int v_valid,
      unsigned int v_width,
      unsigned int v_height):
    _pdata(nullptr),_channels(v_channels),_total(v_valid),
    _valid(v_valid),_width(v_width),_height(v_height)
  {
    if(!(_channels == 1 || _channels == 3)&&(v_valid>0&&v_valid<=16)){
      throw string(__FUNCTION__)+":wrong param";
    }

    _pdata=new unsigned short[v_width*v_height*v_channels];
    memcpy(_pdata,v_pdata,sizeof (unsigned short)*v_width*v_height*v_channels);

  }


  ~ImageBuffer(){
    delete[] _pdata;

  }



};

class ImageConverter
{
public:
  explicit ImageConverter(const string& v_path,ImageType v_imagetype);
  /**
   * @brief ImageConverter  only support raw data,for file of raw lack information
   * @param v_path
   * @param v_imagetype
   * @param v_channels
   * @param v_total_bits
   * @param v_valid_bits
   * @param v_width
   * @param v_height
   */
  explicit ImageConverter(const string& v_path,
                          ImageType v_imagetype,
                          unsigned int v_channels,
                          unsigned v_total_bits,
                          unsigned int v_valid_bits,
                          unsigned int v_width,
                          unsigned int v_height
                          );

  ~ImageConverter();

  //load
  int loadFromPNM(const string & v_file);
  int loadFromOutputFile(const string & v_file);
  int loadFromRaw(const string & v_file,
                  RAW::RAWType v_type,
                  unsigned v_total_bits,
                  unsigned int v_valid_bits,
                  unsigned int v_width,
                  unsigned int  v_height);
  int loadFromJPEG(const string & v_file);

  //save
  int saveToPNM(const string & v_file, PNM::MagicNumber v_mn,unsigned v_range) const;
  int saveToJPEG(const string & v_file) const;
  int saveToOutputFile(const string & v_file) const;


public:
  ImageBuffer *_pimagebufer;


};


#endif
