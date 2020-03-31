#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#ifdef __WIN32
#include "src_win/portcontrol.h"
#elif __linux
#include "src_linux/portcontrol.h"

#endif

void testPortScan();


int main(){
testPortScan();
}



#ifdef __WIN32

void testPortScan(){
  //   int port =777;
//   string name="\"add 777 port\"";
//   string port_type="tcp";
//   string inout="in";
//   string action="block";
//   string opate="set";
//
//
//
//  int flag = setFirewallRule(opate,
//    port,
//   name,
//   port_type,
//   inout,
//   action
// );
// if(flag == true){
//   std::cout << "succeed" << '\n';
// }
// else{
//   std::cout << "failed" << '\n';
//
// }


 bool flag=portcontrol_win::addPortToFirewall(888,"tcp");
if(flag == true){
  cout<<"addPortToFirewall succeed"<<endl;
}
else{
  cout<<"addPortToFirewall failed"<<endl;
}


flag=portcontrol_win::setPortToFirewall(888,"tcp","no");
if(flag == true){
 cout<<"setPortToFirewall able succeed"<<endl;
}
else{
 cout<<"setPortToFirewall able failed"<<endl;
}

flag=portcontrol_win::setPortToFirewall(888,"tcp","yes");
if(flag == true){
 cout<<"setPortToFirewall disable succeed"<<endl;
}
else{
 cout<<"setPortToFirewall disable failed"<<endl;
}



 flag=portcontrol_win::delPortToFirewall(888,"tcp");
if(flag == true){
  cout<<"delPortToFirewall succeed"<<endl;
}
else{
  cout<<"delPortToFirewall failed"<<endl;
}




}

#elif __linux


void testPortScan(){

  const int port =345;
  const string str_porttype="tcp";
    bool flag=portcontrol_linux::isFirewallAllow(port,str_porttype);
    if(flag==true){
      cout<<"port allow"<<endl;
    }
    else{
      cout<<"port is not allowed"<<endl;
      bool flag_add =portcontrol_linux::addPortToFirewall(port,str_porttype);
      if(flag_add == true){
        cout<<"add port succeed"<<endl;
        if(portcontrol_linux::reLoadFirewall() == true){
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

    if(portcontrol_linux::isFirewallAllow(port,str_porttype) == true){
      cout<<"port allow"<<endl;
      if( portcontrol_linux::delPortToFirewall( port,str_porttype) == true){
        cout<<"port del succeed"<<endl;
      }
      else{
        cout<<"port del failed"<<endl;
      }


      if(portcontrol_linux::reLoadFirewall() == true){
        cout<<"restart firewall succeed" <<endl;
      }
      else{
        cout<<"restart firewall failed" <<endl;
      }

      if(portcontrol_linux::isFirewallAllow(port,str_porttype) == true){
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

#endif
