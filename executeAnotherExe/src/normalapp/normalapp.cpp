#include<iostream>
#include <sys/types.h>
#include <unistd.h>

using namespace std;


int  main(int argc, char const *argv[]) {
  printf("normalapp pid=%d\n", getpid());
  printf("%s\n", "normalapp end!");
  return 0;
}
