#ifndef EXECUTECMD_H_
#define EXECUTECMD_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


/**
 * [executeCMD 输入命令行指令，经执行后输出执行结果]
 * @param cmd    [input 输入指令]
 * @param result [output 输出参数]
 */

 inline int executeCMD(const char *cmd, char *result)
{
    char buf_ps[1024]={0};
    char ps[1024]={0};
    FILE *ptr;
    strcpy(ps, cmd);
    if((ptr=popen(ps, "r"))!=NULL)
    {
        while(fgets(buf_ps, 1024, ptr)!=NULL)
        {
          if(strcmp(buf_ps,"\n")!=0){
            memcpy(result,buf_ps,sizeof(char)*512);

            // strcat(result, buf_ps);
          }

           if(strlen(result)>1024)
               break;
        }
        pclose(ptr);
        ptr = NULL;
    }
    else
    {
        printf("popen %s error\n", ps);
        return -1;
    }
    return 0;
}



#endif
