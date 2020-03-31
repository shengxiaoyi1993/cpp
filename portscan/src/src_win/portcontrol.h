
#ifndef PORTCONTROL_H_
#define PORTCONTROL_H_
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include "../common/executecmd.h"
#include "../common/basic.h"

using namespace std;

namespace portcontrol_win{


inline  string  getName(int port,const string &port_type){
  string name="\"add "+port_type+" port "+integerToString(port)+"\"";
  return name;
}


inline bool setFirewallRule(
  string opate,
  int port,
  string name,
  string port_type,
  string inout,
  string action){

  string cmd_add="netsh advfirewall firewall "
  +opate+" rule "
   "name="+name
   +" dir="+inout
   +" protocol="+port_type
   +" localport="+integerToString(port)
   +"   action="+action;
  char result[512]={0};
  cout<<"cmd_add:"<<cmd_add<<endl;
  // return -1;

  int flag =executeCMD(cmd_add.c_str(),result);
  cout<<"result:"<<result<<endl;

  if(flag!=0){
    return true;
  }
  else{
    if(strcmp(result,"Ok.\n") == 0){
      return true;
    }
    else{
      return false;
    }
  }
}


inline bool addPortToFirewall(int port,const string &port_type){
   string name=getName(port,port_type);
  string inout="in";
  string action="allow";
  string opate="add";

  return setFirewallRule(
    opate,
    port,
   name,
   port_type,
   inout,
   action);
}


inline bool delPortToFirewall(int port,const string &port_type){
  string name=getName(port,port_type);

  string cmd_add="netsh advfirewall firewall "
  "delete rule "
   "name="+name;
  char result[512]={0};
  cout<<"cmd_add:"<<cmd_add<<endl;
  int flag =executeCMD(cmd_add.c_str(),result);
  cout<<"result:"<<result<<endl;

  if(flag!=0){
    return true;
  }
  else{
    if(strcmp(result,"Ok.\n") == 0){
      return true;
    }
    else{
      return false;
    }
  }
}

inline bool setPortToFirewall(int port,const string &port_type,bool isable){

  string setable;
  if(isable == true){
    setable="yes";
  }
  else{
    setable="no";
  }
 string name=getName(port,port_type);
  string cmd_add="netsh advfirewall firewall "
  "set rule "
   "name="+name+ " new enable="+setable;
  char result[512]={0};
  cout<<"cmd_add:"<<cmd_add<<endl;
  int flag =executeCMD(cmd_add.c_str(),result);
  cout<<"result:"<<result<<endl;

  if(flag!=0){
    return true;
  }
  else{
    if(strcmp(result,"Ok.\n") == 0){
      return true;
    }
    else{
      return false;
    }
  }
}

}


#endif
