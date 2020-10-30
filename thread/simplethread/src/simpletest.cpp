#include <pthread.h>
#include <iostream>
using namespace std;

pthread_mutex_t         _mutex;


void * print(void*) {
  static  int count=0;
  while (true) {
    count++;
    if(count == 2000){
      pthread_mutex_lock(&_mutex);
      std::cout << "in lock state" << '\n';
      pthread_mutex_unlock(&_mutex);

    }
    std::cout << "in chlid thread" << '\n';
  }
}



int main(){
  pthread_t pid;
  pthread_mutex_init(&_mutex,NULL);
  int flag=pthread_create(&pid,NULL,print,NULL);
  if(flag == 0){
    std::cout << "succeed to start thread" << '\n';
  }
  else{
    std::cout << "fail to start thread" << '\n';

  }
  pthread_mutex_lock(&_mutex);
  int count=0;
  while (true) {
    cout<<"in parent thread:"<<count<<endl;
    count++;
  }
  pthread_mutex_unlock(&_mutex);

  return 0;
}
