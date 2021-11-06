#ifndef _WEBSOCKET_PROGRESSOR_URI_
#define _WEBSOCKET_PROGRESSOR_URI_
#include<string>
#include <stdint.h>
namespace websocket {
	namespace progressor {
		namespace uri {
			typedef std::string string;
			class uri {
				enum type { DOMIAN_NAME, IP_ADDRESS };
			private:
				string scheme;
				string host;
				string port;
				string path;
				string query;
				int host_type;
			public:
				uri(string &uri_str);
				bool check();
				bool get_tsl_tag();
				string get_host();
				string get_port();
				string get_path();
				string get_query();
				bool is_domain_name();
			private:
				bool check_scheme();
				bool check_host();
				bool check_port();
				bool check_path();
				bool check_query();
			};
		}
	}
}
#endif

