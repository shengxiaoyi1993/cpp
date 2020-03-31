#ifndef BASIC_H_
#define BASIC_H_
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

inline std::string integerToString(int num){
    stringstream ss;
    string tmps;
    ss<<num;
    ss>>tmps;
    return tmps;
}


#endif
