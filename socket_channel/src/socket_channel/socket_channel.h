#ifndef SOCKET_CHANNEL_H
#define SOCKET_CHANNEL_H

#include <string>
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <stdint.h>
#include <fcntl.h>
#include <pthread.h>


#define DEBUG_SOCKETCHANNAL

#ifdef DEBUG_SOCKETCHANNAL
#include <glog/logging.h>
#endif

/*
 * 需求
 * - 本类用于实现同一PC linux下的进程间即时通信
 * - 有两种模式，客户端/服务器
 * - 服务器可以长时间listen，接收到的数据根使用回调函数进行处理
 * - 客户端发送请求后可以设置超时时间（或者其他处理方法）
 *
 * 拓展
 * -
 *
 *
 * 使用场景
 * - 类可以实例化为Server模式的对象长期存在
 * - Client以调用静态函数的方式访问Server，并接收消息
 * - S端进行监听，持续，可处理多次请求，但每一时间端只处理一个
 * - C端发送多次请求（每一时间内只存在一个待处理的请求）
 *
 * 技术支撑
 * - socket编程
 * - glog
 *
 *
 * faq
 * - accept()在监听连接时，若连接发生在调用accept()之前，是否会被调用
 *
*/


#define DEBUG

using namespace std;

typedef void (*FUNC_CB_SOCKETCHANNEL_RECV)(const string&,string&,void*);


class SocketChannel{
public:
  enum ENUM_Mode {
    ENUM_Mode_server,
    ENUM_Mode_client
  };
  SocketChannel(const string &v_file);
  ~SocketChannel();
  int listenS(FUNC_CB_SOCKETCHANNEL_RECV v_cb,void *ptr);
  static int query(const string &v_file,const string &v_qry,string &v_resp,unsigned int v_timeout);

  static void *handleNewConnection(void* ppara);


private:

  FUNC_CB_SOCKETCHANNEL_RECV __cb_recv;
  int __socket;
  int __socket_client;

  string __file;

  ENUM_Mode __mode;
  pthread_t __handle_pthread;
  bool __status_handle;
  void *__ptr;

};

void setSockNonBlock(int sock);




#endif
