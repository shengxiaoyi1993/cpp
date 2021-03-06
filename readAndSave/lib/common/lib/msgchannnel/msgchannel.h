#ifndef MsgChannel_H
#define MsgChannel_H

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
#define PRODUCER_SEND_FLAG 100
#define PRODUCER_RECV_FLAG 200
#define CUSTOMER_SEND_FLAG 200
#define CUSTOMER_RECV_FLAG 100

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

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

enum MsgChannel_Mode{
    customer=0,
    producer
};


typedef struct Msg
{
    long msg_type;
    char msg_text[MSG_BUFFER_LEN];
    Msg(){
      msg_type=-1;
      memset(msg_text,0,sizeof (char)*MSG_BUFFER_LEN);
    }
}Msg;

typedef void (*FUNC_RECV)(Msg,long);






class MsgChannel
{

public:
    MsgChannel(int v_projid, MsgChannel_Mode v_mode,
              void (*func_cb)(Msg, long));
    ~MsgChannel() __attribute__((noreturn));

    /**
     * @brief writeData
     * @param v_data
     * @param v_len
     * @return 0: SUCCEED;-1 NOT ACTIVATE;1
     */
    int writeData(char* v_data,int v_len);

    typedef  struct msgchannel_recv_thread_para{
        MsgChannel *pchannel;
        int v_msgid;
        long v_type;
    }msgchannel_recv_thread_para;

private:
    const  int __addr;
    key_t __key;
    int __msgid;
    bool __isActivate;
    MsgChannel_Mode __mode;
    msgchannel_recv_thread_para threadpara;
    FUNC_RECV __fun_callback;

static    void *setReceiver(void* ppara);



};


#endif
