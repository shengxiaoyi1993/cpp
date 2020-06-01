#include<iostream>
#include "../../main/msgchannel.h"

using namespace std;
void recv(Msg msg);

int main() {


    MsgChannel msgmanager_c(0x6666,MsgChannel_Mode::customer,recv);
    while (1) {
        // char *str="hello from client";
        // msgmanager_c.writeData(str,static_cast<int>(strlen(str)+1));
    }

    getchar();
    return 0;
}




void recv(Msg msg){
    static int count=0;
    cout<<"count:"<<count<<endl;
    cout<<"msg:"<<msg.msg_text<<endl;
    count++;
}
