//utili.h
#pragma once

#define MSG_BUFFER_LEN 256
#define SERVER_SEND_FLAG 100
#define SERVER_RECV_FLAG 200

#define CLIENT_SEND_FLAG 200
#define CLIENT_RECV_FLAG 100

typedef struct Msg
{
    long msg_type;
    char msg_text[MSG_BUFFER_LEN];
}Msg;
