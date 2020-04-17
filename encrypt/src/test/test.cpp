#include "response_data.h"
#include <iostream>
#include <string>
using namespace std;


 int main(int argc, char const *argv[]) {

string v_key="key";
string v_keytype="public";
string v_origin_data="helloworld";


ResponseData  data(v_key,v_keytype,v_origin_data);

cout<<"origin:"<<v_origin_data<<endl;
cout<<"secret:"<<data.Json()<<endl;

  return 0;
}
