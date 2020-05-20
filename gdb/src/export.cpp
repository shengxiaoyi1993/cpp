#include "export.h"

void printList(){
  std::vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.push_back(1);
  for (int i = 0; i < v.size(); i++) {
    std::cout<<v[i]<<std::endl;
  }
  return;

}



void wrongFunc(){
  int num=7/0;

  int list[10];
  list[10]=88;

  return;
}
