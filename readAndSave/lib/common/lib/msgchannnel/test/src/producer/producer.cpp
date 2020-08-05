#include <iostream>
#include "../../../msgchannel.h"
using namespace std;


void getmsg(Msg v_msg,long v_addr);

int main(int argc, char const *argv[]) {
  MsgChannel ch_producer(0,MsgChannel_Mode::producer,getmsg);
  while (true) {
    string tmp="data from producer";
    ch_producer.writeData((char*)tmp.c_str(),tmp.size());
  }
  return 0;
}


void getmsg(Msg v_msg,long v_addr){
  std::cout << "/* message */"<<v_msg.msg_text << '\n';
}
