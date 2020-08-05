#include "websocket_client.h"
//#include<unistd.h>
#include "helper.h"
#include "error_debug.h"
#include "constants.h"
#include "config.h"
#include <iostream>

#ifdef _WIN32
#include <WinSock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/select.h>
#include <sys/time.h>
#define closesocket(s) close(s)
#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif
#endif // _WIN32
#define NUM_THREADS 2

namespace websocket {
	namespace client {
		client::client() :status(CLOSED), rx_buff(), wx_buff(), wx_queue(), rx_queue() {
			sockfd = INVALID_SOCKET;
		}

		client::~client() {
			if(sockfd != INVALID_SOCKET) {
				closesocket(sockfd);
				sockfd = INVALID_SOCKET;
			}
			status = CLOSED;
		}

		bool client::ws_connect(string &uri_str) {
			uri ws_uri(uri_str);
			string host = ws_uri.get_host();
			string port = ws_uri.get_port();
			string path = ws_uri.get_path() + ws_uri.get_query();
			bool tcp_tag = tcp_connect(host.c_str(), port.c_str());
			if (tcp_tag == false) return false;
			bool ws_tag = websocket_connect(path, host, port);
			if (ws_tag == false) return false;
#ifdef _WIN32
			u_long on = 1;
			ioctlsocket(sockfd, FIONBIO, &on);
#else
			fcntl(sockfd, F_SETFL, O_NONBLOCK);
#endif
			return true;
		}

		bool client::tcp_connect(const char *host, const char *serv) {
#ifdef _WIN32
			INT rc;
			WSADATA wsaData;

			rc = WSAStartup(MAKEWORD(2, 2), &wsaData);
			if (rc) {
				return false;
			}
#endif		
			if(status == ESTABLISHED) return true;
			int n;
			struct addrinfo hints, *res, *ressave;
			memset(&hints, 0, sizeof(hints));
			hints.ai_family = config::AI_FAMLIY_USED;
			hints.ai_socktype = SOCK_STREAM;
			if (n = getaddrinfo(host, serv, &hints, &res) != 0) {
				progressor::error_debug::error_process(constants::error::ERROR_GET_ADDR_INFO);
				//gai_strerror(n);
				status = CLOSED;
                return false;
			}
			ressave = res;
			do {
				if(status != CLOSED) {
					closesocket(sockfd);
					sockfd = INVALID_SOCKET;
					status = CLOSED;
				}
				if (sockfd != INVALID_SOCKET) return true;
				sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
				if (sockfd < 0) {
					//todo:record error
					continue;
				}
				//for test port
				//struct sockaddr_in client_addr;
				//memset(&client_addr, 0, sizeof(client_addr));
				//client_addr.sin_family = AF_INET;
				//client_addr.sin_addr.s_addr = htonl(INADDR_ANY);
				//client_addr.sin_port = htons(1234);
				//bind(sockfd, (sockaddr *)&client_addr, sizeof(client_addr));
				if (connect(sockfd, res->ai_addr, res->ai_addrlen) == 0) {
					break;
				}
				closesocket(sockfd);
				sockfd = INVALID_SOCKET;
			} while ((res = res->ai_next) != NULL);

			if (res == NULL) {
				freeaddrinfo(ressave);
				progressor::error_debug::error_process(constants::error::ERROR_TCP_CONNECT_FAILED, "by addrinfo");
				status = CLOSED;
				return false;
			}
			freeaddrinfo(ressave);
			status = CONNECTED_TCP;
			return true;
		}

		bool client::websocket_connect(string &path, string &host, string &port) {
			if(status == ESTABLISHED) return true;
			status = CONNECTING_WS;
			request ws_request(path, host, port);
			string request_str = ws_request.progress_request();
			const char* request = request_str.c_str();
			send_buff_data(request, strlen(request));
			string response_ptr;
			bool get_tag = get_buff_data(response_ptr);
			if (get_tag == false) {
				progressor::error_debug::log("error:GET_WS_RESPONCE_FAIL");
				return false;
			}
			response ws_response(response_ptr);
			string key = ws_request.get_sec_websocket_key();
			if (ws_response.responce_check(key) == true) {
				status = ESTABLISHED;
				progressor::error_debug::log("WEBSOCKET_CONNECT_SUCCESS");
				return true;
			}
			else {
				status = CLOSED;
				progressor::error_debug::log("error:WEBSOCKET_CONNECT_FAIL");
				return false;
			}
		}

		bool client::send_buff_data(const char *ptr, int length) {
			if (status != CONNECTING_WS) return false;
			if (handler::helper::writen(sockfd, ptr, length) >= 0) {
				return true;
			}
			else {
				return false;
			}
		}

		bool client::send_buff_data() {
			while (wx_queue.queue_is_empty() != true) {
				V8 data = wx_queue.output_message();
				wx_buff.input_data(data);
				if (config::COMMUNICATION_TYPE == constants::communication::SEND_AND_RECV) {
					select_write();
					wx_poll();
					select_read();
					rx_poll();
				}
				else if (config::COMMUNICATION_TYPE == constants::communication::SEND_ONE_BY_ONE) {
					select_write();
					wx_poll();
				}
			}
			return true;
		}

		bool client::get_buff_data(string &ptr) {
			if (status != CONNECTING_WS) return false;
			char response[2000] = "";
			select_read(config::PING_WAIT_TIME);
			bool tag = handler::helper::read_response(sockfd, response);
			ptr = response;
			return tag;
		}

		bool client::get_buff_data() {
			while (rx_buff.is_buff_empty() == false) {
				V8 message = rx_buff.output_data();
				rx_queue.input_message(message);
			}
			return true;
		}

		bool client::ws_send(V8 &message) {
			if (status != ESTABLISHED) return false;
			wx_queue.input_message(message);
			send_buff_data();
			return true;
		}

		bool client::ws_send(string &message) {
			if (status != ESTABLISHED) return false;
			wx_queue.input_message(message);
			send_buff_data();
			return true;
		}

		bool client::ws_ping(string &message) {
			if (status != ESTABLISHED) return false;
			wx_queue.input_ping(message);
			send_buff_data();
			return true;
		}

		bool client::ws_ping() {
			if (status != ESTABLISHED) return false;
			wx_queue.input_ping(constants::frame::PING_MESSAGE);
			send_buff_data();
			return true;
		}

		bool client::ws_ping(V8 &message) {
			if (status != ESTABLISHED) return false;
			wx_queue.input_ping(message);
			send_buff_data();
			return true;
		}

		bool client::ws_pong(V8 &message) {
			if (status != ESTABLISHED) return false;
			wx_queue.input_pong(message);
			send_buff_data();
			return true;
		}


		bool client::ws_close(string &message) {
			if (status != ESTABLISHED) return false;
			wx_queue.input_close(message);
			send_buff_data();
			status = CLOSING_WS;
			return true;
		}

		bool client::ws_close() {
			if (status != ESTABLISHED) return false;
			wx_queue.input_close(constants::frame::close_frame::CLOSE_NORMAL);
			send_buff_data();
			status = CLOSING_WS;
			return true;
		}

		bool client::ws_close(V8 &message) {
			if (status != ESTABLISHED) return false;
			wx_queue.input_close(message);
			send_buff_data();
			status = CLOSING_WS;
			return true;
		}

        bool client::ws_poll() {
            if (status != ESTABLISHED && status != CLOSED_WS) return false;
			if (config::COMMUNICATION_TYPE == constants::communication::SEND_BY_STREAM_TYPE) {
				select_all();
				wx_poll();
				rx_poll();
			}
			else if (config::COMMUNICATION_TYPE == constants::communication::SEND_ONE_BY_ONE) {
				select_read();
				rx_poll();
			}
			return true;
		}

		bool client::select_read(int timeout) {
			timeval tv;
			fd_set rfds;
			if (timeout != 0) {
				tv = { timeout / 1000, (timeout % 1000) * 1000 };
			}
			FD_ZERO(&rfds);
			FD_SET(sockfd, &rfds);
			select(sockfd + 1, &rfds, NULL, 0, timeout > 0 ? &tv : 0);
			return true;
		}

		bool client::select_write() {
			int timeout = 0;
			timeval tv;
			fd_set wfds;
			if (config::SELECT_WAIT_TIME != 0) {
				timeout = config::SELECT_WAIT_TIME;
				tv = { timeout / 1000, (timeout % 1000) * 1000 };
			}
			FD_ZERO(&wfds);
			FD_SET(sockfd, &wfds);
			select(sockfd + 1, NULL, &wfds, 0, timeout > 0 ? &tv : 0);
			return true;
		}


		bool client::select_all() {
			int timeout = 0;
			timeval tv;
			fd_set wfds;
			fd_set rfds;
			if (config::SELECT_WAIT_TIME != 0) {
				timeout = config::SELECT_WAIT_TIME;
				tv = { timeout / 1000, (timeout % 1000) * 1000 };
			}
			FD_ZERO(&wfds);
			FD_SET(sockfd, &wfds);
			FD_ZERO(&rfds);
			FD_SET(sockfd, &rfds);
			select(sockfd + 1, &rfds, &wfds, 0, timeout > 0 ? &tv : 0);
			return true;
		}

		bool client::wx_poll() {
			while(wx_buff.is_buff_empty() != true) {
				V8 ptr = wx_buff.output_data();
				int length = ptr.size();
				if (handler::helper::writen(sockfd, (char *)&ptr[0], length) < 0) {
					return false;
				}
			}
			return true;
		}

		bool client::rx_poll() {
			int n;
			int length = config::RD_SIZE;
			while (true) {
				char *data = new char[length+1];
				memset(data, 0 , length+1);
				if ((n = handler::helper::readn(sockfd, data, length)) < length) {
					rx_buff.input_data(data, n);
					delete[] data;
					data = NULL;
					break;
				}
				rx_buff.input_data(data, n);
				delete[] data;
				data = NULL;
			}
			get_buff_data();
			return true;
		}

		bool client::ws_recv(string &str) {
			queue_unit message = get_message();
			//std::cout << "message.type: " << (int)message.type << std::endl; 
			//std::cout << "message.content: " << handler::helper::uint8_t_transform_string(message.unit_str) << std::endl; 
			if (message.type == constants::frame::opcode::none) {
				return false;
			}
			while (message.type != constants::frame::opcode::text && message.type != constants::frame::opcode::binary) {
				if (message.type == constants::frame::opcode::close) {
					if(status != CLOSING_WS)
						ws_close(message.unit_str);
					status = CLOSED_WS;
					return true;
				}
				else if (message.type == constants::frame::opcode::ping) {
					ws_pong(message.unit_str);
					message = get_message();
				}
				else if (message.type == constants::frame::opcode::pong) {
					message = get_message();
				}
				else {
					progressor::error_debug::log("error: UNVALID_FRAME_TYPE_MESSAGE_GET!");
					return false;
				}
			}

			if (message.type == constants::frame::opcode::text) {
				str = handler::helper::uint8_t_transform_string(message.unit_str);
			}
			else if (message.type == constants::frame::opcode::binary) {
				progressor::error_debug::log("error: BINARY_FRAME_TYPE_MESSAGE_GET!");
				return false;
			}
			else {
				progressor::error_debug::log("error: UNVALID_FRAME_TYPE_MESSAGE_GET!");
				return false;
			}
			return true;
		}

		bool client::ws_recv(V8 &data) {
			queue_unit message = get_message();
			if (message.type == constants::frame::opcode::none) {
				return false;
			}
			while (message.type != constants::frame::opcode::text && message.type != constants::frame::opcode::binary) {
				if (message.type == constants::frame::opcode::close) {
					if(status != CLOSING_WS)
						ws_close(message.unit_str);
					status = CLOSED_WS;
					return true;
				}
				else if (message.type == constants::frame::opcode::ping) {
					ws_pong(message.unit_str);
					message = get_message();
				}
				else if (message.type == constants::frame::opcode::pong) {
					message = get_message();
				}
				else {
					progressor::error_debug::log("error: UNVALID_FRAME_TYPE_MESSAGE_GET!");
					return false;
				}
			}

			if (message.type == constants::frame::opcode::text) {
				progressor::error_debug::log("error: TEXT_FRAME_TYPE_MESSAGE_GET!");
				return false;
			}
			else if (message.type == constants::frame::opcode::binary) {
				data.assign(message.unit_str.begin(), message.unit_str.end());
			}
			else {
				progressor::error_debug::log("error: UNVALID_FRAME_TYPE_MESSAGE_GET!");
				return false;
			}
			return true;
		}

		queue_unit client::get_message() {
			if (config::HEART_BEAT == constants::heart_beat_type::CLIENT) {
				if (rx_queue.queue_is_empty() == true) {
					select_read(config::PING_WAIT_TIME);
					rx_poll();
				}
				if(rx_queue.queue_is_empty() == true) {
					ws_ping();
					progressor::error_debug::log("ping send");
					select_read(config::PING_WAIT_TIME);
					rx_poll();
				}
				if (rx_queue.queue_is_empty() == true) {
					progressor::error_debug::log("time out");
					ws_close();
					select_read(config::CLOSE_CONFIRM_WAIT_TIME);
					select_read();
					status = CLOSED;
					closesocket(sockfd);
					sockfd = INVALID_SOCKET;
					queue_unit unit;
					unit.type = constants::frame::opcode::none;
					return unit;
				}
				else{
					progressor::error_debug::log("pong get");
				}
			}
			else if(config::HEART_BEAT == constants::heart_beat_type::SERVER) {
				if (rx_queue.queue_is_empty() == true) {
					progressor::error_debug::log("ping begin to wait");
					select_read(config::PING_WAIT_TIME);
					rx_poll();
					if(rx_queue.queue_is_empty() == true) {
						if(rx_queue.left_frame_is_empty() == false) {
							select_read(config::PING_WAIT_TIME);
							rx_poll();
							if(rx_queue.queue_is_empty() == true) {
								progressor::error_debug::log("time out");
								ws_close();
								select_read(config::CLOSE_CONFIRM_WAIT_TIME);
								rx_poll();
								status = CLOSED;
								closesocket(sockfd);
								sockfd = INVALID_SOCKET;
								queue_unit unit;
								unit.type = constants::frame::opcode::none;
								return unit;
							}
						}
						else {
							progressor::error_debug::log("time out");
							ws_close();
							select_read(config::CLOSE_CONFIRM_WAIT_TIME);
							rx_poll();
							status = CLOSED;
							closesocket(sockfd);
							sockfd = INVALID_SOCKET;
							queue_unit unit;
							unit.type = constants::frame::opcode::none;
							return unit;
						}
					}
					else {
						progressor::error_debug::log("ping message get");
					}
				}
			}
			else {
				if (rx_queue.queue_is_empty() == true) {
					select_read(config::SELECT_WAIT_TIME);
					rx_poll();

				}
				if (rx_queue.queue_is_empty() == true) {
					queue_unit unit;
					unit.type = constants::frame::opcode::none;
					return unit;
				}
			}
			return rx_queue.output_message();
		}

		int client::get_status() {
			return status;
		}
	}
}
