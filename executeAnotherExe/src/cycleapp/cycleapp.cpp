#include<iostream>
#include <sys/types.h>
#include <unistd.h>

using namespace std;


int  main(int argc, char const *argv[]) {

  while (true) {
    printf("cycleapp pid=%d\n", getpid());
    printf("%s\n", "in cycleapp");
    sleep(5);
  }
  return 0;
}
