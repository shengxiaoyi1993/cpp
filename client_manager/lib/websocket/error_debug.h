#ifndef _WEBSOCKET_PROGRESSOR_ERROR_DEBUG_H_
#define _WEBSOCKET_PROGRESSOR_ERROR_DEBUG_H_
#include <string>
#include <stdint.h>
namespace websocket {
	namespace progressor {
		namespace error_debug {
			bool log(std::string str);
			bool error_process(int code, std::string info = "");
		}
	}
}
#endif
