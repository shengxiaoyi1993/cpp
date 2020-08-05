#ifndef _WEBSOCKET_BUFF_H_
#define _WEBSOCKET_BUFF_H_
#include "config.h"
#include <string>
#include <vector>
#include <stdint.h>
#include <string.h>
namespace websocket {
	namespace buff {
		typedef std::string string;
		typedef std::vector<uint8_t> V8;
		class buff {
		private:
			V8 buff_array;
			int length;
		public:
			buff();
			bool input_data(string &data);
			bool input_data(V8 &data);
			bool input_data(char data[], int n);
			V8 output_data();
			bool is_buff_empty();
		};
	}
}

#endif
