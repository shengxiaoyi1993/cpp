#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "src_linux/portcontrol.h"


int main(){

const int port =345;
const string str_porttype="tcp";


  bool flag=isFirewallAllow(port,str_porttype);
  if(flag==true){
    cout<<"port allow"<<endl;
  }
  else{
    cout<<"port is not allowed"<<endl;
    bool flag_add =addPortToFirewall(port,str_porttype);
    if(flag_add == true){
      cout<<"add port succeed"<<endl;
      if(reLoadFirewall() == true){
        cout<<"restart firewall succeed" <<endl;
      }
      else{
        cout<<"restart firewall failed" <<endl;
      }


    }
    else{
      cout<<"add port fail"<<endl;
    }
  }

  if(isFirewallAllow(port,str_porttype) == true){
    cout<<"port allow"<<endl;
    if( delPortToFirewall( port,str_porttype) == true){
      cout<<"port del succeed"<<endl;
    }
    else{
      cout<<"port del failed"<<endl;
    }


    if(reLoadFirewall() == true){
      cout<<"restart firewall succeed" <<endl;
    }
    else{
      cout<<"restart firewall failed" <<endl;
    }

    if(isFirewallAllow(port,str_porttype) == true){
      cout<<"port allow"<<endl;
    }
    else{
      cout<<"port is not allowed"<<endl;
    }



  }
  else{
    cout<<"port is not allowed"<<endl;
  }


}
