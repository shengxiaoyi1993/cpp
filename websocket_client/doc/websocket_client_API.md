#websocket client API

## 1.API
### 1.1 ws_connect
原型：``bool ws_connect(string &ws_uri);``
参数说明：ws_uri 为std::string类型的字符串，例如："ws://127.0.0.1:8800"。
作用说明：建立与对应套接字的websocket连接。

### 1.2 ws_send
原型：``bool ws_send(V8 &message);``
参数说明：message为std::vector<uint8_t>类型，用于传输二进制数据。
作用说明：发送二进制消息。

原型：``bool ws_send(string &message);``
参数说明：message为std::string类型，用于传输文本数据。
作用说明：发送文本消息。

### 1.3 ws_ping
原型：``bool ws_ping(string &message);``
参数说明：message为std::string类型，用于传输数据。
作用说明：发送ping消息。

原型：``bool ws_ping();``
作用说明：发送带默认数据的ping消息，可于config中修改。

原型：``bool ws_ping(V8 &message);``
参数说明：message为std::vector<uint8_t>类型，用于传输数据。
作用说明：发送ping消息。

### 1.4 ws_close
原型：``bool ws_close(string &message);``
参数说明：message为std::string类型，用于传输文本数据。
作用说明：发送关闭连接消息。

原型：``bool ws_close();``
作用说明：发送关闭连接消息。

原型：``bool ws_close(V8 &message);``
参数说明：message为std::vector<uint8_t>，用于传输文本数据。
作用说明：发送关闭连接消息。

### 1.5 ws_recv
原型：``bool ws_recv(string &str);``
参数说明：传入std::string类型数据的引用存储接收到的文本数据。
作用说明：接收对端发来的消息。

原型：``bool ws_recv(V8 &data);``
参数说明：传入std::vectro<uint8_t>类型数据的引用存储接收到的二进制数据。
作用说明：接收对端发来的消息。

### 1.6 ws_poll
原型：``bool ws_poll();``
作用说明：config中COMMUNICATION_TYPE = SEND_AND_RECV，无需调用，调用ws_send(...)发送消息后，会等待对端回应消息，然后直接处理该条消息进入消息队列，再调用ws_recv(...)尝试从消息接收队列中读取消息或发送下一条消息。
config中COMMUNICATION_TYPE = SEND_AND_RECV,无需调用，调用ws_send(...)发送消息后，会等待对端回应消息，调用ws_recv(...)尝试从消息接收队列中读取消息。COMMUNICATION_TYPE == SEND_ONE_BY_ONE，需主动调用。该方法将从sockfd套接字描述符中读取数据到rx_buff中，再将buff中的数据（可能为多条消息或不足一条消息）读入消息队列中。

注：上述所有返回值true代表操作执行成功，false代表操作执行失败。

# 2.EXAMPLE
``` ruby
#include "websocket_client.h"
#include <iostream>
int main() {
	websocket::client::client ws_client;
	std::string uri = "ws://169.254.184.110:1234";
	std::string message = "this is a test message";W
	std::string re_uri;
	bool connect_tag = ws_client.ws_connect(uri);
    if(connection_tag == true) {
    	std::cout << "WEBSOCKET_CONNECT_SUCCESS!"; << std::endl;
        on_connect_success();
    }
    else {
    	std::cout << "WEBSOCKET_CONNECT_SUCCESS!"; << std::endl;
        on_connect_fail();
    }
	ws_client.ws_send(message);
	bool tag = ws_client.ws_recv(re_uri);
	if (tag == true) std::cout << "re_uri: " << re_uri << std::endl;
	ws_client.ws_ping();
	tag = ws_client.ws_recv(re_uri);
	if(tag == true) std::cout << "re_uri: " << re_uri << std::endl;
	ws_client.ws_ping(message);
	tag = ws_client.ws_recv(re_uri);
	if(tag == true) std::cout << "re_uri: " << re_uri << std::endl;
	ws_client.ws_close();
	tag = ws_client.ws_recv(re_uri);
	return 1;
}
```

