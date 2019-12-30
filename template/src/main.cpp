
#include <iostream>
#include <string>

using namespace std;

typedef struct Func{
  template <typename Z>
  Z const& Min(const Z & a,const Z & b){
    return a < b ? a:b;
  }

}Func;


namespace function{
  template <typename T>
  inline T const& Max (T const& a, T const& b)
  {
      return a < b ? b:a;
  }

};


 class DataFunc{
public:
  DataFunc(){
    m_count=0;
  }
  DataFunc(int v_count){
    m_count=v_count;
  }
  int m_count;

  int getCount() const
  {
    // m_count++;
    cout<<"m_count: "<<m_count<<endl;
    return m_count;
  }
   DataFunc operator+(const DataFunc &d){
     DataFunc tmp;
     tmp.m_count=this->m_count+d.m_count;
     return tmp;
   }
   friend ostream &operator<<(ostream &oput,const DataFunc &d){
     oput<<"count: "<<d.m_count<<endl;
   }

};

template <typename X,typename Y>
void swap(X& a,Y&b){

}

template <typename T>
class Base{
public:
  Base(T v_t){
    t=v_t;
  }
  friend ostream &operator<<(ostream& output,const Base<T>& b){
    output<<"t:"<<b.t<<endl;
  }
  T t;
};




int main ()
{

    // int i = 39;
    // int j = 20;
    // cout << "Max(i, j): " << Max(i, j) << endl;
    //
    // double f1 = 13.5;
    // double f2 = 20.7;
    // cout << "Max(f1, f2): " << Max(f1, f2) << endl;

    // string s1 = "Hello";
    // string s2 = "World";
    // cout << "Max(s1, s2): " << function::Max(s1, s2) << endl;
    //
    //
    // Func func;
    //
    // cout<<" Min(s1,s2): "<<func.Min(s1,s2)<<endl;

    class DataFunc datafunc(1);
    datafunc.getCount();
    class DataFunc datafunc1(4);
    datafunc1.getCount();
    class DataFunc datafunc_sum=datafunc+datafunc1;
    datafunc_sum.getCount();
    cout<<datafunc_sum<<endl;

Base<int> base_int(67);
cout<<base_int<<endl;

Base<double> base_double(67.565);
cout<<base_double<<endl;






   return 0;
}
