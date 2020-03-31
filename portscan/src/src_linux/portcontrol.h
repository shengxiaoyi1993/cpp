
#ifndef PORTCONTROL_H_
#define PORTCONTROL_H_
#include <iostream>
#include <string>
#include <unistd.h>
#include "../common/executecmd.h"
#include "../common/basic.h"


using namespace std;
namespace portcontrol_linux{

//测试某个断口是否被防火墙允许
//input: port
//ouput: y/n
/**
 * [isFirewallAllow 检测一个端口是否被防火墙允许]
 * @param  port [端口号]
 * @return      [true:则表示端口被允许]
 */

inline bool isFirewallAllow(int port,const string &port_type){
  string cmd="sudo firewall-cmd --query-port="
  +integerToString(port)+
  "/"+port_type;
  char result[512]={0};
  int flag =executeCMD(cmd.c_str(),result);
  // cout<<"cmd:"<<cmd<<endl;
  // printf("result:%s\n",result);
  if(flag!=0){
    return true;
  }
  else{
    if(strcmp(result,"yes\n") == 0){
      return true;
    }
    else{
      return false;
    }
  }
}

inline bool addPortToFirewall(int port,const string &port_type){
  string cmd_add="sudo firewall-cmd --zone=public --add-port="
  +integerToString(port)+"/"+port_type+" --permanent";
  char result[512]={0};
  int flag =executeCMD(cmd_add.c_str(),result);

  if(flag!=0){
    return true;
  }
  else{
    if(strcmp(result,"success\n") == 0){
      return true;
    }
    else{
      return false;
    }
  }
}

inline bool reLoadFirewall(){
  string cmd="sudo firewall-cmd --reload";
  char result[512]={0};
  int flag =executeCMD(cmd.c_str(),result);
  // cout<<"cmd:"<<cmd<<endl;

  if(flag!=0){
    return true;
  }
  else{
    if(strcmp(result,"success\n") == 0){
      return true;
    }
    else{
      return false;
    }
  }
}



inline bool delPortToFirewall(int port,const string &port_type){
  string cmd_add="sudo firewall-cmd --zone=public --remove-port="
  +integerToString(port)+"/"+port_type+" --permanent";
  char result[512]={0};
  int flag =executeCMD(cmd_add.c_str(),result);
  // cout<<"cmd_add:"<<cmd_add<<endl;
  // printf("result:%s\n",result);

  if(flag!=0){
    return true;
  }
  else{
    if(strcmp(result,"success\n") == 0){
      return true;
    }
    else{
      return false;
    }
  }
}


}
#endif
