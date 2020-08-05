#ifndef _WEBSOCKET_HANDLER_HELPER_H_
#define _WEBSOCKET_HANDLER_HELPER_H_
#include <stdlib.h>
#include <vector>
#include <stdint.h>
namespace websocket {
	typedef std::string string;
	namespace handler {
		namespace helper {
			//return a unit8_t random value
			typedef std::vector<uint8_t> V8;

			uint8_t randomFunc();

			std::vector<uint8_t> string_transform_uint8_t(string message);
			string uint8_t_transform_string(std::vector<uint8_t> message);

			template<class T>
			class queue {
			private:
				std::vector<T> queue_simulation;
			public:
				queue() {
					if (!queue_simulation.empty()) {
						queue_simulation.clear();
					}
				}

				bool empty() {
					return queue_simulation.empty();
				}

				void push(T unit) {
					queue_simulation.push_back(unit);
				}

				void pop() {
					if (!empty()) {
						queue_simulation.erase(queue_simulation.begin());
					}
				}

				T front() {
					T temp;
					if (!empty()) {
						temp = *queue_simulation.begin();
					}
					return temp;
				}

				T back() {
					T temp;
					if (!empty()) {
						temp = *queue_simulation.end();
					}
					return temp;
				}

				int size() {
					return (int)queue_simulation.size();
				}

				void head_insert(T unit) {
					queue_simulation.insert(queue_simulation.begin(), unit);
				}

				void clear() {
					while (!empty())
					{
						pop();
					}
				}
			};

			bool is_used_sub_protocol();

			bool is_used_extension();

			bool read_response(int n, char *ptr);

			int readn(int fd, void *vptr, size_t n);

			int writen(int fd, const void *vptr, size_t n);

			int  mask_data(std::vector<uint8_t> &data, uint8_t *masking_key);

			void delete_all_mark(string &s, const string &mark);

			// string
			string str_to_lower(const string &str);

			// string.compareNoCase
			bool compare_no_case(const string &strA, const string &strB);

			string get_field_value(const std::vector<string> &info, string field);

			string get_time();

			string tra_int_to_string(int num);

			string get_frame_message(V8 frame, bool fin, int rsv[], int opcode, bool mask, int payload_len, V8 payload_data);		
		}
	}
}
#endif
