#include "pnm.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "../lib/common/string_manipulation.hpp"

const vector<char> PNM::_list_writespace={0x20,0x09,0x0D,0x0A};
const vector<char> PNM::_list_nextline={0x0A};
const vector<string> PNM::_list_magic_number={"NONE","P1","P2","P3","P4","P5","P6"};




PNM::PNM(const string & v_filepath):
  _magic_number(MagicNumber_none),
  _width(0),_height(0),_range(0),_data(nullptr)

{
  int rload= loadFromFile(v_filepath);
  if( rload < 0){
    throw "Error(bad_input):"+v_filepath;
  }
  else{
    print();
  }

}

PNM::~PNM(){

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
  if(rgethead <=0){
    return rgethead;
  }

  //  - judge data format
  //    - if next file should be binary file then convert the content to binary file
  //    - binary:getbinarydata
  //    - ascii :getasciidata
  int rload=loadData(str.substr(static_cast<unsigned>(rgethead),str.size()-static_cast<unsigned>(rgethead)),
                     _magic_number);



  return rload;

}

int PNM::saveToFile(const string & v_filepath,MagicNumber v_type) const{
  return saveDataToFile(v_filepath,v_type,_data,_width,_height,_range);
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
                        MagicNumber v_type,
                        unsigned short * v_pdata,
                        unsigned int v_width,
                        unsigned int v_height,
                        unsigned int v_range
                        ){
  string string_head=formHeadString(v_type,v_width,v_height,v_range);
  cout<<"string_head:"<<string_head<<endl;

  {
  ofstream outpufile(v_filepath,ios::app);
  outpufile<<string_head;
  outpufile.close();
  }

  string string_data;
  switch (v_type) {
    case MagicNumber_p5:{
      //8 pix as unit

      using namespace common::string_manipulation;
      BinaryData bidata(v_width*v_height,BinaryData::BinaryDataDirection_left);
      for(size_t i=0;i<v_width*v_height;i++){
        bidata.appendData<unsigned short>(v_pdata[i],8);
      }
      bidata.print();
      bidata.endAppend(true);

      {
      ofstream outpufile(v_filepath,ios::app|ios::binary);
      outpufile.write(static_cast<const char*>((char*)bidata._pdata),bidata._size_total);
      outpufile.close();
      }

      break;
    }

    default:
      break;
  }


  return 0;

}


int PNM::loadData(const string & v_pdata,  MagicNumber v_type){

  switch (v_type) {
    case MagicNumber_p5:{
      unsigned size=_width*_height;
      _data =(unsigned short*) malloc(size*sizeof (unsigned short));
      for (size_t i=0;i<size;i++) {
        _data[i]=static_cast<unsigned short>(v_pdata[i]);
      }
      break;
    }
    default:
      return -1;
  }
  return 0;

}



bool PNM::isWhitespace(char v_ch) const{
  for(size_t i=0;i<_list_writespace.size();i++){
    if(v_ch == _list_writespace[i]){
      return true;
    }
  }
  return false;
}

bool PNM::isNextline(char v_ch) const{
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
      if(record+1 == i){
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
             && (v_str[1]>'0'&&v_str[1]<'6')){
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
          string tmp=v_str.substr(record+1,i-record-1);
          int integer_tmp = integerFromString(tmp);
          if(isInteger(tmp)&&(integer_tmp>0)){
            _height=static_cast<unsigned>(integer_tmp);
          }
          else{
            return -1;
          }

          //get height
          break;
        }
        case 3:{
          string tmp=v_str.substr(record+1,i-record-1);
          int integer_tmp = integerFromString(tmp);
          if(isInteger(tmp)&&(integer_tmp>0 && integer_tmp<65536)){
            _range=static_cast<unsigned short>(integer_tmp);
          }
          else{
            return -1;
          }
          bheadend=true;

          //get limit
          break;
        }
        default:
          break;
      }
      ++step;
      record=i;

      //get pos of datablock start
      if(bheadend){
        if(!isWhitespace(v_str[i+1])){
          return static_cast<int>(i+1);
        }
      }

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
  string bdata=(v_pnm._data==nullptr)?("Valid"):"NULL";
  cout<<"Data  :  "<<bdata<<endl;
  cout<<"\\=============PNM END ==============\\"<<endl;


}


void PNM::print() const{
  print(*this);
}




