#include <stdio.h>
#include "log.h"

 int main(int argc, char const *argv[]) {
   log_trace("log_trace");
   log_debug("log_debug");
   log_error("log_error");
   log_warn("log_warn");
   log_fatal("log_fatal");
   log_info("log_info");

  return 0;
}
