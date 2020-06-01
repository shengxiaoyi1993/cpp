#include "websocket/websocket_client.h"
#include "websocket/constants.h"
#include <iostream>
//#include <unistd.h>
int info();

int main() {
	// websocket::client::client ws_client;
	// while(true) {
	// 	info();
	// 	char key;
	// 	std::cin >> key;
	// 	if(key == 'C') {
	// 		std::string uri = "ws://192.168.1.66:60802/?q={\"secret_auth_param\":{\"authcode\":\"c14e7fac28c9eaa81c5117aa38e1145c5a60758458801fc74f466c9fb380c7f4\",\"timecode\":\"\",\"username\":\"zxd\"},\"secret_data\":\"9322b81b7ff9bb78f50c60d08c57ac8d24dc77b3df5f3db0ddb7390681cc6c27238e0e9afa649a6cb07a633a0ec3b485\"}";
	// 		bool connect_tag = ws_client.ws_connect(uri);
	// 	}
	// 	if(key == 'S') {
	// 		std::string msg = "ws://192.168.106.130:8080/echo";
	// 		ws_client.ws_send(msg);
	// 	}
	// 	if(key == 'D') {
	// 		bool close_tag = ws_client.ws_close();
	// 		if(close_tag == true) {
	// 			std::cout << "close success!" << std::endl;
	// 		}
	// 		else {
	// 			std::cout << "close fail!" << std::endl;
	// 		}
	// 	}
  //
	// 	if(key == 'R') {
	// 		while(ws_client.get_status() == 4) {
	// 			std::string message = "NONE";
	// 			ws_client.ws_recv(message);
	// 			std::cout << "message: " << message << std::endl;
	// 		}
	// 	}
	// 	if(key == 'E') {
	// 		break;
	// 	}
	// 	std::cout << "ws_client.get_status()" << ws_client.get_status() << std::endl;
	// }

  int CLOSE = 0;
  bool tag;
  websocket::client::client ws_client;
  std::string uri = "ws://192.168.1.66:8800/";
  bool connect_tag = ws_client.ws_connect(uri);
  std::string msg = "ws://192.168.106.130:8080/echo";
  ws_client.ws_send(msg);
  ws_client.ws_poll();
  int i = 0;
  while(ws_client.get_status() == 4){
    std::string re_message = "NONE";
    ws_client.ws_recv(re_message);
    i++;
    std::cout << "re_uri_send: " << "No: " << i << "/" << re_message << "/" << ws_client.get_status() <<std::endl;
  }
  return 0;
}

int info() {
	std::cout << "press a key for continue:" << std::endl;
	std::cout << "  C:connect\n" <<"  S:sennd message\n" << "  D:disconnect\n" << "  R:receive message\n" << "  E:exit\n"<< std::endl;
	return 0;
}
