#ifndef RTSP_ENCODER_H
#define RTSP_ENCODER_H

#include <iostream>
#include <string>
#include <vector>
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavdevice/avdevice.h"
}



using namespace std;

class RtspEncoder{
  RtspEncoder(string v_rtsp,unsigned int v_buflength);
  ~RtspEncoder();

public:
  bool isValid(void) const;
  int getSnapShot(unsigned char* pdata,
    unsigned int & v_width,
    unsigned int & v_height,
    int v_timeoffset =0);
  int getSnapShotV2( void (*callbak_getimage)(unsigned char *, unsigned int, unsigned int),
  int v_length, int v_timeoffset =0);



}



#endif
