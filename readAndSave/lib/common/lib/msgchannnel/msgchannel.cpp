#include "msgchannel.h"
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <iostream>
#include <fstream>
using namespace std;


#define DEBUG_MSGCHANNEL

static const char* fork_path="/";

#ifdef DEBUG_MSGCHANNEL
static ofstream LogOut("msgchannel.log");
#endif


MsgChannel::MsgChannel(int v_projid, MsgChannel_Mode v_mode,void (*func_cb)(Msg,long)):
    __addr(v_projid),__isActivate(false),__mode(v_mode)
{
    Msg msg;
    if(func_cb!=nullptr){
        //        func_cb(msg);
        __fun_callback=func_cb;

    }
#ifdef DEBUG_MSGCHANNEL
    string modename=(__mode==customer)?"customer":"producer";
    LogOut<<">>start to build channel!fork_path:"<<fork_path
         <<" id: "<<__addr
        <<" mode:"<<modename<<endl;
#endif


    __key=Ftok(fork_path,__addr);


    if(__key == -1){
        __msgid=-1;
#ifdef DEBUG_MSGCHANNEL
        LogOut<<">>Ftok Error!"<<endl;
#endif

    }
    else{
#ifdef DEBUG_MSGCHANNEL

        LogOut<<">>Ftok Succeed!"<<endl;
#endif

        __msgid= msgget(__key,IPC_CREAT|0755);
        if(__msgid == -1){
#ifdef DEBUG_MSGCHANNEL

            LogOut<<">>msgget Error!"<<endl;
#endif

        }
        else{

#ifdef DEBUG_MSGCHANNEL
            LogOut<<">>msgget Succeed!"<<endl;
#endif
            threadpara.pchannel=this;
            threadpara.v_type=(__mode==customer)?CUSTOMER_RECV_FLAG:PRODUCER_RECV_FLAG;
            threadpara.v_msgid=__msgid;
            //将接收过程放在另一线程中
            pthread_t tid;
            //参数依次是：创建的线程id，线程参数，调用的函数，传入的函数参数
            int ret = pthread_create(&tid, nullptr, &setReceiver, static_cast<void*>(&threadpara));

            if (ret != 0)
            {
                __isActivate=false;
#ifdef DEBUG_MSGCHANNEL
                LogOut << ">>Recv Thread Fail:error_code=" << ret << endl;
#endif
            }
            else{
                __isActivate=true;
#ifdef DEBUG_MSGCHANNEL
                LogOut << ">>create Recv Thread Succeed！"<< endl;
                LogOut << ">>succeed to connect to channnel！"<< endl;

#endif
            }
        }
    }
}


MsgChannel::~MsgChannel(){
#ifdef DEBUG_MSGCHANNEL
    LogOut << ">>channel ended!"<<endl;
#endif
    //等各个线程退出后，进程才结束，否则进程强制结束了，线程可能还没反应过来；
    pthread_exit(nullptr);

}


void *MsgChannel::setReceiver(void *ppara){
#ifdef DEBUG_MSGCHANNEL
            LogOut << __func__<<"start"<<endl;
#endif

    Msg msg_tmp;
    msgchannel_recv_thread_para threadpara=*(static_cast<msgchannel_recv_thread_para*>(ppara));
    while(1){
#ifdef DEBUG_MSGCHANNEL
            LogOut << __func__<<">>ready to msgrcv"<<endl;
#endif
        ssize_t flag= msgrcv(threadpara.v_msgid,&msg_tmp,MSG_BUFFER_LEN,threadpara.v_type,0);

#ifdef DEBUG_MSGCHANNEL
            LogOut << __func__<<">>succeed to msgrcv"<<endl;
#endif
        if(flag == -1){
            // cout<<">>Recv data Error!"<<endl;
#ifdef DEBUG_MSGCHANNEL
            LogOut << ">>Recv data Error!"<<endl;
#endif
        }
        else{
#ifdef DEBUG_MSGCHANNEL
            LogOut << ">>Recv data:\n<data>\n"<< msg_tmp.msg_text<<"\n</data>"<<endl;
#endif
            if(threadpara.pchannel->__fun_callback!=nullptr){
                (*threadpara.pchannel->__fun_callback)(msg_tmp,threadpara.pchannel->__addr);
            }

        }
    }

}


int MsgChannel::writeData(char* v_data,int v_len){

    if(__isActivate == false){
#ifdef DEBUG_MSGCHANNEL
        LogOut << ">>fail to write data ! channel is not activate !"<<endl;
#endif
        return -1;
    }
    else{
        Msg msg_tmp;
        msg_tmp.msg_type= (__mode==customer)?CUSTOMER_SEND_FLAG:PRODUCER_SEND_FLAG;
        memcpy(msg_tmp.msg_text,v_data,static_cast<uint>(v_len));
        int flag_send=msgsnd(__msgid,&msg_tmp,strlen(msg_tmp.msg_text)+ 1,IPC_NOWAIT);
        if(flag_send == 0){
#ifdef DEBUG_MSGCHANNEL
            LogOut << ">>succeed to send data:"<<msg_tmp.msg_text<<endl;
#endif
            return 0;

        }
        else{

#ifdef DEBUG_MSGCHANNEL
            LogOut << ">>fail to send data:"<<msg_tmp.msg_text<<endl;
#endif
            return 1;
        }

    }
}
