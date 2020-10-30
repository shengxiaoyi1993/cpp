#include "string_manipulation.hpp"
#include <iomanip>

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
    _size_used(0),_direction(v_direction),
      _offset_cache(0),_cache(0)
    {
      _pdata=new unsigned char[v_size_total];
      _bcomplete=false;
    }

    BinaryData::~BinaryData(){
      delete []_pdata;
    }
    void BinaryData::endAppend(bool v_bend){
      if(v_bend != _bcomplete){
        _bcomplete=v_bend;
      }
      else{
        throw "repeat to endAppend";
      }

      if(v_bend){
        if(_cache != 0){
          _pdata[_size_used]=_cache;
          _size_used++;
        }
      }
      else{
        if(_cache != 0){
          _size_used--;
          _pdata[_size_used]=0;

        }

      }

    }


    void BinaryData::print(){
      cout<<"//========================BinaryData START==========================//"<<endl;
      cout<<"_size_total:"<<_size_total<<endl;
      cout<<"_size_used: "<<_size_used<<endl;
      cout<<"Data:"<<endl;

      for(size_t i=0;i<_size_total;i++){
        if(i%16 == 0){
          cout<<"\n";
        }
        else if(i%4 == 0 &&(i%16!=0)){
          cout<<" ";
        }


        cout<<hex<<setw(2)<<static_cast<int>(_pdata[i]);

      }
      cout<<endl<<endl;


      cout<<dec;
      cout<<"_offset_cache:"<<_offset_cache<<endl;
      cout<<"Cache:"<<endl;
      cout<<hex<<setw(2)<<static_cast<int>(_cache)<<endl;
      cout<<dec;
      cout<<"//========================BinaryData END==========================//"<<endl;


    }





  }

}
