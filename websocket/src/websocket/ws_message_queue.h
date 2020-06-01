#ifndef _WEBSOCKET_MESSAGE_QUEUE_H_
#define _WEBSOCKET_MESSAGE_QUEUE_H_
#include <string>
#include "ws_message.h"
#include "helper.h"
#include <stdint.h>
namespace websocket {
	namespace message_queue {
		typedef std::string string;
		typedef uint8_t opcode_type;
		typedef std::vector<uint8_t> V8;

		struct queue_unit {
			opcode_type type;
			V8 unit_str;
		};

		class send_queue {
		private:
			queue_unit data_left;
			handler::helper::queue<queue_unit> queue;
		public:
			send_queue();
			bool input_message(string &message);
			bool input_message(V8 &message);
			bool input_ping(string &message);
			bool input_ping(V8 &message);
			bool input_pong(V8 &message);
			bool input_close(string &message);
			bool input_close(V8 &message);
			bool queue_is_full();
			bool queue_is_empty();
			bool data_left_is_empty();
			V8 output_message();
		private:
			int get_queue_length();
			bool input_string(V8 &message, opcode_type type);
			bool input_control_frmae(V8 &message, opcode_type type);
			bool enqueue(V8 message, opcode_type type);
			queue_unit dequeue();
		};

		class recv_queue {
		private:
			V8 left_frame;
			handler::helper::queue<message::data_frame> queue;
		public:
			recv_queue();
			bool input_message(V8 &message);
			queue_unit output_message();
			bool queue_is_empty();
			int get_queue_length();
			bool left_frame_is_empty();
		private:
			bool decode_frame(V8 &message, V8::iterator &pos);
			bool fetch_fin(V8::iterator &pos);
			int fetch_rsv(V8::iterator &pos, int i);
			opcode_type fetch_opcode(V8::iterator &pos);
			bool fetch_mask(V8::iterator &pos);
			int fetch_payload_len(V8 &message, V8::iterator &pos, V8::iterator const &pos_store);
			uint8_t fetch_masking_key(V8::iterator &pos);
			V8 fetch_payload_data(V8 &message, V8::iterator &pos, int paload_len, V8::iterator const &pos_store);
			bool enqueue(message::data_frame data);
			message::data_frame dequeue();
			message::data_frame get_front();
		};
	}
}
#endif
