#include "uri.h"
#include "config.h"
#include "error_debug.h"
#include "constants.h"
#include <string.h>
namespace websocket {
	namespace progressor {
		namespace uri {
			uri::uri(string &uri_str) {
				//ws://host:port path?query
				if (uri_str.length() == 0) {
					//ERROR_URI_IS_NULL
					progressor::error_debug::error_process(constants::error::ERROR_URI_IS_NULL);
					return;
				}
				std::size_t pos_scheme = uri_str.find("://");
				if (pos_scheme == string::npos) {
					scheme = "";
					pos_scheme = 0;
				}
				else {
					scheme = uri_str.substr(0, pos_scheme);
					pos_scheme = pos_scheme + strlen("://");
				}

				std::size_t pos_host = uri_str.find('/', pos_scheme);
				string host_str;
				if (pos_host == string::npos) {
					pos_host = uri_str.find('?', pos_scheme);
					if (pos_host == string::npos) {
						host_str = uri_str.substr(pos_scheme);
						path = "/";
						query = "";
					}
					else
					{
						host_str = uri_str.substr(pos_scheme, pos_host - pos_scheme);
						path = "/";
					}
				}
				else {
					host_str = uri_str.substr(pos_scheme, pos_host - pos_scheme);
				}

				std::size_t pos_port = host_str.find(':');
				if (pos_port == string::npos) {
					if (scheme == "wss") {
						port = config::wss_port;
					}
					else if (scheme == "ws") {
						port = config::port;
					}
					host = host_str;
				}
				else {
					port = host_str.substr(pos_port + strlen(":"));
					host = host_str.substr(0, pos_port);
				}

				if (pos_host != string::npos) {
					std::size_t pos_path;
					if (path == "/") {
						pos_path = pos_host;
						query = uri_str.substr(pos_path + strlen("?"));
					}
					else {
						pos_path = uri_str.find('?', pos_host);
						if (pos_path == string::npos) {
							path = uri_str.substr(pos_host);
							query = "";
						}
						else {
							path = uri_str.substr(pos_host, pos_path - pos_host);
							query = uri_str.substr(pos_path + strlen("?"));
						}
					}
				}

				host_type = IP_ADDRESS;
			}

			bool uri::check() {
				if (check_scheme() == false) {
					//ERROR_URI_SCHEME
					progressor::error_debug::error_process(constants::error::ERROR_URI_SCHEME, scheme);
					return false;
				}
				if (check_host() == false) {
					//ERROR_URI_HOST
					progressor::error_debug::error_process(constants::error::ERROR_URI_HOST, host);
					return false;
				}
				if (check_port() == false) {
					//ERROR_URI_PORT
					progressor::error_debug::error_process(constants::error::ERROR_URI_PORT, port);
					return false;
				}
				if (check_path() == false) {
					//ERROR_URI_PATH
					progressor::error_debug::error_process(constants::error::ERROR_URI_PATH, path);
					return false;
				}
				if (check_query() == false) {
					//ERROR_URI_QUERY
					progressor::error_debug::error_process(constants::error::ERROR_URI_QUERY, query);
					return false;
				}
				return true;
			}

			bool uri::check_scheme() {
				if (scheme != "wss" && scheme != "ws") {
					return false;
				}
				return true;
			}
			//todo:check ipv4/ipv6 address format
			bool uri::check_host() {
				if (host == "") {
					return false;
				}
				string::iterator it;
				host_type = IP_ADDRESS;
				for (it = host.begin(); it != host.end(); it++) {
					if (*it > '9' || *it < '0' || *it == '.') {
						host_type = DOMIAN_NAME;
						break;
					}
				}
				if (host_type == DOMIAN_NAME) {
					if (host[0] == '-' || host[0] == '.') {
						return false;
					}
					for (int i = 0; i < host.size(); i++) {
						if ((host[i] != '.' && host[i] != '-' && (int)host[i] < 48) || (host[i] != '.' && (int)host[i] > 57 && (int)host[i] < 65)
							|| (host[i] != '.' && (int)host[i] > 90 && (int)host[i] < 97) || (host[i] != '.' && (int)host[i] > 122)) {
							return false;
						}
					}
				}
				return true;
			}
			//only accept number
			bool uri::check_port() {
				int port_num = 0;
				for (int i = 0; i < port.length(); i++) {
					if (port[i] < '0' || port[i] > '9') {
						return false;
					}
					port_num = port_num * 10 + port[i];
				}
				if (port_num > 65535) {
					return false;
				}
				return true;
			}

			bool uri::check_path() {
				return true;
			}
			//todo:dahdus= format error detect
			bool uri::check_query() {
				if (query != "") {
					std::size_t pos_equal = query.find('=');
					if (pos_equal == string::npos) return false;
					std::size_t pos_and = query.find('&');
					while (pos_equal != string::npos) {
						if (pos_and == string::npos) {
							if (query.find('=', pos_equal + 1) != string::npos) {
								return false;
							}
							else {
								return true;
							}
						}
						else {
							pos_equal = query.find('=', pos_and);
							if (pos_equal == string::npos) {
								return false;
							}
							else {
								pos_and = query.find('&', pos_equal);
							}
						}
					}
				}
				return true;
			}

			bool uri::get_tsl_tag() {
				if (scheme == "wss") {
					return true;
				}
				else {
					return false;
				}
			}

			string uri::get_host() {
				return host;
			}

			string uri::get_port() {
				return port;
			}

			string uri::get_path() {
				return path;
			}

			string uri::get_query() {
				if(query == ""){
					return query;
				}
				else{
					return "?" + query;
				}
			}

			bool uri::is_domain_name() {
				if (host_type == DOMIAN_NAME) {
					return true;
				}
				else {
					return false;
				}
			}
		}
	}
}
