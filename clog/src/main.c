#include <stdio.h>
#include "log.h"

 int main(int argc, char const *argv[]) {
   FILE * fp;
   fp=fopen("/home/sxy/Github/cpp/clog/src/log.txt","a+");
   if(fp == NULL ){
     printf("%s\n", "Fail to open" );
     return 0;
   }
   log_set_quiet(true);


   log_add_fp(fp,1);
   log_trace("log_trace");
   log_debug("log_debug");
   log_error("log_error");
   log_warn("log_warn");
   log_fatal("log_fatal");
   log_info("log_info");
   fclose(fp);

  return 0;
}
