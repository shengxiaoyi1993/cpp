#include "mgchannel.h"
#include <iostream>
#include <fstream>


using namespace std;


 FUNC_MGCHANNEL_RECV MGChannel::g_mgfunc_callback_cgi =nullptr;
 FUNC_MGCHANNEL_RECV MGChannel::g_mgfunc_callback_connector =nullptr;
 FUNC_MGCHANNEL_RECV MGChannel::g_mgfunc_callback_generator =nullptr;


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

    switch (v_type) {
    case MGCHANNEL_TYPE_CGI:{
        g_mgfunc_callback_cgi=func_cb;
        break;
    }
    case MGCHANNEL_TYPE_CONNECTOR:{
        g_mgfunc_callback_connector=func_cb;
        break;
    }
    case MGCHANNEL_TYPE_GENERATOR:{
        g_mgfunc_callback_generator=func_cb;
        break;
    }
    }

    switch (__mode) {
    case MsgChannel_Mode::producer:{

//        __mgfunc_callback=nullptr;
        __msgchannel=new MsgChannel(v_type,v_mode,nullptr);

#ifdef DEBUG_MGCHANNEL
        if(__msgchannel != nullptr){
            LogOut<<">> succeed to build channel！"<<endl;
            LogOut<<">> producer mode"<<endl;
            LogOut<<">> recv func set null"<<endl;
        }
        else{
            LogOut<<">> fail to build channel ！"<<endl;
        }
#endif
        break;
    }
    case MsgChannel_Mode::customer:{
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



void MGChannel::getMsg(Msg v_msg,long v_type){
#ifdef DEBUG_MGCHANNEL
    LogOut<<"new data recv:"<<v_msg.msg_text<<endl;
#endif
    MGMessage v_mgmsg;
    if(0 == MGMessage::MGMsgFromMsg(v_msg,v_mgmsg)){
#ifdef DEBUG_MGCHANNEL
        LogOut<<"succeed to upload data!"<<endl;
#endif
        // v_mgmsg.print();
//        if(__mgfunc_callback){

//        }

        switch (v_type) {
        case MGCHANNEL_TYPE_CGI:{
            if(g_mgfunc_callback_cgi != nullptr){
                (*g_mgfunc_callback_cgi)(v_mgmsg);
            }
            break;
        }
        case MGCHANNEL_TYPE_CONNECTOR:{
            if(g_mgfunc_callback_connector != nullptr){
                (*g_mgfunc_callback_connector)(v_mgmsg);
            }

            break;
        }
        case MGCHANNEL_TYPE_GENERATOR:{
            if(g_mgfunc_callback_generator != nullptr){
                (*g_mgfunc_callback_generator)(v_mgmsg);
            }

            break;
        }
        }



#ifdef DEBUG_MGCHANNEL
    else{
        LogOut<<"no g_mgfunc_callback set!"<<endl;
    }
#endif
    }
#ifdef DEBUG_MGCHANNEL
    else{
        // v_mgmsg.print();
        LogOut<<"MGMsgFromMsg error!"<<endl;
    }
#endif

}
