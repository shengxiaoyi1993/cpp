#include "basic.h"
#include <stdio.h>
#include <cstdlib>
#include<stdlib.h>
#include <sstream>

using namespace std;




uint getRandom(uint v_low,uint v_high){
        srand(time(nullptr));
        uint interval=v_high-v_low;
        uint num=random()%interval+v_low;
        return num;
}

std::string integerToString(uint num){
  stringstream ss;
  ss.clear();
  ss.str("");
  string tmps;
  ss<<num;
  ss>>tmps;
  return tmps;
}
