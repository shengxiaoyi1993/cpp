
#include <unistd.h>
#include <stdio.h>
int main(int argc,char** argv)
{
    char* envp[] = {"PATH=/usr/bin","USER=admin",NULL};
    char* argv_execv[] = {"echo","exec on execv",NULL};
    char* argv_execvp[] = {"echo","exec on execvp",NULL};
    char* argv_execve[] = {"echo","exec on execve",NULL};

    if(fork() == 0)
    {
        if(execl("/bin/echo","echo","execut by execl",NULL) < 0)
        {
            perror("error on execl");
        }
    }

    if(fork() == 0)
    {
      if(execlp("echo","echo","exec by execlp",NULL) < 0 )
           perror("error execlp");
    }

    if(fork() == 0)
    {
        if(execle("/bin/echo","echo","execut by execle",NULL,envp) < 0)
        {
            perror("error on execle");
        }
    }

    if(fork() == 0)
    {
        if(execv("/bin/echo",argv_execv) < 0)
        {
            perror("error on execv");
        }
    }

    if(fork() == 0)
    {
        if(execvp("echo",argv_execvp) < 0)
        {
            perror("error on execvp");
        }
    }

    if(fork() == 0)
    {
        if(execve("/bin/echo",argv_execve,envp) < 0)
        {
            perror("error on execve");
        }
    }

    return 0;
}
