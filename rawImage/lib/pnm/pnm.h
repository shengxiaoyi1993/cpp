#ifndef PNM_H
#define PNM_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;





class PNM
{
  //===================declare=====================//
public:

//the type of image PNM standard constains
//1. divide by the form of data when saved in file ,ASCII or Binary
//   and the DataType it constains,binary,gray or rgb
//  MagicNumber_none:contain nothing
//  MagicNumber_p1:ASCII binary
//  MagicNumber_p2:ASCII gray
//  MagicNumber_p3:ASCII rgb
//  MagicNumber_p4:Binary binary
//  MagicNumber_p5:Binary gray
//  MagicNumber_p6:Binary rgb
  enum MagicNumber{
    MagicNumber_none=0,
    MagicNumber_p1,
    MagicNumber_p2,
    MagicNumber_p3,
    MagicNumber_p4,
    MagicNumber_p5,
    MagicNumber_p6
  };

//the type of data how data from image is saved in buffer of this class
//1. used when save to local file
//2. can be got from MagicNumber
//   DataType_binary:MagicNumber_p1 MagicNumber_p4 1 channels
//   DataType_gray:MagicNumber_p2 MagicNumber_p5   1 channels
//   DataType_rgb:MagicNumber_p3 MagicNumber_p6    3 channels
  enum DataType{
    DataType_binary=1,
    DataType_gray,
    DataType_rgb
  };

  //================member data===================//
  //the type of PNM image
  //channels can be got from it
  MagicNumber      _magic_number;
  unsigned int     _width;
  unsigned int     _height;
  //value range of pix, it is supposed to be (2^bits-1)
  unsigned short   _range;
  //data of pixes
  //size _width*_width*channels
  unsigned short*  _data;
  //===================func====================//
public:
  /**
   * [PNM constructor of class]
   * 1. initailize the class,load data from local file
   * 2. all params will be initailized,otherwise an exception will be thrown out
   * @param  v_filepath [path of file]
   * @return            none
   */
  explicit PNM(const string & v_filepath);
  ~PNM();

  /**
   * @brief saveToFile  support to save to P4/P5/P6
   * @param v_filepath  path of target image
   * @param v_type
   * @param v_range_dst value range of pix, it is supposed to be (2^bits-1)
   * @return
   */
  int saveToFile(const string & v_filepath,MagicNumber v_type,unsigned int v_range_dst) const;

/**
 * [saveDataToFile to save the data to local file without instantiation ]
 * @param  v_filepath  path of target image
 * @param  v_type_src  the DataType of data,DataType_binary is not supported
 * @param  v_type_dst  the form of target image,MagicNumber_p5/MagicNumber_p6 is supported
 * @param  v_pdata     data,size = _width*_height*channels(v_type_src)
 *                     DataType_gray and DataType_binary has 1 channel
 *                     DataType_rgb has 3 channels
 * @param  _width      width of image of v_pdata
 * @param  _height     height of image of v_pdata
 * @param  v_range_dst v_range_dst value range of pix, it is supposed to be (2^bits-1)
 * @return             0:succeed;otherwise fail
 */
  static int saveDataToFile(const string & v_filepath,
                            DataType v_type_src,
                            MagicNumber v_type_dst,
                            unsigned short * v_pdata,
                            unsigned int _width,
                            unsigned int _height,
                            unsigned int v_range_dst
                            );

  //tool function to display the params of class
  static void print(const PNM & v_pnm);
  void print() const;

private:
  static const vector<char> _list_writespace;
  static const vector<char> _list_nextline;
  static const vector<string> _list_magic_number;

  /**
   * [getHeadInfo to get the head info]
   * @param  v_str data load from local file
   * @return       [description]
   */
  int getHeadInfo(const string& v_str);
  //to convert data from file from data to buffer in class
  //only support P5/P6
  int loadData(const string & v_pdata, MagicNumber v_type);
  //to load data from file
  int loadFromFile(const string & v_filepath);


public:
  //to from the head of image
  //save to a string
  static string formHeadString( MagicNumber v_type,
                                unsigned int _width,
                                unsigned int _height,
                                unsigned int _bits);
  //to judge if this string is a integer
  static bool isInteger(const string & v_str) ;
  //convert string to integer
  static int integerFromString(const string& v_str) ;
  //to convert interger to a string
  static string stringFromNumber(int v_num);
  //to get the a base-2 logarithm of v_num,result is a integer
  //  e.g.: 255  8
  //        1023 10
  static int getLogOf2(unsigned v_num);

  //to convert Uint8 to uint16
  static unsigned short uint16FromUint8(unsigned char v_val);

  /**
   * [isWhitespace judge if char is writespace or not]
   * ascii Code of blanks(0x20), TABs(0x09), CRs(0x0D), LFs(0x0A),#(0x23)
   * @param  v_ch
   * @return      true:char is writespace;false: not
   */
  static bool isWhitespace(char v_ch) ;

  /**
   * [isNextline judge if char is LFs(0x0A)]
   * @param  v_ch [description]
   * @return      true:char is Nextline;false: not
   */
  static bool isNextline(char v_ch) ;



};

#endif // PNM_H
