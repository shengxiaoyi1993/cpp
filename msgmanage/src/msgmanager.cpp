#include "msgmanager.h"
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <iostream>
using namespace std;

const char* response_ok="OK";

MsgManager::MsgManager(MsgManager_Mode v_mode,void (*func_cb)(Msg )):
    __mode(v_mode),__addr_cts(0x6666),__addr_stc(0x8888)
{
    Msg msg;
    if(func_cb!=nullptr){
        func_cb(msg);
        fun_callback=func_cb;
    }

    __ket_stc=Ftok("/",__addr_stc);
    __ket_cts=Ftok("/",__addr_cts);

    printf("__ket_stc:%d\n",__ket_stc);
    printf("__ket_cts:%d\n",__ket_cts);

    __msgid_stc= msgget(__ket_stc,IPC_CREAT|0755);
    __msgid_cts= msgget(__ket_cts,IPC_CREAT|0755);
    printf("__msgid_stc:%d\n",__msgid_stc);
    printf("__msgid_cts:%d\n",__msgid_cts);

    fflush(stdout);

    //     __recvid;
    switch (v_mode) {
    case Client:{
        __recvid=__msgid_stc;
        break;
    }
    case Server:{
        __recvid=__msgid_cts;
        break;
    }
    }

    //将接收过程放在另一线程中

    pthread_t tid;

    //参数依次是：创建的线程id，线程参数，调用的函数，传入的函数参数
    int ret = pthread_create(&tid, NULL, &setReceiver, (void*)&__recvid);
    if (ret != 0)
    {
        cout << "pthread_create error: error_code=" << ret << endl;
    }

}





MsgManager::~MsgManager(){
    //等各个线程退出后，进程才结束，否则进程强制结束了，线程可能还没反应过来；
    pthread_exit(NULL);
}


int MsgManager::writeData(char* v_data,int v_len){
    // printf("%s\n",__func__);

    int writeid;
    switch (__mode) {
    case Client:{
        writeid=__msgid_cts;
        break;
    }
    case Server:{
        writeid=__msgid_stc;
        break;
    }
    }

    Msg msg_tmp;
    msg_tmp.msg_type= SERVER_SEND_FLAG;
    memcpy(msg_tmp.msg_text,v_data,static_cast<uint>(v_len));
    msgsnd(writeid,&msg_tmp,strlen(msg_tmp.msg_text)+ 1,IPC_NOWAIT);
    msgrcv(writeid,&msg_tmp,MSG_BUFFER_LEN,SERVER_RECV_FLAG,0);

}



void *MsgManager::setReceiver(void *p_msgid){
    Msg msg_tmp;
    int v_msgid=*((int*)p_msgid);
    while(1){
//        printf("%s\n",__func__);
        int flag= msgrcv(v_msgid,&msg_tmp,MSG_BUFFER_LEN,CLIENT_RECV_FLAG,0);
        printf("v_msgid:%d\n",v_msgid);
        printf("flag:%d\n",flag);
        if(fun_callback!=nullptr){
            (*fun_callback)(msg_tmp);
        }
        msg_tmp.msg_type= CLIENT_SEND_FLAG;
        memcpy(msg_tmp.msg_text,response_ok,strlen(response_ok));
//        msgsnd(v_msgid,&msg_tmp,strlen(msg_tmp.msg_text)+ 1,IPC_NOWAIT);
        fflush(stdout);
    }

}

int MsgManager::writeData_test(char* v_data,int v_len){
    int writeid;
    switch (__mode) {
    case Client:{
        writeid=__msgid_cts;
        break;
    }
    case Server:{
        writeid=__msgid_stc;
        break;
    }
    }

    Msg msg_tmp;
    msg_tmp.msg_type= SERVER_SEND_FLAG;
    memcpy(msg_tmp.msg_text,v_data,static_cast<uint>(v_len));
    return msgsnd(writeid,&msg_tmp,strlen(msg_tmp.msg_text)+ 1,IPC_NOWAIT);
}

