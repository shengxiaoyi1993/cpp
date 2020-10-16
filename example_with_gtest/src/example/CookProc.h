#ifndef COOKPROC_H
#define COOKPROC_H

#include <iostream>

using namespace std;

class CookProc{

private:
  bool _state_addOil;
  bool _state_addSalt;
  bool _state_addVegetable;
public:
  CookProc():_state_addOil(false),
        _state_addSalt(false),
        _state_addVegetable(false){

  }
  void addOil(){
    _state_addOil=true;
  }

  void addSalt(){
    _state_addSalt=true;
  }
  void addVegetable(){
    _state_addVegetable=true;
  }
  bool getDish(){
    if(_state_addOil&&_state_addSalt&&_state_addVegetable){
      _state_addOil=false;
      _state_addSalt=false;
      _state_addVegetable=false;
      return true;
    }
    else{
      return false;
    }
  }

};

#endif
