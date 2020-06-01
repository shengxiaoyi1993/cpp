#include "ws_buff.h"
#include "error_debug.h"
#include "helper.h"
#include <iostream>
namespace websocket {
	namespace buff {

		buff::buff() {
			memset(&buff_array, 0, sizeof(buff_array));
			length = 0;
		}
		bool buff::input_data(string &data) {
			if ((length + data.size()) > config::BUFF_LEN) {
				progressor::error_debug::log("BUFF IS FULL!");
				return false;
			}
			V8 data_ = handler::helper::string_transform_uint8_t(data);
			buff_array.insert(buff_array.end(), data_.begin(), data_.end());
			length = buff_array.size();
			return true;
		}

		bool buff::input_data(V8 &data) {
			if ((length + data.size()) > config::BUFF_LEN) {
				progressor::error_debug::log("BUFF IS FULL!");
				return false;
			}
			buff_array.insert(buff_array.end(), data.begin(), data.end());
			length = buff_array.size();
			return true;
		}

		bool buff::input_data(char data[], int n) {
			uint8_t *data_ = (uint8_t *)data;
			for(int i = 0; i < n; i++) {
				//std::cout << std::hex << (int)*data_ << "/";
				buff_array.push_back(*data_);
				data_++;
			}
			//std::cout << std::endl;
			length = buff_array.size();
			return true;
		}

		V8 buff::output_data() {
			V8 buff;
			buff.insert(buff.end(), buff_array.begin(), buff_array.end());
			buff_array.clear();
			length = 0;
			return buff;
		}

		bool buff::is_buff_empty() {
			if (length == 0) {
				return true;
			}
			else {
				return false;
			}
		}
	}
}
