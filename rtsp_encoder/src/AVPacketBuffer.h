#ifndef AVPACKETBUFFER_H
#define AVPACKETBUFFER_H
#include <iostream>
#include <vector>
#include <string>
#include <mutex>
#include <pthread.h>

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavdevice/avdevice.h"
}
//#define DEBUG_AVPACKETBUFFER

using namespace std;

typedef  struct AVPacketNode{
  AVPacketNode* _front;
  AVPacketNode* _next;
  AVPacket      _packet;
  int           _seq;
  static AVPacketNode* getAVPacketNode(){
    AVPacketNode* tmpnode =static_cast<AVPacketNode*>(malloc(sizeof (AVPacketNode)));
    if(tmpnode == nullptr){
      return nullptr;
    }
    static int seq=0;
    av_init_packet(&tmpnode->_packet);
    tmpnode->_front=nullptr;
    tmpnode->_next=nullptr;
    tmpnode->_seq=seq;
    seq++;
    return tmpnode;
  }
}AVPacketNode;

//环链结构
typedef  struct AVPacketBuffer{
  AVPacketNode* _header;
  AVPacketNode* _pointer;
  bool          _isValid;
  bool          _isReady;

  unsigned int  _size;
  pthread_mutex_t         _mutex;
  AVPacketBuffer(uint v_size);
  ~AVPacketBuffer();
  /**
   * @brief setPacketNode 设置buffer中的某节点
   * @param v_pkt
   * @return
   */
  bool setPacketNode(const AVPacket v_pkt);
  /**
   * @brief getPacketNode  获取某一节点，通过拷贝的方式，
   * 获取到packet后就不用考虑buffer发生修改对数据造成影响
   * @param v_seq
   * @param v_pkt  传入的v_pkt应为空值，函数内部不对数据进行释放，
   *               v_pkt处理结束后，应予以释放内存
   * @return
   */
  bool getPacketNode(int v_seq, AVPacket& v_pkt);
  void printPktBuf();
  AVPacketNode* findKeyFrame(int v_seq, int &v_offset);

  inline void setThreadLock(){
#ifdef DEBUG_AVPACKETBUFFER
        cout<<__func__<<endl;
#endif
        pthread_mutex_lock(&_mutex);
  }

  inline  void setTreadUnlock(){
#ifdef DEBUG_AVPACKETBUFFER
        cout<<__func__<<endl;
#endif
        pthread_mutex_unlock(&_mutex);
  }



}AVPacketBuffer;





#endif
