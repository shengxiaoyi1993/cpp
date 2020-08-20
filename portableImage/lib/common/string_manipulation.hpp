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
public:
  unsigned char*      _pdata;
  unsigned int        _size_total;
  unsigned int        _size_used;
  BinaryDataDirection _direction;
  //bits in _direction is valid
  unsigned char        _cache;
  unsigned int         _offset_cache;
  bool                 _bcomplete;

public:
  //==================func==================//
  BinaryData(unsigned int v_size_total,BinaryDataDirection v_direction);
  ~BinaryData();
  void print();
  void endAppend(bool v_bend);

  /**
   * T must be unsigned type
   */
  template<typename T>
  inline T getSheld(int v_pos_start,int v_pos_end,bool v_flag){
    T zero=0;
    T zero_1=-1;

    if(zero>zero_1){
      throw "Error:T should be unsigned type";
    }

    int size=sizeof(T)*8;
    T allone=~0;
    if(v_pos_start>=0 && v_pos_start<=v_pos_end && v_pos_end<size){
      int num=v_pos_end-v_pos_start+1;
      allone>>=(size-num);
      allone<<=(v_pos_start);
      if(!v_flag){
        allone=~allone;

      }
    }
    else{
      throw "Error:pos overflow";
    }
    return allone;
  }


  //assume v_bits low bits of v_data is valid

  template<typename T>
  inline void appendData( T v_data,int v_bits){
    int size=sizeof(T);
    if(v_bits>size*8){
      throw "Error:v_bits too big";
    }
    if((_offset_cache+v_bits)>>3+_size_used>_size_total){
      throw "Error:overflow";
    }

    if(_bcomplete){
      throw "Error:append is ended";
    }

    //
    if(_direction == BinaryDataDirection_left){


      //judge if bits_sum >8
      //  Y:get 8bit sum sum,and save to _data
      //  N:save remain bits to _cache and set _offset_cache
      int remain=v_bits;
      int count=0;
      while(remain>0){
        cout<<"remain:"<<remain<<endl;
        if(remain+_offset_cache>=8){
          T tmpsheld=getSheld<T>(remain-8+_offset_cache,remain-1,true);
          T value=tmpsheld&v_data;
          value>>=(remain-8+_offset_cache);
          _cache|=value;
          _pdata[_size_used]=_cache;
          _size_used++;
          remain-=(8-_offset_cache);
          _cache=0;
          _offset_cache=0;
        }
        else{
          T tmpsheld=getSheld<T>(0,remain-1,true);
          T value=tmpsheld&v_data;
          value<<=(8-remain-_offset_cache);
          _cache|=value;
          _offset_cache=_offset_cache+remain;
          remain=0;
        }
      }

    }
    else{

      throw  "Error:unsupport now !";
    }
    return;

  }



};



}

}



#endif
