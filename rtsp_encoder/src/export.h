#ifndef DM_MEDIA_H
#define DM_MEDIA_H


#include<iostream>

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavdevice/avdevice.h"
}


namespace dm {

#ifndef DEF_DeviceManagerErrorType
#define DEF_DeviceManagerErrorType
enum DeviceManagerErrorType{
    Normal=1000,
    CanNotConnect=1001,
    CanNotGetInfo=1002,
    OperateFail=1003,
    QuitConnect=1004
};
#endif

/**
*  get  H264 video and save it to certain place.
*  @param   rtsp_url                   handle of get image event
*  @param   time                         the duration of video
*  @param   video_path              save the video to it
*  @return                                   return  0 if normally end
*
*  @example                         SaveToH264(rtsp_url.toLatin1().data(),time,video_path.toLatin1().data());

*/
int SaveToH264(const char* rtsp_url,int time,const char* video_path);




/**
 * @brief saveRtspAsJpg 从rtsp流中获取time 秒时间内的所有关键帧，并解码成图片，通过回调函数的方式传递图片；
 *                      保存时长为time 秒的视频流，并保存在video_path路径下
 * @param rtsp_url
 * @param time          获取关键帧的时间长度
 * @param video_path    视频的保存路径
 * @param void (*callbak_getimage)(QImage) 传递图片的回调函数，由于从rtsp流中获取的图片需要被实时处理，因此使用回调函数的方式即时传递
 *                      同时注意回调函数的的需要立即返回，否则会阻塞该函数的执行
 *                      该参数为NULL时不传递图片 ，只保留视频
 *
 * @return              返回值为0时，函数正常执行否则出错
 * @note                关键帧的频率由设备决定，若需更改图片的输出间隔，请在相机配置界面修改
 */
int saveRtspAsJpg(const char* rtsp_url, int time,
                  const char* video_path,
                 void (*callbak_getimage)(unsigned char *, unsigned int, unsigned int));



}

#endif // DM_MEDIA_H
