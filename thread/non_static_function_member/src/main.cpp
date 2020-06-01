#include<iostream>
#include <pthread.h>

#include"a.h"

using namespace std;
int main(){
  a tmpa;
  tmpa.testthis();
  return 0;



//   a tmpa;
//   pthread_t pid;
// int flag=pthread_create(&pid,NULL,&tmpa.FunctionA,(void*)&tmpa);
// if(flag == 0){
//   std::cout << "succeed to start thread" << '\n';
// }
// else{
//   std::cout << "fail to start thread" << '\n';
// }
//
// while (true) {
//   /* code */
// }

}
