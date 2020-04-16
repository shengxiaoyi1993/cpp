//client.c
#include "myipc.h"
#include "utili.h"

int main(int argc,char *argv[])
{
    key_t msg_key= Ftok(argv[1],atoi(argv[2]));
    int msg_id= msgget(msg_key,0);
    Msg msg;
    while(1)
    {
      printf(">>wait client rcv:\n");
        msgrcv(msg_id,&msg,MSG_BUFFER_LEN,CLIENT_RECV_FLAG,0);
        printf(">>finish client rcv:\n");

        printf("Ser:%s\n",msg.msg_text);
        printf("Cli:");
        scanf("%s",msg.msg_text);
        msg.msg_type= CLIENT_SEND_FLAG;
        printf(">>wait client send:\n");
        msgsnd(msg_id,&msg,strlen(msg.msg_text)+ 1,0);
        printf(">>finish client send:\n");

    }
    return 0;
}
