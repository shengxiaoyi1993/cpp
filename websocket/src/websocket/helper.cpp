#include <stdlib.h>
#include <time.h>
#include <algorithm>
#ifdef _WIN32
#include <WS2tcpip.h>
typedef long long ssize_t;
#else
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <string.h>
#endif
#include "config.h"
#include "helper.h"
#include "error_debug.h"
//#include <iostream>

namespace websocket {
	typedef std::string string;
	namespace handler {
		namespace helper {
			//return a unit8_t random value
			uint8_t randomFunc()
			{
				uint8_t value;
				srand((unsigned)time(NULL));
				value = rand() % 256;
				return value;
			}

			std::vector<uint8_t> string_transform_uint8_t(string message) {
				std::vector<uint8_t> message_new;
				for (int i = 0; i < (int)message.size(); i++) {
					message_new.push_back((uint8_t)message[i]);
				}
				return message_new;
			}

			string uint8_t_transform_string(std::vector<uint8_t> message) {
				string message_new = "";
				for (int i = 0; i < (int)message.size(); i++) {
					message_new += ((char)message[i]);
				}
				return message_new;
			}

			bool is_used_sub_protocol() {
				return config::SUB_PROTOCOL;
			}

			bool is_used_extension() {
				return config::EXTENSION;
			}

			bool read_response(int fd, char *vptr) {
				ssize_t nread;
				char *target = "\r\n\r\n";
				char *ptr;
				ptr = vptr;
				do {
					if ((nread = recv(fd, ptr, 1, 0)) < 0) {
						if (errno == EINTR) {
							nread = 0;
							continue;
						}
						else {
							//progressor::error_debug::log("RECV_FUNC_FAIL");
							return -1;
						}
					}
					else if (nread == 0) {
						//progressor::error_debug::log("NO_DATA_TO_READ");
						break;
					}
					ptr += nread;
					if (strstr(vptr, target) != NULL) {
						break;
					}
				} while (true);
				return true;
			}

			int readn(int fd, void *vptr, size_t n) {
				size_t nleft;
				ssize_t nread;
				char *ptr;
				ptr = (char *)vptr;
				nleft = n;
				while (nleft > 0) {
					if ((nread = recv(fd, ptr, nleft, 0)) < 0) {
						if (errno == EINTR) {
							nread = 0;
						}
						else {
							//progressor::error_debug::log("read error:RECV_FUNC_FAIL");
							nread = 0;
							while(*ptr != 0) {
								ptr++;
								nread++;
							}
							nleft -= nread;
							return (n - nleft);
						}
					}
					else if (nread == 0) {
						//progressor::error_debug::log("NO_DATA_TO_READ");
						break;
					}
					if (nread != -1) {
						nleft -= nread;
						ptr += nread;
					}

				}
				return (n - nleft);
			}

			int writen(int fd, const void *vptr, size_t n) {
				size_t nleft;
				ssize_t nwritten;
				const char *ptr;

				ptr = (char *)vptr;
				nleft = n;
				while (nleft > 0) {
					if ((nwritten = send(fd, ptr, nleft, 0)) <= 0) {
						if (nwritten < 0 && errno == EINTR) {
							nwritten = 0;
						}
						else {
							//progressor::error_debug::log("write error:SEND_FUNC_FAIL");
							return (-1);
						}
					}
					nleft -= nwritten;
					ptr += nwritten;
				}
				return (n - nleft);
			}

			int  mask_data(std::vector<uint8_t> &data, uint8_t *masking_key) {
				for (int i = 0; i < data.size(); i++) {
					int j = i % 4;
					data.at(i) = data.at(i) ^ masking_key[j];
				}
				return true;
			}

			void delete_all_mark(string &s, const string &mark)
			{
				unsigned int nSize = mark.size();
				while (1)
				{
					std::size_t pos = s.find(mark);
					if (pos == string::npos)
					{
						break;
					}

					s.erase(pos, nSize);
				}
			}

			// string
			string str_to_lower(const string &str)
			{
				string strTmp = str;
				transform(strTmp.begin(), strTmp.end(), strTmp.begin(), tolower);
				return strTmp;
			}

			// string.compareNoCase
			bool compare_no_case(const string &strA, const string &strB)
			{
				string str1 = str_to_lower(strA);
				string str2 = str_to_lower(strB);
				return (str1 == str2);
			}

			string get_field_value(const std::vector<string> &info, string field) {
				string field_value = "";
				for (int i = 0; i < info.size(); i++) {
					string str = info.at(i);
					std::size_t key_pos = str.find(":");
					if (key_pos == string::npos) continue;
					string key = str.substr(0, key_pos);
					string value = str.substr(key_pos + strlen(":"));
					if (handler::helper::compare_no_case(key, field) == true) {
						string space = " ";
						delete_all_mark(value, space);
						field_value += value;
						break;
					}
				}
				return field_value;
			}

			string get_time() {
				string time_str = "";
				char time_char[100];
				time_t tt; 
				time( &tt ); 
				tt = tt + 8*3600; // transform the time zone 
				tm* t= gmtime( &tt ); 
				sprintf(time_char, "%d-%02d-%02d %02d:%02d:%02d\n", 
					t->tm_year + 1900, 
					t->tm_mon + 1, 
					t->tm_mday, 
					t->tm_hour, 
					t->tm_min, 
					t->tm_sec);
				time_str += time_char;
				return time_str; 
			}


			string tra_int_to_string(int num) {
				char num_char[11] = "0123456789";
				string str_num = "";
				char pos;
				while(num/10 != 0) {
					pos = num_char[num % 10];
					str_num = pos + str_num;
					num = num/10;
				}
				pos = num_char[num % 10];
				str_num = pos + str_num;
				return str_num;
			}

			string get_frame_message(V8 frame, bool fin, int rsv[], int opcode, bool mask, int payload_len, V8 payload_data) {
				string message = "";
				message = message + "fin:" + tra_int_to_string(fin) + "\n";
				message = message + "rsv:" + tra_int_to_string(rsv[0]) + tra_int_to_string(rsv[1]) + tra_int_to_string(rsv[2]) + "\n";
				message = message + "opcode:" + tra_int_to_string(opcode) + "\n";
				message = message + "mask:" + tra_int_to_string(mask) + "\n";
				message = message + "payload_len:" + tra_int_to_string(payload_len) + "\n";
				message = message + "payload_data:" + "\n";
				for(int i = 0; i < payload_data.size(); i++) {
					message = message + (char)payload_data.at(i);
				}
				message = message + "\n";
				message = message + "Original frame:" + "\n";
				for(int i = 0; i < frame.size(); i++) {
					message = message + tra_int_to_string(frame.at(i)) + "/";
				}
				message = message + "\n";
				return message;
			}

		}
	}
}