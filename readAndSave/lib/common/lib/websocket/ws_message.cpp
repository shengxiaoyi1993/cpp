#include "ws_message.h"
#ifdef _WIN32
#include <WinSock2.h>
#else
#include <netinet/in.h>
#endif // _WIN32
#include "helper.h"
#include "config.h"
#include "base64.h"
#include "sha1.h"
#include <vector>
#include <string.h>
#include "error_debug.h"
//#include <iostream>
//masking_key[i] = handler::helper::randomFunc();
namespace websocket {
	namespace message {
		//------------------------------data_frame-------------------------------
		using namespace constants::frame::opcode;
		data_frame::data_frame(bool ws_fin, opcode_type ws_opcode, V8 ws_data) :fin(ws_fin), opcode(ws_opcode), mask(true) {
			for (int i = 0; i < 3; i++) {
				rsv[i] = 0;
			}
			if (mask == true) {
				for (int i = 0; i < 4; i++)
				{
					masking_key[i] = handler::helper::randomFunc();
				}
				handler::helper::mask_data(ws_data, masking_key);
			}
			payload_data = ws_data;
			payload_len = payload_data.size();
			check_data_frame();
		}

		data_frame::data_frame(bool ws_fin, int ws_rsv[3], opcode_type ws_opcode, V8 ws_data) :fin(ws_fin), opcode(ws_opcode), mask(1) {
			for (int i = 0; i < 3; i++) {
				rsv[i] = ws_rsv[i];
			}
			for (int i = 0; i < 4; i++)
			{
				masking_key[i] = handler::helper::randomFunc();
			}
			if (mask == 1) {
				handler::helper::mask_data(ws_data, masking_key);
				payload_data = ws_data;
			}
			payload_len = payload_data.size();
			check_data_frame();
		}

		data_frame::data_frame(bool ws_fin, int ws_rsv[3], opcode_type ws_opcode, bool ws_mask, int ws_payload_len, V8 ws_payload_data)
			:fin(ws_fin), opcode(ws_opcode), mask(ws_mask), payload_len(ws_payload_len), payload_data(ws_payload_data) {
			for (int i = 0; i < 3; i++) {
				rsv[i] = ws_rsv[i];
			}
			check_data_frame();
		}

		V8 data_frame::get_payload_data() {
			return payload_data;
		}

		V8 data_frame::get_data_frame() {
			int pos = 7;
			uint8_t fin_ = (uint8_t)fin;
			uint8_t rsv_[3];
			uint8_t mask_ = (uint8_t)mask;
			uint8_t opcode_ = (uint8_t)opcode;
			uint8_t payload_len_;
			uint8_t payload_len_array[8];
			uint8_t masking_key_[4];
			V8 header;
			V8 data_frame_;

			fin_ = fin_ << pos;

			for (int i = 0; i < 3; i++) {
				pos -= 1;
				rsv_[i] = ((uint8_t)rsv[i]) << pos;
			}
			header.push_back(fin_ + rsv[0] + rsv[1] + rsv[2] + opcode_);
			pos = 7;
			mask_ = mask_ << pos;
			if (payload_len < 126) {
				payload_len_ = (uint8_t)payload_len;

				header.push_back(mask_ + payload_len_);
			}
			else if (payload_len >= 126 && payload_len <= 64335) {
				payload_len_ = (uint8_t)0x7E;
				uint16_t payload_len_net = (uint16_t)payload_len;//htons((uint16_t)payload_len);
				payload_len_array[0] = (uint8_t)(payload_len_net >> 8);
				payload_len_array[1] = (uint8_t)(payload_len_net & 0xFF);
				header.push_back(mask_ + payload_len_);
				header.push_back(payload_len_array[0]);
				header.push_back(payload_len_array[1]);
			}
			else {
				payload_len_ = (uint8_t)0x7F;
				header.push_back(mask_ + payload_len_);
				uint16_t payload_len_net = (uint64_t)payload_len;//htons((uint64_t)payload_len);
				for (int i = 0; i < 8; i++)
				{
					payload_len_array[i] = uint8_t(payload_len_net >> (56 - 8 * i) & 0xFF);
					header.push_back(payload_len_array[i]);
				}
			}

			if (mask == 1) {
				for (int i = 0; i < 4; i++)
				{
					masking_key_[i] = (uint8_t)handler::helper::randomFunc();
					header.push_back(masking_key_[i]);
				}
			}
			data_frame_.insert(data_frame_.end(), header.begin(), header.end());
			data_frame_.insert(data_frame_.end(), payload_data.begin(), payload_data.end());
			//std::cout << "fin: " << fin << std::endl;
			//std::cout << "rsv: " << rsv[0] << rsv[1] << rsv[2] << std::endl;
			//std::cout << "opcode: " << (int)opcode << std::endl;
			//std::cout << "mask: " << mask << std::endl;
			//std::cout << "payload_len: " << payload_len << std::endl;
			return data_frame_;
		}

		bool data_frame::check_data_frame() {
			for (int i = 0; i < 3; i++) {
				if (rsv[i] != 0 && rsv[i] != 1) {
					//ERROR(ERROR_RSV_VALUE);
					progressor::error_debug::log("error_frame:ERROR_RSV_VALUE");
					return false;
				}
				if (rsv[i] == 1 && (handler::helper::is_used_extension() == false)) {
					//ERROR(ERROR_EXTENSION_NOT_EXIST);
					progressor::error_debug::log("error_frame:ERROR_EXTENSION_NOT_EXIST");
					return false;
				}
			}
			if (opcode != continuation && opcode != text && opcode != binary && opcode != close && opcode != ping && opcode != pong && (handler::helper::is_used_extension() == false)) {
				//ERROR(ERROR_EXTENSION_NOT_EXIST);
				progressor::error_debug::log("error_frame:ERROR_EXTENSION_NOT_EXIST");
				return false;
			}
			if (payload_len < 0) {
				//ERROR_PAYLOAD_LEN_ERROR;
				progressor::error_debug::log("error_frame:ERROR_PAYLOAD_LEN_ERROR");
				return false;
			}

			return true;
		}

		bool data_frame::get_fin() {
			return fin;
		}

		int *data_frame::get_rsv() {
			return rsv;
		}

		opcode_type data_frame::get_opcode() {
			return opcode;
		}

		bool data_frame::get_mask() {
			return mask;
		}

		int data_frame::get_payload_len() {
			return payload_len;
		}
		uint8_t *data_frame::get_masking_key() {
			return masking_key;
		}

		/*V8 data_frame::get_payload_data() {
		return payload_data;
		}*/
		//------------------------------request-------------------------------

		request::request(string &path, string &ws_host) :header("GET " + path + " HTTP/1.1"), upgrade("websocket"), connection("Upgrade"), sec_websocket_version("13") {
			if (config::TSL == true) {
				host = ws_host + ":" + config::wss_port;
			}
			else {
				host = ws_host + ":" + config::port;
			}

			string key = "";
			for (int i = 0; i < 16; i++) {
				key += (char)handler::helper::randomFunc();
			}
			sec_websocket_key = handler::base64::base64_encode(key);
			sec_websocket_protocol = "";
			sec_websocket_extensions = "";
			origin = "";
		}

		request::request(string &path, string &ws_host, string &port) : header("GET " + path + " HTTP/1.1"), upgrade("websocket"), connection("Upgrade"), sec_websocket_version("13") {
			host = ws_host + ":" + port;
			string key = "";
			for (int i = 0; i < 16; i++) {
				key += (char)handler::helper::randomFunc();
			}
			sec_websocket_key = handler::base64::base64_encode(key);
			sec_websocket_protocol = "";
			sec_websocket_extensions = "";
			origin = "";
		}

		int request::set_origin(string &origin_str) {
			origin = origin_str;
			return 1;
		}

		int request::set_sec_websocket_protocol(string &protocol_str) {
			sec_websocket_protocol = protocol_str;
			return 1;
		}

		int request::set_sec_websocket_extensions(string &extensions_str) {
			sec_websocket_extensions = extensions_str;
			return 1;
		}

		string request::get_sec_websocket_key() {
			return sec_websocket_key;
		}

		string request::progress_request() {
			string handshake_request = "";
			handshake_request = handshake_request + header + "\r\n";
			handshake_request = handshake_request + "Host: " + host + "\r\n";
			handshake_request = handshake_request + "Upgrade: " + upgrade + "\r\n";
			handshake_request = handshake_request + "Connection: " + connection + "\r\n";
			handshake_request = handshake_request + "Sec-WebSocket-Key: " + sec_websocket_key + "\r\n";
			handshake_request = handshake_request + "Sec-WebSocket-Version: " + sec_websocket_version + "\r\n";
			if (origin != "") {
				handshake_request = handshake_request + "Origin: " + origin + "\r\n";
			}
			if (sec_websocket_extensions != "") {
				handshake_request = handshake_request + "Sec-WebSocket-Extensions: " + sec_websocket_extensions + "\r\n";
			}
			if (sec_websocket_protocol != "") {
				handshake_request = handshake_request + "Sec-Websocket-Protocol: " + sec_websocket_protocol + "\r\n";
			}
			handshake_request += "\r\n";
			return handshake_request;
		}

		string request::get_sec_websocket_protocol() {
			return sec_websocket_protocol;
		}

		string request::get_sec_websocket_extensions() {
			return sec_websocket_extensions;
		}

		//------------------------------responce-------------------------------

		response::response(string &response_str) {
			std::vector<string> response_field;
			std::size_t head = response_str.find("HTTP/1.1 ") + strlen("HTTP/1.1 ");
			std::size_t tail = response_str.find(" Switching Protocols") - strlen("HTTP/1.1 ");
			string status = response_str.substr(head, 3);
			header = status;
			std::size_t pos = 0;
			while (true) {
				std::size_t per_pos = pos;
				pos = response_str.find("\r\n", pos);
				if (pos == string::npos) break;
				if (pos != per_pos)
					response_field.push_back(response_str.substr(per_pos, pos - per_pos));
				pos = pos + strlen("\r\n");
			}
			upgrade = handler::helper::get_field_value(response_field, "Upgrade");
			connection = handler::helper::get_field_value(response_field, "Connection");
			sec_websocket_accept = handler::helper::get_field_value(response_field, "Sec-WebSocket-Accept");
			sec_websocket_protocol = handler::helper::get_field_value(response_field, "Sec-WebSocket-Protocol");
			sec_websocket_extensions = handler::helper::get_field_value(response_field, "Sec-WebSocket-Extensions");
		}

		bool response::check_accept(string &key) {
			key += "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
			std::vector<uint8_t> sha1_abstract = handler::sha1::sha1_encode(key);
			string client_accept = handler::base64::base64_encode(sha1_abstract);
			if (client_accept == sec_websocket_accept) {
				return true;
			}
			else {
				return false;
			}
		}

		bool response::check_protocol() {
			if (sec_websocket_protocol == "") {
				return true;
			}
			else {
				//todo:check;
				return true;
			}
		}

		bool response::check_extensions() {
			if (sec_websocket_extensions == "") {
				return true;
			}
			else {
				//todo:check;
				return true;
			}
		}

		bool response::responce_check(string &key) {
			if (header != "101") {
				progressor::error_debug::log("ERROR_RESPONSE_STATUS");
				return false;
			}
			if (upgrade != "websocket") {
				//ERROR_UPGRADE;
				progressor::error_debug::log("ERROR_UPGRADE");
				return false;
			}
			if (connection != "Upgrade") {
				//ERROR_CONNECTION_FIELD;
				progressor::error_debug::log("ERROR_CONNECTION_FIELD");
				return false;
			}
			if (check_accept(key) == false) {
				//ERROR_ACCEPT;
				progressor::error_debug::log("ERROR_ACCEPT");
				return false;
			}
			if (check_protocol() == false) {
				//ERROR_ACCEPT;
				progressor::error_debug::log("ERROR_ACCEPT");
				return false;
			}
			if (check_extensions() == false) {
				//ERROR_ACCEPT;
				progressor::error_debug::log("ERROR_ACCEPT");
				return false;
			}
			return true;
		}

		string response::get_sec_websocket_protocol() {
			return  sec_websocket_protocol;
		}

		string response::get_sec_websocket_extensions() {
			return sec_websocket_extensions;
		}
	}
}
