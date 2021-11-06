#include <iostream>
#include "restclient-cpp/restclient.h"
#include "restclient-cpp/connection.h"


using namespace std;

void test_simple();
void test_complex();


int main()
{

  return 0;
}


void test_simple(){
  RestClient::Response res=RestClient::get("http://root:admin@192.168.1.170/cgi-bin/UVSSapi.cgi?{%22cmd%22:%22get%22,%22key%22:%22server%20ip%22}");
  cout<<"res body:"<<res.body;

  cout << "Hello World!" << endl;
}


void test_complex(){
  RestClient::Connection httpcon("http://192.168.1.170/cgi-bin/UVSSapi.cgi");
  httpcon.SetBasicAuth("root","admin");
  httpcon.SetTimeout(5);
  RestClient::Response res=httpcon.get("{%22cmd%22:%22get%22,%22key%22:%22server%20ip%22}");
  cout<<"res"<<res.body<<endl;
}
