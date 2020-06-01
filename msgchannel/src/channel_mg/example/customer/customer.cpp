#include<iostream>
#include "../../../channel_mg/main/mgchannel.h"

using namespace std;
void recv(MGMessage msg);

int main() {

    MGChannel  producer(MsgChannel_Mode::customer,MGCHANNEL_TYPE::MGCHANNEL_TYPE_CGI,recv);
    while (true) {
//        string input;
//        cin>>input;
//        producer.addNewMGMessage(MGMessage(112233,input.c_str(),true));
    }

    return 0;
}




void recv(MGMessage msg){
    static int count=0;
    cout<<"count:"<<count<<endl;
    cout<<"iswait:"<<msg.iswait<<endl;
    cout<<"path:"<<msg.path<<endl;
    cout<<"timecode:"<<msg.timecode<<endl;

    count++;
}
