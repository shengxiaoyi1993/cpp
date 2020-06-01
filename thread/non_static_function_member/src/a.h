#include<iostream>

using namespace std;

class a
{
public:
  static void* FunctionA(void* pa)
  {
    a* _a =(a*)pa;
    _a-> menber = 1;
    cout<<_a-> menber<<endl;
    _a->f(NULL);
  }
static void* f(void* p)
{
 cout<<"f被调用了"<<endl;
}

void* g(void* p)
{
 cout<<"g被调用了"<<endl;
}

void testthis() {
  cout<<"testthis:"<<this->menber<<endl;

}
private:
  int menber;
};
