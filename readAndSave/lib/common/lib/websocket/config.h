#ifndef _WEBSOCKET_CONFIG_CONFIG_H_
#define _WEBSOCKET_CONFIG_CONFIG_H_
#include <string>
#include "constants.h"
namespace websocket {
	namespace config {
		typedef std::string string;
		static int const BUFF_LEN = 2048 * 2048;//buff_size
		static bool TSL = false;//is uesd translation security layer protocol, default is not and do not implement it for now
		static string const port = "80";//default port without TSL
		static string const wss_port = "443";//default port with TSL
		static int const MAX_QUEUE_LENGTH = 100;//send message queue length
		static int const FRAGMENT_SIZE = 256;//websocket data frame default fragment size, 0 present unlimited
		static bool SUB_PROTOCOL = false;
		static bool EXTENSION = false;
		static const int RD_SIZE = 50;//the bytes of reading data from socket every time
		static const int WR_SIZE = 50;
		static const int AI_FAMLIY_USED = constants::connection::AI_FAMILY_IPv4;//the protocol family used in connection
		static const int HEART_BEAT = constants::heart_beat_type::SERVER;
		static const int SELECT_WAIT_TIME = 20000;//microseconds as unit
        static const int CLOSE_CONFIRM_WAIT_TIME = 30000;//
        static const int PING_WAIT_TIME = 1200000;//
		static const int COMMUNICATION_TYPE = constants::communication::SEND_ONE_BY_ONE;//type of message send and recv; 
        static const int LOG_MSG = false;
        static const int RECORD_MSG = true;
	}
}
#endif
