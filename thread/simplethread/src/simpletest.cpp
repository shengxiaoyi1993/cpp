#include <pthread.h>
#include <iostream>
using namespace std;

void * print(void*) {
  while (true) {
    /* code */
    std::cout << "in thread" << '\n';

  }
  /* code */
}


int main(){
  pthread_t pid;
  int flag=pthread_create(&pid,NULL,print,NULL);
  if(flag == 0){
    std::cout << "succeed to start thread" << '\n';
  }
  else{
    std::cout << "fail to start thread" << '\n';

  }

  while (true) {
    /* code */
  }
  return 0;
}
