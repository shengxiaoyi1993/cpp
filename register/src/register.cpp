#include"register.h"
#include <iostream>
using namespace std;

Register::Register(unsigned v_addr, unsigned v_mask,unsigned v_shift,unsigned v_signed):
    _addr(v_addr),_mask(v_mask),_shift(v_shift),_signed(v_signed)
{
    cout<<"Register init"<<endl;
}



Register::Register(){
    _addr = 0;
    _mask =0;
    _shift = 0;
    _signed = 0;
    _name = "";
}
