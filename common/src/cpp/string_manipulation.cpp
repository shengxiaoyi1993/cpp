#include "string_manipulation.hpp"

namespace common{
  namespace string_manipulation{

  //=======================StringConverter=============================//

    StringConverter::StringConverter(const string &v_str ):
      _binary_data(nullptr),_stdstring(v_str)
    {

    }

    unsigned char* StringConverter::AsciiStringFromBinary(const string & v_str){
      unsigned int len_str=v_str.size();
      if(len_str == 0){
        return nullptr;
      }

      unsigned char* pdata=(unsigned char*)malloc(len_str*sizeof(unsigned char));
      //每个字符对应1个ascii码对应 8bits 1byte

      return pdata;


    }




    //=======================BinaryData=============================//
    BinaryData::BinaryData(unsigned int v_size_total,BinaryDataDirection v_direction):
    _pdata(nullptr),_size_total(v_size_total),
    _size_used(0),_direction(v_direction)
    {
      _pdata=new unsigned char[v_size_total];
    }
    BinaryData::~BinaryData(){
      delete []_pdata;
    }




  }

}
