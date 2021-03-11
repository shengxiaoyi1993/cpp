#include "../socket_channel/socket_channel.h"
#define FD_FILE "/home/sxy/tmpfd7"


int main(int argc, char *argv[])
{

//  FLAGS_logtostderr = 1;
  FLAGS_alsologtostderr = true;

  FLAGS_log_dir = "/home/sxy/Github/cpp/socket_channel/build/build_client/build";
  google::InitGoogleLogging(argv[0]);

  string v_resp;
  int ret=SocketChannel::query(FD_FILE,"msg from client",v_resp,1000);
  if (ret == 0) {
    LOG(INFO)<<"succeed to query:"<<v_resp;
  }
  else{
    LOG(ERROR)<<"fail to query";
  }

  return 0;
}
