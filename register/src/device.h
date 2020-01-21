#ifndef DEVICE_H
#define DEVICE_H
#include <iostream>
#include <string>
#include <vector>
#include "register.h"
#include "dvt-uio.h"
#include "basic.h"


using namespace std;
class DeviceIO{

private:
    string _path_register_info;
    std::vector<Register> _list_register;
    UIO _uio;
    UIO_mmap _mmap_regs;

public:
    DeviceIO(const string & path_register_info ,const char* fn);
    int writeReg(const string& name_reg,unsigned wr_word);
    int readReg(const string & name_reg);

private:
    bool findRegister(const string & name_reg,Register& v_register) const;



};





#endif
