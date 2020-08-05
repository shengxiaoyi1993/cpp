#include"channel_imagebuffer.h"
#include <fstream>

static  ofstream LogOut("imagebuffer_channel.log");

 FUNC_ImageBufferChannel_RECV ImageBufferChannel::g_mgfunc_callback_display=nullptr;
void* ImageBufferChannel::__pdata=nullptr;
ImageBufferChannel:: ImageBufferChannel(MsgChannel_Mode v_mode,
        ImageBufferChannel_TYPE v_type,
        void (*func_cb)(ImageBufferInArm,void* ), void *pdata):
    __mode(v_mode),__type(v_type)
{
    LogOut<<"v_type:"<<v_type<<endl;
    g_mgfunc_callback_display=func_cb;
    __pdata=pdata;

    switch (__mode) {
    case MsgChannel_Mode::producer:{

        //        __mgfunc_callback=nullptr;
        __msgchannel=new MsgChannel(v_type,v_mode,getMsg);

#ifdef DEBUG_ImageBufferChannel
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
#ifdef DEBUG_ImageBufferChannel
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


ImageBufferChannel::~ImageBufferChannel(){
#ifdef DEBUG_ImageBufferChannel
    LogOut<<"channel delete !"<<endl;
#endif
}


int ImageBufferChannel::addNewImageBufferInArm(ImageBufferInArm v_mgmsg){

    Msg v_msg;
    if(0 == ImageBufferInArm::MsgFromImageBufferInArm(v_mgmsg,v_msg)){
        if(nullptr != __msgchannel){
            int flag= __msgchannel->writeData(v_msg.msg_text,
                                              static_cast<int>(strlen(v_msg.msg_text))+1);

            return flag;
        }
    }
    return -2;

}


void ImageBufferChannel::getMsg(Msg v_msg,long v_type){


    ImageBufferInArm v_mgmsg;
    LogOut<<"v_msg:"<<v_msg.msg_text<<endl;
    if(0 == ImageBufferInArm::ImageBufferInArmFromMsg(v_msg,v_mgmsg)){

        if(g_mgfunc_callback_display != nullptr){
            g_mgfunc_callback_display(v_mgmsg,__pdata);
        }

    }


}
