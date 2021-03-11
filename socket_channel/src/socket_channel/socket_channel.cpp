#include "socket_channel.h"
#include<setjmp.h>


const unsigned LENGTH_BUFFER=20;

static jmp_buf jmpbuf;
static void sig_quit(int signo)
{
  longjmp(jmpbuf, 1);
}

//函数：设置sock为non-blocking mode
void setSockNonBlock(int sock) {
  int flags;
  flags = fcntl(sock, F_GETFL, 0);
  if (flags < 0) {
    perror("fcntl(F_GETFL) failed");
    exit(EXIT_FAILURE);
  }
  if (fcntl(sock, F_SETFL, flags | O_NONBLOCK) < 0) {
    perror("fcntl(F_SETFL) failed");
    exit(EXIT_FAILURE);
  }
}

SocketChannel::SocketChannel(const string &v_file):
  __cb_recv(nullptr),
  __socket(0)
{

  __handle_pthread=0;
  __socket_client=0;
  __file=v_file;


  //======创建socket=======//
  /// 本的通信时：
  ///   __domain:PF_UNIX/PF_LOCAL <区别>
  ///   __type :SOCK_STREAM/SOCK_DGRAM <区别>
  ///
  __socket = socket(PF_UNIX,SOCK_STREAM,0);

  if(__socket < 0) {
    LOG(FATAL)<<"fail to create __socket";
  }
  else{
    /// 在进程结束后删除文件
    /// 若不执行，则在再次打开时无法bind()到相同的文件
    /// 无法bind()的原因未知
    unlink(__file.c_str());
  }

  //======绑定=======//
  /// 本地绑定的数据结构
  struct sockaddr_un server_sockaddr;
  /// 只能是AF_LOCAL或AF_UNIX
  server_sockaddr.sun_family=PF_UNIX;
  /// sun_path是本地文件的路径。通常将文件放在/tmp目录下
  strcpy(server_sockaddr.sun_path, v_file.c_str());

  /// 一般关闭socket后，bind()的端口或者文件会保持2～4分钟
  /// 取消在关闭socket后的等待
  struct linger l;
  l.l_onoff  = true;
  l.l_linger = 0;
  setsockopt(__socket,SOL_SOCKET,SO_LINGER,(const char*)&l,sizeof(struct linger));

  /// 避免"98：Address already in use"
  /// 影响未知
  int yes = 1;
  if (setsockopt(__socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))) {
    perror("setsockopt failed");
    LOG(FATAL)<<"setsockopt failed";
  }

  setSockNonBlock(__socket);

  /// 在文件已经被bind()时，再次band()会失败
  if(bind(__socket,(struct sockaddr*)&server_sockaddr, sizeof(server_sockaddr)) < 0) {
    ///通过该函数可以查看出错原因
    string err=strerror(errno);

    close(__socket);
    LOG(FATAL)<<"fail to bind!"<<err;
  }


}

SocketChannel::~SocketChannel(){
  LOG(INFO)<<__func__;

  if (__socket_client>0) {

    int ret_close=close(__socket_client);
    if (ret_close == 0) {
      LOG(INFO)<<"succeed to close(__socket_client)";
    }
    else{
      LOG(INFO)<<"fail to close(__socket_client)"<<strerror(errno);
    }

  }

  if (__socket > 0) {

    int ret_close=close(__socket);

    if (ret_close == 0) {
      LOG(INFO)<<"succeed to close(__socket)";
    }
    else{
      LOG(INFO)<<"fail to close(__socket)"<<strerror(errno);
    }

  }

  __status_handle=false;
  void* ptr;
  pthread_join(__handle_pthread,&ptr);

}

int SocketChannel::listenS(FUNC_CB_SOCKETCHANNEL_RECV v_cb, void *v_ptr){
  __cb_recv=v_cb;
  __ptr=v_ptr;
  __status_handle = true;

  if(listen(__socket,LENGTH_BUFFER) < 0) {
    close(__socket);
    LOG(FATAL)<<"fail to bind!";
  }

  int ret = pthread_create(&__handle_pthread, nullptr, &handleNewConnection, static_cast<void*>(this));

  if (ret == 0) {
    LOG(INFO)<<"succeed to create pthread ";
  }
  else{
    LOG(INFO)<<"fail to create pthread ";
  }

  return ret;

}

/// 先根据单线程方式进行设计
/// 当检测到有新的连接时
/// 调用上层传入的函数进行数据处理
/// 然后将返回结果写入socket关闭socket
void *SocketChannel::handleNewConnection(void* ppara){
  CHECK(ppara != nullptr)<<"para wrong!";

  SocketChannel* pclass=static_cast<SocketChannel*>(ppara);
  int client_addr_len = sizeof(struct sockaddr_un);

  while (pclass->__status_handle) {

    struct sockaddr_un client_addr;
    //    if(setjmp(jmpbuf)) {
    //      exit(0);
    //    }
    //    struct linger l;
    //    l.l_onoff  = true;
    //    l.l_linger = 0;
    //    setsockopt(__socket,SOL_SOCKET,SO_LINGER,(const char*)&l,sizeof(struct linger));

    fd_set fds_read;
    FD_ZERO(&fds_read);
    FD_SET(pclass->__socket,&fds_read);

    /// 这里若没有socket可读，则在timeout时间内返回
    /// 若需要停止监听，则可以在timeout时间内重新判断是否需要监听的条件，使该进程可以正常退出
    struct timeval tv;
    tv.tv_sec=1;
    tv.tv_usec=0;
    int ret_select=select(pclass->__socket+1,&fds_read,nullptr,nullptr,&tv);
    if (ret_select <0) {
      LOG(FATAL)<<"select return err";
    }
    else if(ret_select == 0){
      LOG(INFO)<<"select timeout ";

      continue;
    }
    else{
      LOG(INFO)<<"select: has socket to read ";

      pclass->__socket_client = accept(pclass->__socket,(struct sockaddr*)&client_addr,(socklen_t*)&client_addr_len);

      if(pclass->__socket_client > 0){

        LOG(INFO)<<"new connection is ready";

        setSockNonBlock(pclass->__socket_client);

//        int flags = 0;
//        fcntl(pclass->__socket_client, F_GETFL,flags);
//        fcntl(pclass->__socket_client, F_SETFL, O_NONBLOCK | flags);

        char recv_buf[1024];
        memset(recv_buf,0,1024);

        ssize_t num=read(pclass->__socket_client,recv_buf,sizeof(recv_buf));

        //        printf("Message from client (%ld)) :%s\n",num,recv_buf);
        LOG(INFO)<<"read from socket("<<pclass->__socket_client<<"):"<<recv_buf;

        string resp;
        if (pclass->__cb_recv != nullptr) {
          pclass->__cb_recv(recv_buf,resp,pclass->__ptr);
          LOG(INFO)<<"succeed to write";
        }
        else{
          resp="fail";
        }

        //        char data_write[]="ok";
        ssize_t num_write=write(pclass->__socket_client,resp.c_str(),resp.size());

        if (num_write<0){
          LOG(ERROR)<<"fail to write";
        }
        else if (num_write == resp.size()) {
          LOG(INFO)<<"succeed to write";
        }
        else{
          LOG(ERROR)<<"fail to write all data, only a part";
        }
        close(pclass->__socket_client);
        pclass->__socket_client=0;

      }//end of get msg from client socket
      else{
        LOG(INFO)<<"fail to accept new connection";
      }

    }//end of handle return of select

  }

  return nullptr;

}

#define CAN_SERVICE "CAN_SERVICE"


int SocketChannel::query(const string &v_file,const string &v_qry,string &v_resp,unsigned int v_timeout){

  int ret;
  int socket_fd;
  char snd_buf[1024];
  static struct sockaddr_un srv_addr;

  // 创建socket
  socket_fd=socket(PF_UNIX,SOCK_STREAM,0);
  if(socket_fd<0)
  {
    perror("cannot create communication socket");
    return 1;
  }
  srv_addr.sun_family=PF_UNIX;
  strcpy(srv_addr.sun_path,v_file.c_str());

  // 连接到服务器
  ret=connect(socket_fd,(struct sockaddr*)&srv_addr,sizeof(srv_addr));
  if(ret==-1)
  {
    LOG(ERROR)<<"cannot connect to the server";
    perror("cannot connect to the server");
    close(socket_fd);
    return -1;
  }

  memset(snd_buf,0,1024);
  strcpy(snd_buf,"message from client");

  // 读取和写入
  ssize_t num_write=write(socket_fd,v_qry.c_str(),v_qry.size());
  if (num_write >= 0  &&(static_cast<ulong>(num_write) == v_qry.size())) {
    LOG(INFO)<<"succeed to write";
  }
  else{
    LOG(ERROR)<<"fail to write";
    close(socket_fd);
    return -1;
  }


  /// 接收回复过程
  /// 为实现超出timeout时间自动退出功能，
  fd_set fds_read;
  FD_ZERO(&fds_read);
  FD_SET(socket_fd,&fds_read);

  /// 这里若没有socket可读，则在timeout时间内返回
  /// 若需要停止监听，则可以在timeout时间内重新判断是否需要监听的条件，使该进程可以正常退出
  struct timeval tv;
  tv.tv_sec=v_timeout/1000;
  tv.tv_usec=(v_timeout%1000)*1000;
  int ret_select=select(socket_fd+1,&fds_read,nullptr,nullptr,&tv);
  if (ret_select <0) {
    PLOG( ERROR)<<"fail to select";
    close(socket_fd);
    return -1;
  }
  else if (ret_select ==0){
    LOG(INFO)<<"select nothing";
    close(socket_fd);
    return -1;
  }
  else{
    LOG(INFO)<<"select read change";
    if (FD_ISSET(socket_fd,&fds_read)) {
      char recv_buf[1024];
      memset(recv_buf,0,1024);
      ssize_t num=read(socket_fd,recv_buf,sizeof(recv_buf));

      if (num>0) {
        LOG(INFO)<<"succeed to read:"<<recv_buf;
        v_resp=recv_buf;
      }
      else{
        LOG(INFO)<<"fail to read:"<<recv_buf;
      }
    }
    else{
      PLOG( ERROR)<<"FD_ISSET fail ";
    }//end of FD_ISSET judge

    ///该分支检查到有数据变动

  }// end of select result handle


  close(socket_fd);
  return 0;

}
