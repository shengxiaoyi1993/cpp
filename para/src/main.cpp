#include <iostream>

using namespace std;


void lvalue_reference_test(void){
  int a = 10;
  int& refA = a; // refA是a的别名， 修改refA就是修改a, a是左值，左移是左值引用

  cout<<"before modify:"<<endl;
  cout<<"a:"<<a<<endl;
  cout<<"refA:"<<refA<<endl;

  a=7;
  cout<<"after modify a:"<<endl;
  cout<<"a:"<<a<<endl;
  cout<<"refA:"<<refA<<endl;

  refA=5;
  cout<<"after modify refA:"<<endl;
  cout<<"a:"<<a<<endl;
  cout<<"refA:"<<refA<<endl;

}

class A {
  public:
    int a;
};
A getTemp()
{
    return A();
}


void value_reference(int && i){
  cout<<__func__<<endl;
  cout<<"r:i:"<<i<<endl;
  i=9;
}

void value_reference(int & i){
  cout<<__func__<<endl;
  cout<<"l:i:"<<i<<endl;
  i=6;

}

template<typename T>
bool compare(const T& value1, const T& value2)
{
	return value1 == value2;
}

struct S {
    double operator()(char, int&); // 这个函数的返回类型是 double
};




int main()
{

  // int&& a = 1; //实质上就是将不具名(匿名)变量取了个别名
  // cout<<"a:"<<a<<endl;



  // int b = 1;
  // int && c = b; //编译错误！ 不能将一个左值复制给一个右值引用
  // cout<<"c:"<<c<<endl;


  // A && a = getTemp();   //getTemp()的返回值是右值（临时变量）
  // cout<<"a.a:"<<a.a<<endl;
  //




  // value_reference(1);
  // int v=9;
  // value_reference(v);
  // cout<<"r:v:"<<v<<endl;

  //
  // int a=6;
  // int b=6;
  // cout<<compare(a,b)<<endl;


  std::result_of<S(char, int&)>::type foo = 3.14; // 使用这样的写法会推导出模板参数中函数的返回值类型
  typedef std::result_of<S(char, int&)>::type MyType; // 是 double 类型吗?
  std::cout << "foo's type is double: " << std::is_same<double, MyType>::value << std::endl;
  return 0;




  return 0;

}
