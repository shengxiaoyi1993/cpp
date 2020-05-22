#include "stack.h"
#include <iostream>

using namespace std;
int main(){

  try{
    Stack<int> intStack;
    std::cout << "isempty:" << intStack.empty() <<'\n';
    intStack.push(4);
    cout<<"top:"<<intStack.top()<<endl;
    intStack.pop();
    cout<<"top:"<<intStack.top()<<endl;
  }
  catch(exception const& ex){
    cerr<<"exception:"<<ex.what()<<endl;
    return EXIT_FAILURE;

  }




}
