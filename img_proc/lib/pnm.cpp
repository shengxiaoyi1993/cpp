#include "pnm.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdlib.h>
#include <string.h>
#include "string_manipulation.hpp"

const vector<char> PNM::_list_writespace={0x20,0x09,0x0D,0x0A};
const vector<char> PNM::_list_nextline={0x0A};
const vector<string> PNM::_list_magic_number={"NONE","P1","P2","P3","P4","P5","P6"};




PNM::PNM(const string & v_filepath):
  _magic_number(MagicNumber_none),
  _width(0),_height(0),_range(0),_data(nullptr)

{
  int rload= loadFromFile(v_filepath);
  if( rload < 0){
    throw string(__func__)+"Error(bad_input):";
  }
  else{
    print();
  }

}

PNM::~PNM(){

   free(_data);
   _data=nullptr;
}

int PNM::loadFromFile(const string & v_filepath){
  //load data from file
  ifstream infile(v_filepath,ios::in);   //输入流
  if(!infile.is_open()){
    cout<<"open failed"<<endl;
    return -1;
  }
  std::string str((std::istreambuf_iterator<char>(infile)),
                  std::istreambuf_iterator<char>());


  //get Head
  int rgethead=getHeadInfo(str);
  print();
  if(rgethead <=0){
    return rgethead;
  }

  //  - judge data format
  //    - if next file should be binary file then convert the content to binary file
  //    - binary:getbinarydata
  //    - ascii :getasciidata
  int rload=loadData(str.substr(static_cast<unsigned>(rgethead),str.size()-static_cast<unsigned>(rgethead)),
                     _magic_number);
  print();


  return rload;

}

int PNM::saveToFile(const string & v_filepath,MagicNumber v_type,unsigned int v_range_dst) const{
  DataType type=DataType((_magic_number%3!=0)?(_magic_number%3):(3));

  return saveDataToFile(v_filepath,type,v_type,_data,_width,_height,v_range_dst);
}

string PNM::formHeadString( MagicNumber v_type,
                            unsigned int _width,
                            unsigned int _height,
                            unsigned int _range){
  string tmpstr;
  tmpstr+=_list_magic_number[v_type]+"\n";
  tmpstr+=stringFromNumber(static_cast<int>(_width))+"\n";
  tmpstr+=stringFromNumber(static_cast<int>(_height))+"\n";
  tmpstr+=stringFromNumber(static_cast<int>(_range))+"\n";
  return tmpstr;

}


string PNM::stringFromNumber(int v_num){
  string tmpstr;
  stringstream ss;
  ss << v_num;
  ss >> tmpstr;
  return tmpstr;
}


int PNM::saveDataToFile(const string & v_filepath,
                        DataType v_type_src,
                        MagicNumber v_type_dst,
                        unsigned short * v_pdata,
                        unsigned int v_width,
                        unsigned int v_height,
                        unsigned int v_range_dst
                        ){
  string string_head=formHeadString(v_type_dst,v_width,v_height,v_range_dst);

  {
    ofstream outpufile(v_filepath);
    outpufile<<string_head;
    outpufile.close();
  }

  //save pix data
  int bits=getLogOf2(v_range_dst);
  int pix_store_space = bits>8?16:8;


  //if v_type_dst == p2 p5 ->gray
  //if v_type_dst == p3 p6 ->rgb
  unsigned short *buffer_tmp=nullptr;
  switch (v_type_dst) {
    case MagicNumber_p1:
    case MagicNumber_p4:{
      throw string(__func__)+"Error:Save Type not support!";
      //      break;
    }
    case MagicNumber_p2:
    case MagicNumber_p5:{

      switch (v_type_src) {
        case DataType_binary:{
          throw string(__func__)+"unsupport";
          //          break;
        }
        case DataType_gray:{
          buffer_tmp =new unsigned short[v_width*v_height];
          memcpy(buffer_tmp,v_pdata, sizeof(unsigned short)*v_width*v_height);
          break;
        }
        case DataType_rgb:{
          buffer_tmp =new unsigned short[v_width*v_height];
          for(size_t i=0;i<v_width*v_height;i++){
            buffer_tmp[i]=static_cast<unsigned short>(v_pdata[i*3]*0.3+v_pdata[i*3+1]*0.59+v_pdata[i*3+2]*0.11);
          }
          break;
        }
        default:
          throw string(__func__)+"unsupport";
      }

      break;
    }
    case MagicNumber_p3:
    case MagicNumber_p6:{
      switch (v_type_src) {
        case DataType_binary:{

          throw string(__func__)+"unsupport";
          //          break;
        }
        case DataType_gray:{

          buffer_tmp =new unsigned short[v_width*v_height*3];
          for(size_t i=0;i<v_width*v_height;i++){
            buffer_tmp[3*i]=v_pdata[i];
            buffer_tmp[3*i+1]=v_pdata[i];
            buffer_tmp[3*i+2]=v_pdata[i];
          }

          break;
        }
        case DataType_rgb:{

          buffer_tmp =new unsigned short[v_width*v_height*3];
          memcpy(buffer_tmp,v_pdata, sizeof(unsigned short)*v_width*v_height*3);
          break;
        }
      }

      break;
    }
    default:
      throw string(__func__)+"Error:Save Type not support!";
  }



  switch (v_type_dst) {

    case MagicNumber_p5:{
      //8 pix as unit
      unsigned int size=v_width*v_height;
      unsigned buffersize=size*pix_store_space/8;
      unsigned offset=16-bits;

      using namespace common::string_manipulation;
      BinaryData bidata(buffersize,BinaryData::BinaryDataDirection_left);

      for(size_t i=0;i<v_width*v_height;i++){
        bidata.appendData<unsigned short>(buffer_tmp[i]>>offset,pix_store_space);
      }
//    bidata.print();
      bidata.endAppend(true);
      {
        ofstream outpufile(v_filepath,ios::app|ios::binary);
        outpufile.write(static_cast<const char*>((char*)bidata._pdata),bidata._size_total);
        outpufile.close();
      }
      break;
    }
    case MagicNumber_p6:{

      //8 pix as unit
      using namespace common::string_manipulation;
      unsigned int size=v_width*v_height*3;
      unsigned buffersize=size*pix_store_space/8;

      BinaryData bidata(buffersize,BinaryData::BinaryDataDirection_left);
      unsigned offset=16-bits;
      for(size_t i=0;i<size;i++){
        bidata.appendData<unsigned short>(static_cast<unsigned short>(buffer_tmp[i]>>offset),pix_store_space);
      }
      bidata.endAppend(true);

      {
        ofstream outpufile(v_filepath,ios::app|ios::binary);
        outpufile.write(static_cast<const char*>((char*)bidata._pdata),bidata._size_total);
        outpufile.close();
      }

      break;
    }

    default:
      throw string(__func__)+"Error:Save Type not support!";
  }
  delete[] buffer_tmp;

  return 0;

}


int PNM::loadData(const string & v_pdata,  MagicNumber v_type){
  unsigned size;
  switch (v_type) {
    case MagicNumber_p5:{
     size=_width*_height;
      break;
    }
    case MagicNumber_p6:{
     size=_width*_height*3;
      break;
    }
    default:
      return -1;
  }



  switch (v_type) {
    case MagicNumber_p1: case MagicNumber_p2: case MagicNumber_p3:{
      //load as ASCII format
      throw string(__func__)+"Error:not support";
    }
    case MagicNumber_p4:{
      //load as ASCII format
      throw string(__func__)+"Error:not support";
    }
    case MagicNumber_p5: case MagicNumber_p6:{
      if(size>v_pdata.size() ){
        throw string(__func__)+"Error:not support";
      }

      int bits=getLogOf2(_range);
      _data = new unsigned short[size];
      unsigned offset=16-bits;

      if(_range >255 && _range <65536){
        //small-end
          memcpy(_data,v_pdata.c_str(),size*sizeof(unsigned short));
          for (size_t i=0;i<size;i++) {
            //collect order of bits,resulted from small-end order when copy
            _data[i]=static_cast<unsigned short>(_data[i]<<8)
            |static_cast<unsigned short>(_data[i]>>8);
            _data[i]=_data[i]<<offset;

        }

      }
      else if(_range<=255){
        for (size_t i=0;i<size;i++) {
          _data[i]=static_cast<unsigned short>(v_pdata[i])<<offset;
        }
      }
      else{
        throw string(__func__)+"Error:range overlap 1!";
      }
      return 0;
    }
    default:
    return -1;
  }

}


bool PNM::isWhitespace(char v_ch) {
  for(size_t i=0;i<_list_writespace.size();i++){
    if(v_ch == _list_writespace[i]){
      return true;
    }
  }
  return false;
}

bool PNM::isNextline(char v_ch) {
  for(size_t i=0;i<_list_nextline.size();i++){
    if(v_ch == _list_nextline[i]){
      return true;
    }
  }
  return false;
}

int PNM::getHeadInfo(const string& v_str){
  //given that magic number is start of string
  //1. get magic_number
  //2. check magic_number
  //3. get param until all info get
  //  - check if record and current adjacent
  //  - check if comment start
  //    - Y:getWhitespace until next line
  //    - N:if start with '#'
  //      - Y:comment start
  //      - N:read number,chech number >0,throw error otherwise

  //get Head
  size_t record=0;
  bool commentstart=false;
  bool bheadend=false;
  int step=0;
  for(size_t i=0;i<v_str.size();i++){

    //judge if two writespace is adjacent
    if(isWhitespace(v_str[i])){
      if(record+1 == i &&  !commentstart ){
        record=i;
        continue;
      }

      //jump comment
      if(commentstart){
        if(isNextline(v_str[i])){
          commentstart=false;
        }
        record=i;
        continue;
      }
      else{
        if(v_str[i+1] == '#'){
          commentstart=true;
        }
      }

      //get info
      switch(step){
        case 0:{
          //get magic_number
          //and check magic number
          if((i == 2) && (v_str[0] == 'P')
             && (v_str[1]>'0'&&v_str[1]<='6')){
            string tmp=v_str.substr(0,i-record);
            _magic_number = static_cast<MagicNumber>(v_str[1]-'0');
          }
          else{
            return -1;
          }
          break;
        }
        case 1:{
          //get width

          string tmp=v_str.substr(record+1,i-record-1);
          int integer_tmp = integerFromString(tmp);
          if(isInteger(tmp)&&(integer_tmp>0)){
            _width=static_cast<unsigned>(integer_tmp);
          }
          else{
            return -1;
          }

          break;
        }
        case 2:{
          //get height
          string tmp=v_str.substr(record+1,i-record-1);
          int integer_tmp = integerFromString(tmp);
          if(isInteger(tmp)&&(integer_tmp>0)){
            _height=static_cast<unsigned>(integer_tmp);
          }
          else{
            return -1;
          }

          break;
        }
        case 3:{
          //get limit
          string tmp=v_str.substr(record+1,i-record-1);
          int integer_tmp = integerFromString(tmp);
          if(isInteger(tmp)&&(integer_tmp>0 && integer_tmp<65536)){
            _range=static_cast<unsigned short>(integer_tmp);
            return static_cast<int>(i+1);
          }
          else{
            return -1;
          }
          bheadend=true;

          break;
        }
        default:
          break;
      }
      ++step;
      record=i;

    }
  }
  return -1;


}

bool PNM::isInteger(const string & v_str) {
  for(auto it:v_str){
    if(!(it<='9'&&it>='0')){
      return false;
    }
  }
  return true;

}
int PNM::integerFromString(const string& v_str) {
  int integer;
  stringstream ss;
  ss << v_str;
  ss >> integer;
  return integer;
}

void PNM::print(const PNM & v_pnm){
  cout<<"\\=============PNM HEAD==============\\"<<endl;
  cout<<"Type  :  "<<_list_magic_number[v_pnm._magic_number]<<endl;
  cout<<"Width :  "<<v_pnm._width<<endl;
  cout<<"Height:  "<<v_pnm._height<<endl;
  cout<<"Range :  "<<v_pnm._range<<endl;
  string bdata=(v_pnm._data==nullptr)?("NULL"):"Valid";
  cout<<"Data  :  "<<bdata<<endl;
  cout<<"\\=============PNM END ==============\\"<<endl;

}


void PNM::print() const{
  print(*this);
}

int PNM::getLogOf2(unsigned v_num){
  unsigned tmp=1;
  unsigned ret=0;
  while (tmp<v_num) {
    tmp*=2;
    ret++;
  }
  return ret;

}


unsigned short PNM::uint16FromUint8(unsigned char v_val){
  unsigned short ret=0;
  for (size_t i=1,sheld=1;i<=8;i++,sheld<<=1) {
    unsigned short tmp=static_cast<unsigned short>((v_val&sheld)<<(i-1));
    ret|=tmp;
  }
  return ret;

}
