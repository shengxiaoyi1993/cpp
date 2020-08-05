#ifndef _BASE64_H_
#define _BASE64_H_
#include <string>
#include <vector>
#include <stdint.h>
namespace websocket {
	namespace handler {
		namespace base64 {
			std::string base64_encode(std::string str);
			std::string base64_encode(std::vector<uint8_t> str);
			std::string base64_decode(std::string str);
		}
	}
}

#endif
