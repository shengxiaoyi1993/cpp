#include <stdio.h>
#include <unistd.h>

#include "util-pidfile.h"

int main()
{
    int result = 0;

    const char *pidfile = "/var/run/sayhello.pid";

    if (PidfileTestRunning(pidfile) != 0)
        return -1;

    PidfileCreate(pidfile);

    // while (1){
        printf("hello !\n");
    // }
    sleep(15);

    printf("i'm sleep !\n");

    // PidfileRemove(pidfile);
    return 0;
}
