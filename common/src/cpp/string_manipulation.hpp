#ifndef COMMON_STRING_MANIPULATION_HPP
#define COMMON_STRING_MANIPULATION_HPP

#include <iostream>
#include <string>

using namespace std;

namespace common{
namespace string_manipulation{
class StringConverter{
  StringConverter(const string &v_str );
  string         _stdstring;
  unsigned char* _binary_data;
  //uncomplete
  static unsigned char* AsciiStringFromBinary(const string & v_str);
};

/**
     * designed to format BinaryData
     * input different bits of data and save to BinaryData
     * data from out gradually fill the BinaryData from certain direction,but
     * as uncertain number of bits.When certain unsigned char cannot be filled,
     * overlap bits will save in _cache temporarily.When append next data,_cache
     * should be added to _data
     *
     */
class BinaryData{
  //============statement==============//
public:
  enum BinaryDataDirection{
    BinaryDataDirection_left=0,
    BinaryDataDirection_right
  };
  //==================member==================//
private:
  unsigned char*      _pdata;
  unsigned int        _size_total;
  unsigned int        _size_used;
  BinaryDataDirection _direction;
  //bits in _direction is valid
  unsigned char        _cache;
  unsigned int         _offset_cache;

  //==================func==================//
  BinaryData(unsigned int v_size_total,BinaryDataDirection v_direction);
  ~BinaryData();



  //assume v_bits low bits of v_data is valid

  template<typename T>
  inline void appendData( T& v_data,int v_bits){
    int size=sizeof(T);
    if(v_bits<size){
      throw "Error:v_bits too big";
    }
    if(_offset_cache+_size_used+v_bits>_size_total){
      throw "Error:overflow";
    }

    //
    if(_direction == BinaryDataDirection_left){
      int remain=v_bits+_offset_cache;
      int count=0;
      while(remain<8){
        remain-=8;
        switch (_direction) {
          case BinaryDataDirection_left:{
            _cache+=v_data>>((8-_offset_cache+8*count));
            break;
          }
          case BinaryDataDirection_right:{
            _cache+=v_data<<((8-_offset_cache+8*count));
            break;
          }
        }
        _pdata[_size_used]=_cache;
        _size_used++;
        count++;
      }
      _offset_cache=remain;
      switch (_direction) {
        case BinaryDataDirection_left:{
          _cache+=v_data>>((8-_offset_cache+8*count));
          break;
        }
        case BinaryDataDirection_right:{
          _cache+=v_data<<((8-_offset_cache+8*count));
          break;
        }
      }

    }
    return;

  }



};



}

}



#endif
