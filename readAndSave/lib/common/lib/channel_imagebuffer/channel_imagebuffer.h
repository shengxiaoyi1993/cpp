#ifndef CHANNEL_IMAGEBUFFER_H
#define CHANNEL_IMAGEBUFFER_H
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include "../msgchannnel/msgchannel.h"
// #include "../cjson/cJSON.h"

using namespace std;
const unsigned int STRING_LENGTH=128;

typedef struct ImageBufferInArm{
  //内存中的地址
  unsigned int _paddr;
  //宽
  unsigned int _width;
  //高
  unsigned int _height;
  //模式
  //0:raw  1:rgb
  int _mode ;
  //序号
  unsigned long _id;
  //处理状态
  int _status;
  //存储的分区位置
  unsigned int _loc;

  ImageBufferInArm(
      unsigned int v_paddr,
      unsigned int v_width,
      unsigned int v_height,
      int v_mode,
      unsigned int v_loc,
      unsigned long v_id,
      int v_status
      ){
    _paddr=v_paddr;
    _width=v_width;
    _height=v_height;
    _mode=v_mode;
    _id=v_id;
    _status=v_status;
    _loc=v_loc;
  }

  ImageBufferInArm(){
    _paddr=0;
    _width=0;
    _height=0;
    _mode=0;
    _id=0;
    _loc=0;
    _status=-1;
  }

  static string getString(const ImageBufferInArm& v_buffer){
    char tmpstr[STRING_LENGTH];
    memset(tmpstr,0,STRING_LENGTH*sizeof(char));
    sprintf(tmpstr,"%u %u %u %d %u %u %d",
            v_buffer._paddr,
            v_buffer._width,
            v_buffer._height,
            v_buffer._mode,
            v_buffer._loc,
            v_buffer._id,
            v_buffer._status
            );
    return string(tmpstr);
  }

  static int loadFromString(const string& v_str,ImageBufferInArm& v_buffer){
    sscanf(v_str.c_str() ,"%u %u %u %d %u %u %d",
           &v_buffer._paddr,
           &v_buffer._width,
           &v_buffer._height,
           &v_buffer._mode,
           &v_buffer._loc,
           &v_buffer._id,
           &v_buffer._status);
    return 0;
  }

  static int MsgFromImageBufferInArm(const ImageBufferInArm& v_buffer,
                                     Msg& v_msg
                                     ){
    string tmpstr=ImageBufferInArm::getString(v_buffer);
    memcpy(v_msg.msg_text,tmpstr.c_str(),tmpstr.size()*sizeof (char));
    return 0;
  }

  static int ImageBufferInArmFromMsg(const Msg& v_msg,
                                     ImageBufferInArm& v_buffer                                     ){
    string tmpstr=string(v_msg.msg_text);
    return loadFromString(tmpstr,v_buffer);
  }


}ImageBufferInArm;

enum ImageBufferChannel_TYPE{
  ImageBufferChannel_TYPE_Display =0x2000
};


//PS端接受到数据后，将数据传递给该通道（producer），(custom)接受收到消息，解析数据，并传递给图片显示控件
//

typedef void (*FUNC_ImageBufferChannel_RECV)(ImageBufferInArm,void*);

class ImageBufferChannel
{

public:
  ImageBufferChannel(MsgChannel_Mode v_mode,
                     ImageBufferChannel_TYPE v_type,
                     void (*func_cb)(ImageBufferInArm ,void*),void*pdata);
  ~ImageBufferChannel();

  /**
     * @brief addNewImageBufferInArm SEND DATA
     * @param v_mgmsg
     * @return
     */
  int addNewImageBufferInArm(ImageBufferInArm v_mgmsg);

private:
  MsgChannel_Mode __mode;
  MsgChannel *__msgchannel;
  static void* __pdata;

  static void getMsg(Msg v_msg, long v_type);
  /**
     * @brief __type 说明通道用途，有三种，msgid不同
     */
  ImageBufferChannel_TYPE __type;
  static FUNC_ImageBufferChannel_RECV g_mgfunc_callback_display;


  //    FUNC_MSGCHANNEL_RECV getmsg;
  //    static void *setReceiver(void* ppara);

#ifdef DEBUG_ImageBufferChannel
  ofstream LogOut;
#endif


};


#endif
