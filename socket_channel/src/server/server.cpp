#include "../socket_channel/socket_channel.h"
#define FD_FILE "/home/sxy/tmpfd7"


void cb_handle_socket_recv(const string &v_qry,string &v_resp,void *v_ptr);

int main(int argc, char *argv[])
{

//  FLAGS_minloglevel=0;

  google::InitGoogleLogging(argv[0]);

  FLAGS_log_dir = "/home/sxy/Github/cpp/socket_channel/build/build_server/build";
//  FLAGS_logtostderr = 1;
  FLAGS_alsologtostderr = true;
//  FLAGS_logtostderr = 0;

  SocketChannel SocketChannel(FD_FILE);
  SocketChannel.listenS(cb_handle_socket_recv,nullptr);

  getchar();

  return 0;

}

void cb_handle_socket_recv(const string &v_qry,string &v_resp,void *v_ptr){
  v_resp="response for "+v_qry;
  LOG(INFO)<<__func__<<"conclude:qry("<<v_qry<<")"<<"resp("<<v_resp<<")";

}
