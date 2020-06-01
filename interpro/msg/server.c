//server.c
#include "myipc.h"
#include "utili.h"

int main(int argc,char *argv[])
{
    key_t msg_key= Ftok(argv[1],atoi(argv[2]));
    int msg_id= msgget(msg_key,IPC_CREAT|0755);
    if(msg_id== -1)
    {
        perror("msgget");
        exit(1);
    }


    Msg msg;
    while(1)
    {
        printf("Ser:");
        // scanf("%s",msg.msg_text);
        memcpy(msg.msg_text,"test",strlen("test")+1);
        msg.msg_type= SERVER_SEND_FLAG;
        printf(">>wait server send:\n");

        msgsnd(msg_id,&msg,strlen(msg.msg_text)+ 1,0);
        printf(">>finish server send:\n");
        printf(">>wait server rcv:\n");
        msgrcv(msg_id,&msg,MSG_BUFFER_LEN,SERVER_RECV_FLAG,0);
        printf(">>finish server rcv:\n");

        printf("Cli:%s\n",msg.msg_text);
    }
    msgctl(msg_id,IPC_RMID,NULL);
    return 0;
}
