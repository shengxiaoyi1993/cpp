#ifndef STACK_H
#define STACK_H


#include<iostream>
#include<vector>
#include<stdexcept>


using namespace std;
template <typename T>
class Stack{
  // Stack();

private:
  vector<T> elems;

public:
  void push(T const& v_elem);
  void pop();
  T top() const;
  bool empty() const {
    return elems.empty();
  }


};

template <typename T>
void Stack<T>::push(T const& v_elem){
  elems.push_back(v_elem);
}

template <typename T>
void Stack<T>::pop(){
  if(elems.empty()){
    throw out_of_range("elems.empty");
  }
  elems.pop_back();
}

template <typename T>
T Stack<T>::top() const{
  if(elems.empty()){
    throw out_of_range("elems.empty");
  }

  return elems.back();
}




#endif
