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
  enum MagicNumber{
    MagicNumber_none=0,
    MagicNumber_p1,
    MagicNumber_p2,
    MagicNumber_p3,
    MagicNumber_p4,
    MagicNumber_p5,
    MagicNumber_p6
  };

  enum DataType{
    DataType_binary=1,
    DataType_gray,
    DataType_rgb
  };

  //================member data===================//
  MagicNumber      _magic_number;
  unsigned int     _width;
  unsigned int     _height;
  unsigned short   _range;
  unsigned short*  _data;
  //===================func====================//
public:
  explicit PNM(const string & v_filepath);
  ~PNM();
  int loadFromFile(const string & v_filepath);
  /**
   * @brief saveToFile  support save to P4/P5/P6
   * @param v_filepath
   * @param v_type
   * @return
   */
  int saveToFile(const string & v_filepath,MagicNumber v_type,unsigned int v_range_dst) const;
  static int saveDataToFile(const string & v_filepath,
                            DataType v_type_src,
                            MagicNumber v_type_dst,
                            unsigned short * v_pdata,
                            unsigned int _width,
                            unsigned int _height,
                            unsigned int v_range_dst
                            );
  static void print(const PNM & v_pnm);
  void print() const;

private:
  static const vector<char> _list_writespace;
  static const vector<char> _list_nextline;
  static const vector<string> _list_magic_number;
  bool isWhitespace(char v_ch) const;
  bool isNextline(char v_ch) const;
  int getHeadInfo(const string& v_str);
  int loadData(const string & v_pdata, MagicNumber v_type);
  int loadAsciiData(unsigned char* v_pdata);
  static string formHeadString( MagicNumber v_type,
                         unsigned int _width,
                         unsigned int _height,
                         unsigned int _bits);


 static bool isInteger(const string & v_str) ;
  static int integerFromString(const string& v_str) ;
  static string stringFromNumber(int v_num);
  static int getLogOf2(unsigned v_num);

  static unsigned short uint16FromUint8(unsigned char v_val);
//  static unsigned short bitConvert();



};

#endif // PNM_H
