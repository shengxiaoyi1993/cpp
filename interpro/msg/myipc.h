// myipc.h
#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

key_t Ftok(const char *pathname,int proj_id)
{
    key_t key= ftok(pathname,proj_id);
    if(key== -1)
    {
        perror("ftok.");
        exit(1);
    }
    return key;
}
