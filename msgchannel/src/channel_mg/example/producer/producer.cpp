
#include<iostream>
#include <sstream>
#include "../../../channel_mg/main/mgchannel.h"

using namespace std;
void recv(MGMessage msg);

std::string integerToString(int num){
    stringstream ss;
    ss.clear();
    ss.str("");
    string tmps;
    ss<<num;
    ss>>tmps;
    return tmps;
}

int main() {

  MGChannel  producer(MsgChannel_Mode::producer,MGCHANNEL_TYPE::MGCHANNEL_TYPE_GENERATOR,nullptr);
  while (true) {
      cout<<"in while"<<endl;
      string input;
      cin>>input;
      producer.addNewMGMessage(MGMessage(112233,input.c_str(),true));
  }

    return 0;
}



void recv(MGMessage v_mgmsg){
    static int count=0;
    cout<<"count:"<<count<<endl;
    cout<<"iswait:"<<v_mgmsg.iswait<<endl;
    cout<<"path:"<<v_mgmsg.path<<endl;
    cout<<"timecode:"<<v_mgmsg.timecode<<endl;

    count++;
}
