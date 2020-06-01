
#include<iostream>
#include <sstream>
#include "../../main/msgchannel.h"

using namespace std;
void recv(Msg msg);

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



    MsgChannel msgmanager_s(0x6666,MsgChannel_Mode::producer,recv);
    int count=0;
    while (1) {
        string input_str="data from server "+integerToString(count);

        cout<<"count:"<<count<<" getstring:"<<input_str<<endl;

        int flag=  msgmanager_s.writeData(const_cast<char*>(input_str.c_str()),
                                               static_cast<int>(strlen(input_str.c_str())+1));
        cout<<"result:"<<flag<<endl;
        count++;

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
