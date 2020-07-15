#ifndef RTSP_ENCODER_H
#define RTSP_ENCODER_H

#include <iostream>
#include <string>
#include <vector>
#include <pthread.h>
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavdevice/avdevice.h"
}
#include "AVPacketBuffer.h"




using namespace std;


typedef void (*pcallbak_getimage)(unsigned char *, unsigned int,unsigned int);

class RtspEncoder{
public:

  /**
   * @brief RtspEncoder rtsp流的解码，通过该类可以截取图片和视频
   * @param v_rtsp      rtsp码流地址，需要携带用户名/密码,如rtsp://username:pawword@url
   *
   * @param v_buflength 视频流缓冲时长，单位为ms
   */
  RtspEncoder(const string & v_rtsp,unsigned int v_buflength);
  ~RtspEncoder();
  /**
   * @brief isValid 判断设备是否处于可用状态
   * @return
   */
  bool isValid(void) const;

  /* 下面是提供的功能函数，为防止出错，同一时间只能有个函数工作*/
  /**
   * @brief getSnapShot  获取一张图片
   * @param pdata        图片存储指针，该指针需要用户手动释放
   * @param v_width      ouput 输出图片宽度（pix）
   * @param v_height     ouput 输出图片高度（pix）
   * @param v_timeoffset input 回退的时间(ms),要求（v_timeoffset<=0），
   * @return             返回值为0则结果正常；否则出错
   */
  int getSnapShot(unsigned char** pdata,
                  unsigned int & v_width,
                  unsigned int & v_height,
                  int v_timeoffset =0);
  /**
   * @brief getSnapShotV2 获取连续输出的图片
   * @param void (*callbak_getimage)(unsigned char *, unsigned int, unsigned int)
   *   回调函数作为参数，图片数据及图片的宽和高通过回调函数传出。
   *   同时注意回调函数需要立即返回，否则会阻塞该类函数的执行
   *   注意图片数据指针使用后不必释放内存
   *   该参数为NULL时不传递图片 ，只保留视频
   * @param v_length      录制时长
   * @param v_interval    截取图片的时间间隔
   * @param v_timeoffset  回退的时间(ms),要求（v_timeoffset<=0），且（|v_timeoffset|<|缓冲区时长|-|关键帧时间间隔|）
   *     缓冲区时长在RtspEncoder初始化时设置，关键帧时间间隔由设备确定，可以设置为1000ms或2000ms
   * @return             返回值为0则结果正常；否则出错
   */
  int getSnapShotV2(void (*callbak_getimage)(unsigned char *, unsigned int, unsigned int),
                     int v_length, int v_interval, int v_timeoffset =0);

  /**
   * @brief recordVideo        录制单个视频
   * @param v_length           录制时长
   * @param video_path         视频文件为".mp4"为后缀，保存到本地路径下
   * @param v_timeoffset       同getSnapShotV2
   * @return                   返回值为0则结果正常；否则出错
   */
  int recordVideo(int v_length, string video_path, int v_timeoffset =0);


  /**
   * @brief getSnapShotAndVideo 获取连续输出的图片和录制视频
   * @param void (*callbak_getimage)(unsigned char *, unsigned int, unsigned int)
   *                            同getSnapShotV2
   * @param v_length            同getSnapShotV2
   * @param v_interval          同getSnapShotV2
   * @param video_path          视频的存储位置
   * @param v_timeoffset        同getSnapShotV2
   * @return                    返回值为0则结果正常；否则出错
   */
  int getSnapShotAndVideo(void (*callbak_getimage)(unsigned char *, unsigned int, unsigned int),
                     int v_length, int v_interval,string video_path, int v_timeoffset =0);


  //放到线程中持续运行的函数
  friend  void *run(void*);

private:
  //初始化时的rtsp流地址，每个解码器只支持解码一个rtsp流
  string             _rtsp;
  //缓冲区域长度，初始化时给定
  unsigned int       _bufferlength;
  //该解码器是否可用
  bool               _isValid;
  //帧缓存块
  AVPacketBuffer*     _packetBuffer;
  AVFormatContext   *_pFormatCtx;
  int                _videoindex;
  AVCodecContext    *_pCodecCtx;
  AVCodec           *_pCodec;
  AVFrame           * _pFrame;
  uint8_t           *_out_buffer;
  AVStream          *_i_video_stream;
  AVFormatContext   *_o_pFormatCtx;
//  AVStream          *_o_video_stream;
  struct SwsContext *_img_convert_ctx;
//  const char        *video_path;
  AVFrame           *_pFrameRGB;
  int                _numBytes;
  //x frame/s
  int                _frame_rate;

  pcallbak_getimage _callbak_getimage;
  //帧数 总帧数
  int               _snap_time;
  //帧数 间隔
  int               _snap_interval;
  pthread_mutex_t _mutex_encoder;
  pthread_mutex_t _mutex_snapshot;
  pthread_mutex_t _mutex_encode_video;
  int64_t             _video_pts_record;
  int64_t             _video_dts_record;

  /**
   * @brief packet2ImageBuf 与全局变量相关，将pkt解码成图片
   * @param ppkt
   * @return
   */
  int packet2ImageBuf(AVPacket* ppkt);


};


void *run(void*);

#endif
