#include "sha1.h"
#include <string>
#include <vector>
#include <cmath>
namespace websocket {
	namespace handler {
		namespace sha1 {
			typedef std::string string;
			unsigned sha1_circular_shift(int bits, unsigned word)
			{
				return ((word << bits) & 0xFFFFFFFF) | ((word & 0xFFFFFFFF) >> (32 - bits));
			}

			std::vector<uint8_t> supply_bits(std::vector<uint8_t> origin_msg) {
				std::vector<uint8_t> supply_msg = origin_msg;
				uint8_t first_8_bits = 0x80;
				uint8_t other_8_bits = 0x00;
				int n = floor((origin_msg.size() * 8 + 64) / 512);
				int supply_8_bits_num = 56 - (origin_msg.size() - 64 * n);
				if (supply_8_bits_num > 0) {
					supply_msg.push_back(first_8_bits);
					if (supply_8_bits_num > 1) {
						for (int i = 0; i < supply_8_bits_num - 1; i++) {
							supply_msg.push_back(other_8_bits);
						}
					}
				}
				uint64_t msg_size = (uint64_t)(origin_msg.size() * 8);
				for (int i = 0; i < 8; i++) {
					uint8_t tail = (uint8_t)((msg_size >> 8 * (7 - i)) & 0xFF);
					supply_msg.push_back(tail);
				}
				return supply_msg;
			}

			void supply_groups(std::vector<uint32_t> &sub_groups) {
				for (int i = 16; i < 80; i++) {
					uint32_t wt = sha1_circular_shift(1, (sub_groups[i - 3] ^ sub_groups[i - 8] ^ sub_groups[i - 14] ^ sub_groups[i - 16]));
					sub_groups[i] = wt;
				}
			}

			std::vector<uint32_t> progress_groups(std::vector<uint32_t> const &sub_groups, std::vector<uint32_t> &abstract) {
				const unsigned K[] = {               // Constants defined for SHA-1
					0x5A827999,
					0x6ED9EBA1,
					0x8F1BBCDC,
					0xCA62C1D6
				};
				uint32_t A = abstract[0];
				uint32_t B = abstract[1];
				uint32_t C = abstract[2];
				uint32_t D = abstract[3];
				uint32_t E = abstract[4];
				std::vector<uint32_t> abstract_new(5);
				for (int i = 0; i < 80; i++) {
					uint32_t ft_value;
					uint32_t kt;
					if (i >= 0 && i <= 19) {
						ft_value = (B&C) | (~B&D);
						kt = K[0];
					}
					else if (i >= 20 && i <= 39) {
						ft_value = (B^C^D);
						kt = K[1];
					}
					else if (i >= 40 && i <= 59) {
						ft_value = (B&C) | (B&D) | (C&D);
						kt = K[2];
					}
					else if (i >= 60 && i <= 79) {
						ft_value = (B^C^D);
						kt = K[3];
					}
					uint32_t temp = sha1_circular_shift(5, A) + ft_value + E + sub_groups[i] + kt;
					E = D;
					D = C;
					C = sha1_circular_shift(30, B);
					B = A;
					A = temp;
				}
				abstract_new[0] = (A + abstract[0]) & 0xFFFFFFFF;
				abstract_new[1] = (B + abstract[1]) & 0xFFFFFFFF;
				abstract_new[2] = (C + abstract[2]) & 0xFFFFFFFF;
				abstract_new[3] = (D + abstract[3]) & 0xFFFFFFFF;
				abstract_new[4] = (E + abstract[4]) & 0xFFFFFFFF;
				return abstract_new;
			}

			std::vector<uint32_t> grouping_procressing(std::vector<uint8_t> supply_str) {
				string abstract_str = "";
				std::vector<uint32_t> abstract(5);
				abstract[0] = 0x67452301;
				abstract[1] = 0xEFCDAB89;
				abstract[2] = 0x98BADCFE;
				abstract[3] = 0x10325476;
				abstract[4] = 0xC3D2E1F0;
				int group_num = supply_str.size() * 8 / 512;
				for (int i = 0; i < group_num; i++) {
					std::vector<uint32_t> sub_groups(80);
					for (int j = 0; j < 16; j++) {
						sub_groups[j] = (uint32_t)(supply_str[i * 64 + 4 * j] << 24) + (uint32_t)(supply_str[i * 64 + 4 * j + 1] << 16) + (uint32_t)(supply_str[i * 64 + 4 * j + 2] << 8) + (uint32_t)(supply_str[i * 64 + 4 * j + 3]);
					}
					supply_groups(sub_groups);
					abstract = progress_groups(sub_groups, abstract);
				}
				return abstract;
			}

			std::vector<uint8_t> sha1_encode(std::string str) {
				if (str.length() >(pow(2, 64) / 8)) {
					//ERROR_SHA1_LENGTH;
				}
				std::vector<uint8_t> origin_msg;
				for (int i = 0; i < str.size(); i++) {
					origin_msg.push_back((uint8_t)str[i]);
				}
				std::vector<uint32_t> abstract_new;
				std::vector<uint8_t> supply_str = supply_bits(origin_msg);
				abstract_new = grouping_procressing(supply_str);

				std::vector<uint8_t> abstract(20);
				for (int i = 0; i < 5; i++) {
					abstract[4 * i] = (uint8_t)((abstract_new[i] >> 24) & 0xFF);
					abstract[4 * i + 1] = (uint8_t)((abstract_new[i] >> 16) & 0xFF);
					abstract[4 * i + 2] = (uint8_t)((abstract_new[i] >> 8) & 0xFF);
					abstract[4 * i + 3] = (uint8_t)(abstract_new[i] & 0xFF);
				}

				return abstract;
			}
		}
	}
}