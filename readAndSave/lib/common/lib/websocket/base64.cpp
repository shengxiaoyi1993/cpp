#include "base64.h"
namespace websocket{
	namespace handler {
		namespace base64 {
			std::string base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

			std::string transform_encode(uint8_t a, uint8_t b, uint8_t c) {
				uint64_t sum;
				uint8_t encode[4];
				std::string code = "";
				uint64_t a_ = ((uint64_t)a) << 16;
				uint64_t b_ = ((uint64_t)b) << 8;
				uint64_t c_ = ((uint64_t)c);
				sum = a_ + b_ + c_;
				for (int i = 0; i < 4; i++) {
					encode[i] = (uint8_t)((sum >> (18 - i * 6)) & 0x3F);
					code = code + base64[(int)encode[i]];
				}
				return code;
			}

			std::string transform_encode(uint8_t a, uint8_t b) {
				uint64_t sum;
				uint8_t encode[4];
				std::string code = "";
				uint64_t a_ = ((uint64_t)a) << 16;
				uint64_t b_ = ((uint64_t)b) << 8;
				sum = a_ + b_;
				for (int i = 0; i < 3; i++) {
					encode[i] = (uint8_t)((sum >> (18 - i * 6)) & 0x3F);
					code = code + base64[(int)encode[i]];
				}
				code = code + "=";
				return code;
			}

			std::string transform_encode(uint8_t a) {
				uint64_t sum;
				uint8_t encode[4];
				std::string code = "";
				uint64_t a_ = ((uint64_t)a) << 16;
				sum = a_;
				for (int i = 0; i < 2; i++) {
					encode[i] = (uint8_t)((sum >> (18 - i * 6)) & 0x3F);
					code = code + base64[(int)encode[i]];
				}
				code = code + "==";
				return code;
			}

			std::string  base64_encode(std::string str) {
				std::string encode_str = "";
				for (int i = 0; i < str.size(); i = i + 3) {
					if ((i + 1) < str.size() && (i + 2) < str.size()) {
						std::string temp = transform_encode(str[i], str[i + 1], str[i + 2]);
						encode_str += temp;
					}
					else if ((i + 1) >= str.size()) {
						std::string temp = transform_encode(str[i]);
						encode_str += temp;
					}
					else if ((i + 2) >= str.size()) {
						std::string temp = transform_encode(str[i], str[i + 1]);
						encode_str += temp;
					}
				}
				return encode_str;
			}

			std::string  base64_encode(std::vector<uint8_t> str) {
				std::string encode_str = "";
				for (int i = 0; i < str.size(); i = i + 3) {
					if ((i + 1) < str.size() && (i + 2) < str.size()) {
						std::string temp = transform_encode(str[i], str[i + 1], str[i + 2]);
						encode_str += temp;
					}
					else if ((i + 1) >= str.size()) {
						std::string temp = transform_encode(str[i]);
						encode_str += temp;
					}
					else if ((i + 2) >= str.size()) {
						std::string temp = transform_encode(str[i], str[i + 1]);
						encode_str += temp;
					}
				}
				return encode_str;
			}

			std::string transform_decode(char a, char b, char c, char d) {
				uint64_t sum;
				std::string decode_str = "";
				char decode[3];
				if (c == '=') {
					uint64_t a_ = ((uint64_t)base64.find(a)) << 18;
					uint64_t b_ = ((uint64_t)base64.find(b)) << 12;
					sum = a_ + b_;
					decode_str += (char)(sum >> 16);
				}
				else if (d == '=') {
					uint64_t a_ = ((uint64_t)base64.find(a)) << 18;
					uint64_t b_ = ((uint64_t)base64.find(b)) << 12;
					uint64_t c_ = ((uint64_t)base64.find(c)) << 6;
					sum = a_ + b_ + c_;
					decode[0] = (char)(sum >> 16);
					decode[1] = (char)((sum >> 8) & 0xFF);
					decode_str = decode_str + decode[0] + decode[1];
				}
				else {
					uint64_t a_ = ((uint64_t)base64.find(a)) << 18;
					uint64_t b_ = ((uint64_t)base64.find(b)) << 12;
					uint64_t c_ = ((uint64_t)base64.find(c)) << 6;
					uint64_t d_ = ((uint64_t)base64.find(d));
					sum = a_ + b_ + c_ + d_;
					decode[0] = (uint8_t)((sum >> 16) & 0xFF);
					decode[1] = (uint8_t)((sum >> 8) & 0xFF);
					decode[2] = (uint8_t)(sum & 0xFF);
					decode_str = decode_str + decode[0] + decode[1] + decode[2];
				}
				return decode_str;
			}

			std::string base64_decode(std::string str) {
				std::string decode_str = "";
				for (int i = 0; i < str.size(); i = i + 4) {
					std::string temp = transform_decode(str[i], str[i + 1], str[i + 2], str[i + 3]);
					decode_str += temp;
				}
				return decode_str;
			}
		}
	}
}
