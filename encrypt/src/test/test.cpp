#include "response_data.h"
#include "sha256.h"

#include <iostream>
#include <string>
using namespace std;


 int main(int argc, char const *argv[]) {

//string v_key="key";
string v_keytype="public";
string v_origin_data="helloworld";


string usrname="root";
string password="admin";
string sn="jy5654j44t4545y454";
string v_key=picosha2::hash256_hex_string(usrname+password+sn);


ResponseData  data(v_key,v_keytype,v_origin_data);
ResponseData  dedata=ResponseData::FromJson(data.Json());

dedata.DecodeSecretData(v_key);
cout<<"decode origin:"<<dedata.Json()<<endl;
cout<<"decode _secret_data:"<<dedata._secret_data<<endl;
cout<<"decode _data:"<<dedata._data<<endl;

  return 0;
}
