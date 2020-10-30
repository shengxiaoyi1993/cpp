#ifndef RAW_H
#define RAW_H

#include <iostream>
#include <string>

using namespace  std;


class RAW{

public:
  //RAWType
  //1. RGGB is only type supported now,as 226/178 ouput
  enum RAWType {
    RAWType_RGGB=0,
    RAWType_BGGR,
    RAWType_GBRG,
    RAWType_GRBG,
    RAWType_gray
  };

  enum ConvertType{
    // Adjacent_Interpolation=0,
    ConvertType_A=0,
    // Boundary_Gradient_Interpolation,
    ConvertType_B,
    // Hamilton_Interpolation
    ConvertType_H
  }ConvertType;

  /**
 * RAW constructor to initailize the class
 * 1. initailize the params. For file of rawimage lack of information, we need
 * input the params mannully
 * 2. load data from file
 * @param v_file       path of src image;
 * @param v_type       type
 * @param v_total_bits bits of pix occupaied when save in v_file
 * @param v_valid_bits valid_bits per pix,it occupy part or all bits of total_bits;
 *                     assume that valid pix always occupy the low space of bits
 * @param v_width      width of image
 * @param v_height     height of image
 */
  RAW(
      const string &v_file,
      RAWType v_type,
      unsigned v_total_bits,
      unsigned int v_valid_bits,
      unsigned int v_width,
      unsigned int  v_height);
  ~RAW();


private:
  //type of rawimage
  //only suport RAWType_RGGB and RAWType_gray
  RAWType _type;
  /**
     * @brief _total_bits bits per pix save in file
     */
  unsigned int _total_bits;
  unsigned int _valid_bits;
  unsigned int _height;
  unsigned int _width;
  /**
     * @brief _pdata the valid bits is at right
     */
  unsigned short* _pdata;
  string _file;

  //load from file
  int loadFromFile(
      const string &v_file,
      unsigned v_total_bits,
      unsigned int v_valid_bits,
      unsigned int v_width ,
      unsigned int v_height);

public:


  //save to file
  int saveToFile(const string &v_file,int v_bits) const;

  /**
     * @brief getRGBData get rgb dataData(3 channels) ,with size of v_width and v_height
     * @return Not nullptr:succeed;nullptr:fail to get data
     * @note  after use this function ,return value should be free as `delete [] pdata`
     */
  unsigned short * getRGBData(unsigned int &v_width,unsigned int &v_height);
  /**
     * @brief getGaryData to get gray data of raw image,with size of v_width and v_height
     * @return Not nullptr:succeed;nullptr:fail to get data
     * @note  after use this function ,return value should be free as `delete [] pdata`
     * @return
     */
  unsigned short * getGaryData(unsigned int &v_width,unsigned int &v_height);



};



#endif // RAW_H
