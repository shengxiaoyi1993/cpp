#ifndef _SHA1_H_
#define _SHA1_H_
#include <string>
#include <vector>
#include <stdint.h>
namespace websocket {
	namespace handler {
		namespace sha1 {
			std::vector<uint8_t> sha1_encode(std::string str);
		}
	}
}
#endif 
