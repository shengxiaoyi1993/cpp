#include <string>
#include <iostream>
#include <fstream>
#include "constants.h"
#include "error_debug.h"
#include "config.h"
#include "helper.h"
namespace websocket {
	namespace progressor {
		namespace error_debug {
			bool log(std::string str) {
				std::string time = handler::helper::get_time();
				if(config::LOG_MSG == true) {
					std::cout << time << ": ";
					std::cout << str << std::endl;
				}
				if(config::RECORD_MSG == true) {
					std::ofstream output;
					output.open("websocket_log.txt", std::ios::app);
					if(output.is_open()) {
						output << time << ": ";
						output << str << std::endl;
						output.close();
					}
				}
				return true;
			}

			bool error_process(int code, std::string info) {
				std::string  str = "error:";
				if (code == constants::error::ERROR_GET_ADDR_INFO) {
					str = str + "ERROR_GET_ADDR_INFO!!" + info;
				}
				else if (code == constants::error::ERROR_TCP_CONNECT_FAILED) {
					str = str + "ERROR_TCP_CONNECT_FAILED!!" + info;
				}
				else if (code == constants::error::ERROR_WEBSOCKET_CONNECT_FAILED) {
					str = str + "ERROR_WEBSOCKET_CONNECT_FAILED!!" + info;
				}
				else if (code == constants::error::ERROR_URI_IS_NULL) {

				}
				else if (code == constants::error::ERROR_URI_SCHEME) {
					str = str + "ERROR_URI_SCHEME!!" + info;
				}
				else if (code == constants::error::ERROR_URI_HOST) {
					str = str + "ERROR_URI_HOST!!" + info;
				}
				else if (code == constants::error::ERROR_URI_PORT) {
					str = str + "ERROR_URI_PORT!!" + info;
				}
				else if (code == constants::error::ERROR_URI_PATH) {
					str = str + "ERROR_URI_PATH!!" + info;
				}
				else if (code == constants::error::ERROR_URI_QUERY) {
					str = str + "ERROR_URI_QUERY!!" + info;
				}
				else if (code == constants::error::ERROR_SOCKFD_CREATE_FAILD) {
					str = str + "ERROR_SOCKFD_CREATE_FAILD!!" + info;
				}
				else if (code == constants::error::ERROR_INET_PTON_FAILD) {
					str = str + "ERROR_INET_PTON_FAILD!!" + info;
				}
				log(str);
				return true;
			}
		}
	}
}