#include <iostream>
#include "../../../msgchannel.h"

using namespace std;


void getmsg(Msg v_msg,long v_addr);

int main(int argc, char const *argv[]) {
  MsgChannel ch_customer(0,MsgChannel_Mode::customer,getmsg);
  while (true) {
    string tmp="data from customer";
    ch_customer.writeData((char*)tmp.c_str(),tmp.size());
  }

  return 0;
}


void getmsg(Msg v_msg,long v_addr){
  std::cout << "/* message */"<<v_msg.msg_text << '\n';
}
