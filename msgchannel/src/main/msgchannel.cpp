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



static const char* fork_path="/";
static FUNC_MSGCHANNEL_RECV fun_callback;




MsgChannel::MsgChannel(int v_projid,MsgChannel_Mode v_mode,void (*func_cb)(Msg )):
    __addr(v_projid),__isActivate(false),__mode(v_mode)
{
    Msg msg;
    if(func_cb!=nullptr){
        func_cb(msg);
        fun_callback=func_cb;
    }
#ifdef DEBUG_MSGCHANNEL
    LogOut.open("msgchannel.log");
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
            LogOut<<">>msgget Succeed!__msgid:"<<__msgid<<endl;
#endif

            threadpara.v_type=(__mode==customer)?100:200;
            threadpara.v_msgid=__msgid;
            threadpara.__pclass=this;
            LogOut<<"init threadpara.v_type:"<<threadpara.v_type<<endl;
            LogOut<<"init threadpara.v_msgid:"<<threadpara.v_msgid<<endl;

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

#ifdef DEBUG_MSGCHANNEL

void MsgChannel::setLogFile(const string &v_file){
  if (LogOut.is_open()) {
    LogOut.close();
    LogOut.open(v_file);
  }

}
#endif


void *MsgChannel::setReceiver(void *ppara){
    Msg msg_tmp;
    msgchannel_recv_thread_para threadpara_in=*(static_cast<msgchannel_recv_thread_para*>(ppara));
    MsgChannel* pch=threadpara_in.__pclass;

    while(1){
        ssize_t flag= msgrcv(threadpara_in.v_msgid,&msg_tmp,MSG_BUFFER_LEN,threadpara_in.v_type,0);
        if(flag == -1){
//            cout<<">>Recv data Error!"<<errno<<endl;
//            cout<<"threadpara_in.v_type:"<<threadpara_in.v_type<<endl;
//            cout<<"threadpara_in.v_msgid:"<<threadpara_in.v_msgid<<endl;
#ifdef DEBUG_MSGCHANNEL
            pch->LogOut<<"threadpara_in.v_type:"<<threadpara_in.v_type<<endl;
            pch->LogOut<<"threadpara_in.v_msgid:"<<threadpara_in.v_msgid<<endl;
            pch->LogOut << ">>Recv data Error!"<<errno<<endl;
#endif
        }
        else{
            if(fun_callback!=nullptr){
                (*fun_callback)(msg_tmp);
            }
#ifdef DEBUG_MSGCHANNEL
            pch->LogOut << ">>Recv data:\n<data>\n"<< msg_tmp.msg_text<<"\n</data>"<<endl;
#endif
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
        }
        else{
#ifdef DEBUG_MSGCHANNEL
            LogOut << ">>fail to send data:"<<msg_tmp.msg_text<<endl;
#endif
        }

        return 0;
    }
}


bool MsgChannel::isActivated(){
    return __isActivate;
}
