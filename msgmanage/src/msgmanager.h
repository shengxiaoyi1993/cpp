#ifndef MSGMANAGER_H
#define MSGMANAGER_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <string>


#define MSG_BUFFER_LEN 256
#define SERVER_SEND_FLAG 100
#define SERVER_RECV_FLAG 200
#define CLIENT_SEND_FLAG 200
#define CLIENT_RECV_FLAG 100

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};


typedef struct Msg
{
    long msg_type;
    char msg_text[MSG_BUFFER_LEN];
}Msg;

typedef void (*FUNC_RECV)(Msg);
static FUNC_RECV fun_callback;


inline key_t Ftok(const char *pathname,int proj_id)
{
    key_t key= ftok(pathname,proj_id);
    if(key== -1)
    {
        perror("ftok.");
        exit(1);
    }
    return key;
}

enum MsgManager_Mode{
    Client=0,
    Server
};

class MsgManager
{

public:
    MsgManager(MsgManager_Mode v_mode,void (*func_cb)(Msg ));
    ~MsgManager();
    int writeData(char* v_data,int v_len);
    int writeData_test(char* v_data,int v_len);


private:
    MsgManager_Mode __mode;
    const  int __addr_cts;
    const  int __addr_stc;


    key_t __ket_cts;
    key_t __ket_stc;
    int __msgid_stc;
    int __msgid_cts;

    int __recvid;
    static void *setReceiver(void* p_msgid);



};


#endif
