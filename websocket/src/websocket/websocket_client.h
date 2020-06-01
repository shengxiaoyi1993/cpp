#ifndef _WEBSOCKET_CLIENT_H_
#define _WEBSOCKET_CLIENT_H_

#include <string>
#include <vector>
#include "uri.h"//#include<websocket/progressor/uri.h>
#include "ws_message.h"
#include "ws_message_queue.h"
#include "config.h"
#include "ws_buff.h"
#include <stdint.h>
#include <stdio.h>
#include "constants.h"
#ifdef _WIN32
typedef SOCKET socket_t;
#else
typedef int socket_t;
#endif

namespace websocket {
	namespace client {
		typedef std::string string;
		typedef std::vector<uint8_t> V8;
		typedef progressor::uri::uri uri;
		typedef message::request request;
		typedef message::response response;
		typedef websocket::buff::buff buff;
		typedef message_queue::send_queue send_queue;
		typedef message_queue::recv_queue recv_queue;
		typedef message_queue::queue_unit queue_unit;
		class client {
			enum status { CLOSED = constants::connection_status::ST_CLOSED, CONNECTING_TCP = constants::connection_status::ST_CONNECTING_TCP, 
				CONNECTED_TCP = constants::connection_status::ST_CONNECTED_TCP, CONNECTING_WS = constants::connection_status::ST_CONNECTING_WS, 
				ESTABLISHED = constants::connection_status::ST_ESTABLISHED, CLOSING_WS = constants::connection_status::ST_CLOSING_WS, 
				CLOSED_WS = constants::connection_status::ST_CLOSED_WS, CLOSING_TCP = constants::connection_status::ST_CLOSING_TCP};
		private:
			socket_t sockfd;
			int status;
			send_queue wx_queue;
			recv_queue rx_queue;
			buff rx_buff;
			buff wx_buff;
		private:
			bool tcp_connect(const char *host, const char *serv);
			bool websocket_connect(string &path, string &host, string &port);
			bool send_buff_data(const char *ptr, int length);
			bool get_buff_data(string &ptr);
			bool select_read(int timeout = config::SELECT_WAIT_TIME);
			bool select_write();
			bool select_all();
			bool wx_poll();
			bool rx_poll();
			bool ws_pong(V8 &message);
			queue_unit get_message();
		public:
			client();
			~client();
			int get_status();
			bool get_buff_data();
			bool send_buff_data();
			bool ws_connect(string &ws_uri);
			bool ws_send(V8 &message);
			bool ws_send(string &message);
			bool ws_ping(string &message);
			bool ws_ping();
			bool ws_ping(V8 &message);
			bool ws_close(string &message);
			bool ws_close();
			bool ws_close(V8 &message);
			bool ws_poll();
			bool ws_recv(string &str);
			bool ws_recv(V8 &data);
		};
	}
}

#endif


