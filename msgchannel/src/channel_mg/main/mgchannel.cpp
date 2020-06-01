#include "mgchannel.h"
#include <iostream>
#include <fstream>


#define DEBUG_MGCHANNEL
using namespace std;

static FUNC_MGCHANNEL_RECV g_mgfunc_callback;

#ifdef DEBUG_MGCHANNEL
static ofstream LogOut;
#endif

MGChannel::MGChannel(MsgChannel_Mode v_mode,MGCHANNEL_TYPE v_type,void (*func_cb)(MGMessage )):
    __mode(v_mode),__type(v_type)
{
#ifdef DEBUG_MGCHANNEL
    switch (v_type) {
    case MGCHANNEL_TYPE_CGI:{
        LogOut.open("cgi_channel.log");
        break;
    }
    case MGCHANNEL_TYPE_CONNECTOR:{
        LogOut.open("connector_channel.log");

        break;
    }
    case MGCHANNEL_TYPE_GENERATOR:{
        LogOut.open("generator_channel.log");
        break;
    }
    }

#endif

    switch (__mode) {
    case MsgChannel_Mode::producer:{
        g_mgfunc_callback=nullptr;
        __msgchannel=new MsgChannel(v_type,v_mode,nullptr);

#ifdef DEBUG_MGCHANNEL
        if(__msgchannel != nullptr){
            LogOut<<">> succeed to build channel！"<<endl;
            LogOut<<">> producer mode"<<endl;
            LogOut<<">> recv func set null"<<endl;
        }
        else{
            LogOut<<">> fail to build channel！"<<endl;
        }
#endif
        break;
    }
    case MsgChannel_Mode::customer:{
        g_mgfunc_callback=func_cb;
        __msgchannel=new MsgChannel(v_type,v_mode,getMsg);
#ifdef DEBUG_MGCHANNEL
        if(__msgchannel != nullptr){
            LogOut<<">> succeed to build channel！"<<endl;
            LogOut<<">> customer mode"<<endl;
            LogOut<<">> recv func set "<<endl;
        }
        else{
            LogOut<<">> fail to build channel！"<<endl;
        }
#endif
        break;
    }
    }

}


MGChannel::~MGChannel(){
#ifdef DEBUG_MGCHANNEL
    LogOut<<"channel delete !"<<endl;
#endif
}


int MGChannel::addNewMGMessage(MGMessage v_mgmsg){
#ifdef DEBUG_MGCHANNEL
    LogOut<<"addNewMGMessage start !"<<endl;
#endif
    Msg v_msg;
    if(0 == MGMessage::MsgFromMGMsg(v_mgmsg,v_msg)){
        if(nullptr != __msgchannel){
            int flag= __msgchannel->writeData(v_msg.msg_text,
                                              static_cast<int>(strlen(v_msg.msg_text))+1);
#ifdef DEBUG_MGCHANNEL
            if(flag == 0){
                LogOut<<"succeed to send !"<<endl;
            }
            else{
                LogOut<<"fail to send !"<<endl;
            }

#endif
            return flag;

        }
#ifdef DEBUG_MGCHANNEL
        else{
            LogOut<<"__msgchannel is not activated !"<<endl;
            LogOut<<"fail to send !"<<endl;
        }
#endif
    }
#ifdef DEBUG_MGCHANNEL
    else{
        LogOut<<"fail to get v_msg !"<<endl;
        LogOut<<"fail to send !"<<endl;
    }
#endif
    return -1;

}



void MGChannel::getMsg(Msg v_msg){
#ifdef DEBUG_MGCHANNEL
    LogOut<<"new data recv:"<<v_msg.msg_text<<endl;
#endif
    MGMessage v_mgmsg;
    if(0 == MGMessage::MGMsgFromMsg(v_msg,v_mgmsg)){
#ifdef DEBUG_MGCHANNEL
        LogOut<<"succeed to upload data!"<<endl;
#endif

        (*g_mgfunc_callback)(v_mgmsg);
    }
#ifdef DEBUG_MGCHANNEL
    else{
        LogOut<<"MGMsgFromMsg error!"<<endl;
    }
#endif

}
