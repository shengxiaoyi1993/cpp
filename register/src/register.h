
#ifndef REGISTER_H
#define REGISTER_H

#include<iostream>
#include "cJSON.h"

using namespace std;



class Register{
private:
  unsigned _addr;
  unsigned _mask;
  unsigned _shift;
  unsigned _signed;
  string _name;

public:
  Register(unsigned v_addr, unsigned v_mask,unsigned v_shift,unsigned v_signed);
  Register();

  unsigned vaddr() const{ return _addr;}
  unsigned vmask() const{ return _mask;}
  unsigned vshift() const{ return _shift;}
  unsigned vsigned() const{ return _signed;}
  string vname() const{return _name;}

  static Register loadFromJsonObj(cJSON* v_obj){
      Register v_datainfo;
      if(v_obj!= nullptr){

          cJSON* item_child=cJSON_GetObjectItem(v_obj,"addr");
          v_datainfo._addr=static_cast<unsigned>(item_child->valuedouble);

          item_child=cJSON_GetObjectItem(v_obj,"name");
          v_datainfo._name=item_child->valuestring;

          item_child=cJSON_GetObjectItem(v_obj,"mask");
          v_datainfo._mask=static_cast<unsigned>(item_child->valuedouble);

          item_child=cJSON_GetObjectItem(v_obj,"shift");
          v_datainfo._shift=static_cast<unsigned>(item_child->valuedouble);

          item_child=cJSON_GetObjectItem(v_obj,"signed");
          v_datainfo._signed=static_cast<unsigned>(item_child->valuedouble);

      }
      return v_datainfo;
  }


};





#endif
