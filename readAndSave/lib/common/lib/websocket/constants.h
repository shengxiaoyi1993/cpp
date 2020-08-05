#ifndef _WEBSOCKET_CONFIG_CONSTANTS_H_
#define _WEBSOCKET_CONFIG_CONSTANTS_H_
#include <string>
#include "ws_message.h"
#include <vector>
#include <stdint.h>
#ifdef _WIN32
#include <WinSock2.h>
#else
#include <sys/socket.h>
#endif
namespace websocket {
	namespace constants {
		namespace frame {
			namespace opcode {
				static const int none = -1;
				static const uint8_t continuation = 0x0;
				static const uint8_t text = 0x1;
				static const uint8_t binary = 0x2;
				static const uint8_t rsv3 = 0x3;
				static const uint8_t rsv4 = 0x4;
				static const uint8_t rsv5 = 0x5;
				static const uint8_t rsv6 = 0x6;
				static const uint8_t rsv7 = 0x7;
				static const uint8_t close = 0x8;
				static const uint8_t ping = 0x9;
				static const uint8_t pong = 0xA;
				static const uint8_t rsv11 = 0xB;
				static const uint8_t rsv12 = 0xC;
				static const uint8_t rsv13 = 0xD;
				static const uint8_t rsv14 = 0xE;
				static const uint8_t rsv15 = 0xF;
			}
			static const std::string hanshark_key = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
			static std::string PING_MESSAGE = "THIS IS A PING FRAME";
			namespace close_frame {
				static std::string CLOSE_NORMAL = "CLOSE,NORMAL";
			}
		}
		namespace connection {
			static const int AI_FAMILY_IPv4 = AF_INET;
			static const int AI_FAMILY_IPv6 = AF_INET6;
		}
		namespace error {
			static const int ERROR_GET_ADDR_INFO = 0;
			static const int ERROR_TCP_CONNECT_FAILED = 1;
			static const int ERROR_WEBSOCKET_CONNECT_FAILED = 2;
			static const int ERROR_URI_SCHEME = 3;
			static const int ERROR_URI_HOST = 4;
			static const int ERROR_URI_PORT = 5;
			static const int ERROR_URI_PATH = 6;
			static const int ERROR_URI_QUERY = 7;
			static const int ERROR_URI_IS_NULL = 8;
			static const int ERROR_SOCKFD_CREATE_FAILD = 9;
			static const int ERROR_INET_PTON_FAILD = 10;
		}

		namespace communication {
			static const int SEND_AND_RECV = 0;//send message then wait message of server;
			static const int SEND_ONE_BY_ONE = 1;//only can send message after last message send action complete, then use ws_poll() get message of server;
			static const int SEND_BY_STREAM_TYPE = 2;//you can send message at anytime, they will be store in the message queue, ws_poll() get message of server;
		}

		namespace connection_status {
			static const int ST_CLOSED = 0;
			static const int ST_CONNECTING_TCP = 1;
			static const int ST_CONNECTED_TCP = 2;
			static const int ST_CONNECTING_WS = 3; 
			static const int ST_ESTABLISHED = 4;
			static const int ST_CLOSING_WS = 5;
			static const int ST_CLOSED_WS = 6;
			static const int ST_CLOSING_TCP = 7;
		}

		namespace heart_beat_type {
			static const int CLIENT = 0;
			static const int SERVER = 1;
			static const int NONE = -1;
		}
	}
}
#endif
