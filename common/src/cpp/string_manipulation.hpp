#ifndef COMMON_STRING_MANIPULATION_HPP
#define COMMON_STRING_MANIPULATION_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <string>

using namespace std;

namespace common{
namespace string_manipulation{

inline string stringFromInt(int v_val){
  stringstream ofs;
  ofs<<v_val;
  string ret;
  ofs>>ret;
  return ret;

}


/**
 * T must be unsigned type
 * v_flag ==true bit at v_pos_start~v_pos_end is 1,others are 0
 * v_flag ==false bit at v_pos_start~v_pos_end is 0,others are 1
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
  BinaryData(unsigned char* v_pdata ,unsigned int v_size_total,BinaryDataDirection v_direction);

  ~BinaryData();
  void print();
  void endAppend(bool v_bend);



  //assume v_bits low bits of v_data is valid

  template<typename T>
  inline void appendData( T v_data,int v_bits){
    int size=sizeof(T);
    //check if v_bits match the size of container
    if(v_bits>size*8){
      throw "Error:v_bits too big";
    }

    //judge if overflow when data is added
    if((_offset_cache+v_bits)>>3+_size_used>_size_total){
      throw "Error:overflow";
    }

    //chech the state of buffer
    //the `_bcomplete` is set to true,data in buffer is not allowed to change
    if(_bcomplete){
      throw "Error:append is ended";
    }

    if(_direction == BinaryDataDirection_left){
      //judge if bits_sum >8
      //  Y:get 8 bit from sum,and save to _data
      //  N:save remain bits to _cache and set _offset_cache
      int remain=v_bits;
      int count=0;
      while(remain>0){

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
    }//end of (_direction == BinaryDataDirection_left)

    return;

  }


  /** get data from buffer of class remove the data
   *
   */
  template<typename T>
  inline bool popData( T v_data,int v_bits){
    //1. check if the size of v_data no smaller than value of v_bits,when it happens,v_data cannot hold the data obtain from _buffer of class
    int size=sizeof(T);
    if(v_bits>size*8){
        throw "[FUNC]: "+string(__FUNCTION__)+" [LINE: ]"+stringFromInt(__LINE__)+" [Error]: params error";
    }

    //2. check the state of _buffer,if _bcomplete is true ,_buffer is not allowed to change
    if(_bcomplete){
      throw "[FUNC]: "+string(__FUNCTION__)+" [LINE: ]"+stringFromInt(__LINE__)
          +" [Error]: not allowed to change";
    }
    //3. check if valid_bits remain in _buffer bigger than demand
    if(v_bits>_size_used+_offset_cache){
      throw "[FUNC]: "+string(__FUNCTION__)+" [LINE: ]"+stringFromInt(__LINE__)
          +" [Error]: no enough bits remain";
    }

    throw "[FUNC]: "+string(__FUNCTION__)+" [LINE: ]"+stringFromInt(__LINE__)
        +" [Error]: not complete";
    //it is complex that to get data from head or tail

    //4. to get data
    //  - if _cache is enough
    //    Y:get data from _cache
    //    N:get data from _cache first,
    //      then load data from _buffer,
    //      return to check again
//    int ;
//    do{

//    }while();




  }



};



}

}



#endif
