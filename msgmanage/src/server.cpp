#include<iostream>
#include "msgmanager.h"

using namespace std;
void recv(Msg msg);

int main() {



    MsgManager msgmanager_s(MsgManager_Mode::Server,recv);
    while (1) {
        char *str="hello from server";
        msgmanager_s.writeData(str,static_cast<int>(strlen(str)+1));
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
