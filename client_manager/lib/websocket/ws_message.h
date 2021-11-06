#ifndef _WEBSOCKET_MESSAGE_H_
#define _WEBSOCKET_MESSAGE_H_
#include "constants.h"
#include <vector>
#include <stdint.h>
namespace websocket {
	namespace message {
		typedef std::string string;
		typedef uint8_t opcode_type;
		typedef std::vector<uint8_t> V8;
		struct data_delivery {
			enum status {head = 0, middle = 1, tail = 3, single = 4};
			enum status data_status;
			opcode_type data_type;
			V8 data;
		};

		class data_frame {
		private:
			bool fin;
			int rsv[3];
			opcode_type opcode;
			bool mask;
			int payload_len;
			uint8_t masking_key[4];
			V8 payload_data;
		public:
			data_frame() {

			};
			data_frame(bool ws_fin, opcode_type ws_opcode, V8 ws_data);
			data_frame(bool ws_fin, int ws_rsv[3], opcode_type ws_opcode,V8 ws_data);
			data_frame(bool ws_fin, int ws_rsv[3], opcode_type ws_opcode, bool ws_mask, int ws_payload_len, V8 ws_payload_data);
			V8 get_data_frame();
			bool get_fin();
			int* get_rsv();
			opcode_type get_opcode();
			bool get_mask();
			int get_payload_len();
			uint8_t *get_masking_key();
			V8 get_payload_data();
		private:
			bool check_data_frame();
		};



		class request {
		private:
			string header;
			string host;
			string upgrade;
			string connection;
			string sec_websocket_key;
			string origin;
			string sec_websocket_protocol;
			string sec_websocket_extensions;
			string sec_websocket_version;
		public:
			request(string &path, string &host);
			request(string &path, string &host, string &port);
			int set_origin(string &origin_str);
			int set_sec_websocket_protocol(string &procotol_str);
			int set_sec_websocket_extensions(string &extensions_str);
			string get_sec_websocket_key();
			string get_sec_websocket_protocol();
			string get_sec_websocket_extensions();
			string progress_request();
		};

		class response {
		private:
			string header;
			string upgrade;
			string connection;
			string sec_websocket_accept;
			string sec_websocket_protocol;
			string sec_websocket_extensions;
			bool check_accept(string &key);
			bool check_protocol();
			bool check_extensions();
		public:
			response(string &response_str);
			bool responce_check(string &key);
			string get_sec_websocket_protocol();
			string get_sec_websocket_extensions();
		};

	}
}
#endif
