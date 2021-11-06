#include "ws_message_queue.h"
#ifdef _WIN32
#include <WinSock2.h>
#else
#include<netinet/in.h>
#endif
#include "config.h"
#include "helper.h"
#include "error_debug.h"
#include <iostream>

namespace websocket {
	namespace message_queue {

		//---------------------------------send_queue-----------------------------------

		send_queue::send_queue() {
			data_left.type = constants::frame::opcode::none;
			data_left.unit_str.clear();
			queue.clear();
		}
		bool send_queue::input_message(string &message) {
			if (queue_is_full() == true) return false;
			//progressor::error_debug::log(message);
			bool input_tag = true;
			if (data_left_is_empty() == false) {
				input_tag = input_string(data_left.unit_str, data_left.type);
			}
			V8 message_new = handler::helper::string_transform_uint8_t(message);
			if (input_tag == true) {
				input_string(message_new, constants::frame::opcode::text);
			}
			return input_tag;
		}

		bool send_queue::input_message(V8 &message) {
			if (queue_is_full() == true) return false;
			bool input_tag = true;
			if (data_left_is_empty() == false) {
				input_tag = input_string(data_left.unit_str, data_left.type);
			}
			if (input_tag == true) {
				data_left.unit_str.clear();
				input_string(message, constants::frame::opcode::binary);
			}
			return input_tag;
		}

		bool send_queue::input_ping(string &message) {
			V8 message_new = handler::helper::string_transform_uint8_t(message);
			bool tag = input_ping(message_new);
			return tag;
		}

		bool send_queue::input_ping(V8 &message) {
			bool tag = input_control_frmae(message, constants::frame::opcode::ping);
			return tag;
		}

		bool send_queue::input_pong(V8 &message) {
			bool tag = input_control_frmae(message, constants::frame::opcode::pong);
			return tag;
		}

		bool send_queue::input_close(string &message) {
			V8 message_new = handler::helper::string_transform_uint8_t(message);
			bool tag = input_close(message_new);
			return tag;
		}

		bool  send_queue::input_close(V8 &message) {
			bool tag = input_control_frmae(message, constants::frame::opcode::close);
			return tag;
		}

		bool send_queue::input_string(V8 &message, opcode_type type) {
			if (config::FRAGMENT_SIZE != 0 && message.size() > (config::FRAGMENT_SIZE)) {
				V8::iterator pos = message.begin();
				int pos_tag = 0;
				while (pos != message.end()) {
					V8 fragement;
					if (pos_tag + config::FRAGMENT_SIZE <= message.size()) {
						fragement.insert(fragement.end(), pos, pos + config::FRAGMENT_SIZE);
						V8 frame;
						if (pos == message.begin()) {
							message::data_frame data(false, type, fragement);
							frame = data.get_data_frame();
						}
						else if ((pos_tag + config::FRAGMENT_SIZE) >= message.size()) {
							message::data_frame data(true, constants::frame::opcode::continuation, fragement);
							frame = data.get_data_frame();
						}
						else {
							message::data_frame data(false, constants::frame::opcode::continuation, fragement);
							frame = data.get_data_frame();
						}
						if (queue_is_full() == true) {
							data_left.type = type;
							data_left.unit_str.insert(data_left.unit_str.end(), pos, message.end());
							return true;
						}
						if (enqueue(frame, type) == false) {
							return false;
						}
						pos += config::FRAGMENT_SIZE;
						pos_tag += config::FRAGMENT_SIZE;
					}
					else
					{
						int tail = message.size() - pos_tag;
						if (tail < 0) return false;
						fragement.insert(fragement.end(), pos, pos + tail);
						message::data_frame data(true, (opcode_type)0x0, fragement);
						V8 frame = data.get_data_frame();
						if (enqueue(frame, type) == false) {
							return false;
						}
						pos += tail;
						pos_tag += tail;
					}
				}
			}
			else {
				message::data_frame data(true, type, message);
				V8 frame = data.get_data_frame();
				if (enqueue(frame, type) == false) {
					return false;
				}
			}
			return true;
		}

		bool send_queue::input_control_frmae(V8 &message, opcode_type type) {
			message::data_frame data(true, type, message);
			V8 frame = data.get_data_frame();
			if (enqueue(frame, type) == false) {
				return false;
			}
			return true;
		}

		bool send_queue::enqueue(V8 message, opcode_type type) {
			struct queue_unit data;
			data.type = type;
			data.unit_str = message;
			if (type == constants::frame::opcode::ping || type == constants::frame::opcode::pong) {
				queue.head_insert(data);
			}
			else {
				if (queue_is_full() == true) return false;
				queue.push(data);
			}
			return true;
		}

		V8 send_queue::output_message() {
			queue_unit data = dequeue();
			if (data_left_is_empty() == false) {
				input_string(data_left.unit_str, data_left.type);
			}
			return data.unit_str;
		}

		queue_unit send_queue::dequeue() {
			queue_unit data;
			if (queue_is_empty() == false) {
				data = queue.front();
				queue.pop();
			}
			return data;
		}

		int send_queue::get_queue_length() {
			return queue.size();
		}

		bool send_queue::queue_is_full() {
			if (get_queue_length() >= config::MAX_QUEUE_LENGTH) {
				//progressor::error_debug::log("warning: SEND_QUEUE_IS_FULL");
				return true;
			}
			return false;
		}

		bool send_queue::data_left_is_empty() {
			if (data_left.unit_str.empty() == false) {
				return false;
			}
			return true;
		}

		bool send_queue::queue_is_empty() {
			if (get_queue_length() == 0) {
				//progressor::error_debug::log("warning: SEND_QUEUE_IS_NULL");
				return true;
			}
			else {
				return false;
			}
		}

		//---------------------------------recv_queue-----------------------------------
		recv_queue::recv_queue() {
			left_frame.clear();
			queue.clear();
		}

		bool recv_queue::left_frame_is_empty() {
			return left_frame.empty();
		}

		bool recv_queue::input_message(V8 &message) {
			bool decode_tag = true;
			if (left_frame_is_empty() == false) {
				left_frame.insert(left_frame.end(), message.begin(), message.end());
				V8 message_new = left_frame;
				V8::iterator pos = message_new.begin();
				left_frame.clear();
				while (pos != message_new.end())
				{
					decode_tag = decode_frame(message_new, pos);
				}
			}
			else {
				V8::iterator pos = message.begin();
				while (pos != message.end())
				{
					decode_tag = decode_frame(message, pos);
				}
			}
			return decode_tag;
		}

		bool recv_queue::decode_frame(V8 &message, V8::iterator &pos) {
			V8::iterator const pos_store = pos;
			bool fin = fetch_fin(pos);
			int rsv[3];
			for (int i = 0; i < 3; i++) {
				rsv[i] = fetch_rsv(pos, i);
			}
			opcode_type opcode = fetch_opcode(pos);

			pos += 1;
			if (pos == message.end()) {
				left_frame.insert(left_frame.end(), pos_store, message.end());
				return false;
			}
			bool mask = fetch_mask(pos);
			int payload_len = fetch_payload_len(message, pos, pos_store);
			if (payload_len == 0) {
				progressor::error_debug::log("error_encode: ERROR_PAYLOAD_LEN_NUM");
				return false;
			}
			if (mask == true) {
				//ERROR
				for (int i = 0; i < 2; i++) {
					pos++;
					if (pos == message.end()) {

						left_frame.insert(left_frame.end(), pos_store, message.end());
						return false;
					}
				}
			}
			if(pos == message.end()) {
				progressor::error_debug::log("error_decode: ERROR_PAYLOAD_DATA");
				return false;
			}

			V8 payload_data;
			if (handler::helper::is_used_extension() == true) {
				//LOG("don't support extension mode for now");
			}
			else {
				payload_data = fetch_payload_data(message, pos, payload_len, pos_store);
			}
			if ((int)payload_data.size() != payload_len) {
				progressor::error_debug::log("error_decode: ERROR_PAYLOAD_DATA");
				string debug_message = handler::helper::get_frame_message(message, fin, rsv, opcode, mask, payload_len, payload_data);
				progressor::error_debug::log(debug_message);
				return false;
			}
			string debug_message = handler::helper::get_frame_message(message, fin, rsv, opcode, mask, payload_len, payload_data);
			progressor::error_debug::log(debug_message);
			message::data_frame data(fin, rsv, opcode, mask, payload_len, payload_data);
			bool tag = enqueue(data);
			return tag;
		}

		bool recv_queue::fetch_fin(V8::iterator &pos) {
			bool fin = (bool)(*pos >> 7);
			return fin;
		}

		int recv_queue::fetch_rsv(V8::iterator &pos, int i) {
			uint8_t temp = (*pos >> (6 - i)) & 0x01;
			int rsv = temp & 0x01;
			return rsv;
		}

		opcode_type recv_queue::fetch_opcode(V8::iterator &pos) {
			opcode_type opcode = (opcode_type)(*pos & 0x0F);
			return opcode;
		}

		bool recv_queue::fetch_mask(V8::iterator &pos) {
			bool mask = (bool)(*pos >> 7);
			return mask;
		}

		int recv_queue::fetch_payload_len(V8 &message, V8::iterator &pos, V8::iterator const &pos_store) {
			int payload_len = 0;
			int payload_length_tag = (int)(*pos & 0x7F);
			if (payload_length_tag < 126) {
				payload_len = payload_length_tag;
			}
			else if (payload_length_tag == 126) {
				pos += 1;
				if (pos == message.end()) {
					left_frame.insert(left_frame.end(), pos_store, message.end());
				}
				uint16_t len = ((uint16_t)*pos) << 8;
				pos += 1;
				if (pos == message.end()) {
					left_frame.insert(left_frame.end(), pos_store, message.end());
				}
				len = len + (uint16_t)(*pos);
				payload_len = (int)len; //(int)ntohs(len);
			}
			else if (payload_length_tag == 127) {
				pos += 1;
				if (pos == message.end()) {
					left_frame.insert(left_frame.end(), pos_store, message.end());
				}
				uint64_t len = ((uint64_t)*pos) << 56;
				for (int i = 1; i < 8; i++) {
					pos++;
					if (pos == message.end()) {

						left_frame.insert(left_frame.end(), pos_store, message.end());
					}
					len = len + ((uint64_t)*pos) << (56 - i * 8);
				}
				payload_len = (int)len;//(int)ntohl((uint64_t)len);
			}
			return payload_len;
		}

		uint8_t recv_queue::fetch_masking_key(V8::iterator &pos) {
			pos += 1;
			uint8_t masking_key = *pos;
			return masking_key;
		}

		V8 recv_queue::fetch_payload_data(V8 &message, V8::iterator &pos, int payload_len, V8::iterator const &pos_store) {
			pos += 1;
			V8 data;
			if (payload_len > 0) {
				int byte_num = payload_len;
				for (int i = 0; i < byte_num; i++) {
					if (pos == message.end()) {
						left_frame.insert(left_frame.end(), pos_store, message.end());
						break;
					}
					data.push_back(*pos);
					pos++;
				}
			}
			else {
				//ERROR(ERROR_PAYLOAD_LEN_NUM);
			}
			return data;
		}

		bool recv_queue::enqueue(message::data_frame data) {
			if (data.get_opcode() == constants::frame::opcode::pong || data.get_opcode() == constants::frame::opcode::ping || data.get_opcode() == constants::frame::opcode::close) {
				queue.head_insert(data);
			}
			else {
				queue.push(data);
			}
			return true;
		}

		queue_unit recv_queue::output_message() {
			struct queue_unit message;
			message::data_frame data = dequeue();
			message.unit_str = data.get_payload_data();
			message.type = data.get_opcode();
			if (data.get_fin() == false) {
				message::data_frame data_next = get_front();
				while ((queue_is_empty() == false) && (data_next.get_opcode() == constants::frame::opcode::continuation)) {
					message::data_frame data_ = dequeue();
					message.unit_str.insert(message.unit_str.end(), data_.get_payload_data().begin(), data_.get_payload_data().end());
					if (queue_is_empty() == false) {
						data_next = get_front();
					}
				}
			}
			return message;
		}

		message::data_frame recv_queue::dequeue() {
			//need judge queue is or not empty? but data_frame has not default constructor function
			message::data_frame data = queue.front();
			queue.pop();
			return data;
		}

		message::data_frame recv_queue::get_front() {
			message::data_frame data = queue.front();
			return data;
		}

		int recv_queue::get_queue_length() {
			return queue.size();
		}

		bool recv_queue::queue_is_empty() {
			if (get_queue_length() == 0) {
				//progressor::error_debug::log("warning: RECV_QUEUE_IS_NULL");
				return true;
			}
			else {
				return false;
			}
		}
	}
}
