#include "basic.h"
#include <stdio.h>
#include <cstdlib>
#include<stdlib.h>
#include <sstream>
#include <sys/time.h>

using namespace std;




uint getRandom(uint v_low,uint v_high){
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv,&tz);
    srand(tv.tv_sec*1000000 +tv.tv_usec);
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
