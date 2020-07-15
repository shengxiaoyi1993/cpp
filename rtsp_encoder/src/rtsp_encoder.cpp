#include "rtsp_encoder.h"
#include <iostream>
#include <vector>
#include <string>
#include <pthread.h>
#include <sys/time.h>
#include "unistd.h"
#include <thread>

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavdevice/avdevice.h"
}


using namespace std;
//#define DEBUG_RTSPENCODER

RtspEncoder::RtspEncoder(const string & v_rtsp,unsigned int v_buflength):
    _rtsp(v_rtsp),
    _bufferlength(v_buflength),
    _isValid(false)
{


    pthread_mutex_init(&_mutex_encoder,nullptr);
    pthread_mutex_init(&_mutex_encode_video,nullptr);
    pthread_mutex_init(&_mutex_snapshot,nullptr);

    _callbak_getimage = nullptr;
    _pFormatCtx=nullptr;
    _videoindex = -1;
    _pCodecCtx=nullptr;
    _pCodec=nullptr;
    _pFrame=nullptr;
    _out_buffer=nullptr;
    _i_video_stream=nullptr;
    _o_pFormatCtx=nullptr;
    _img_convert_ctx=nullptr;
    _pFrameRGB=nullptr;
    _callbak_getimage=nullptr;

    avcodec_register_all();
    av_register_all();
    avformat_network_init();

    AVDictionary* opts = nullptr;
    av_dict_set(&opts, "stimeout", "6000000", 0);
    av_dict_set(&opts, "rtsp_transport", "tcp", 0);


    //打开网络流或文件流
    if (avformat_open_input(&_pFormatCtx, _rtsp.c_str(), nullptr,&opts) != 0)
    {
        printf("Couldn't open input stream.\n");
        return ;
    }

    //改善查找解码器的关键语句
    //    _pFormatCtx->probesize = 100 *1024;
    if (avformat_find_stream_info(_pFormatCtx,nullptr)<0)
    {
        printf("Couldn't find stream information.\n");
        fflush(stdout);
        return ;
    }

    for (uint i = 0; i<_pFormatCtx->nb_streams; i++){
        if (_pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            _videoindex = static_cast<int>(i);
            _i_video_stream = _pFormatCtx->streams[i];
            break;
        }
    }


    if (_videoindex == -1)
    {
        printf("Didn't find a video stream.\n");
        return ;
    }

    _pCodecCtx=_pFormatCtx->streams[_videoindex]->codec;
    _pCodec=avcodec_find_decoder(_pCodecCtx->codec_id);
    _frame_rate=_pFormatCtx->streams[_videoindex]->avg_frame_rate.num
            /_pFormatCtx->streams[_videoindex]->avg_frame_rate.den;

    if (_i_video_stream == nullptr)
    {
        printf( "didn't find any video stream\n");
        return ;
    }

    if(_pCodec==nullptr)
    {
        printf("Codec not found.\n");
        return ;
    }
    if(avcodec_open2(_pCodecCtx, _pCodec,nullptr)<0)
    {
        printf("Could not open codec.\n");
        return ;
    }


    _pFrame=av_frame_alloc();
    _pFrameRGB = av_frame_alloc();
    _numBytes = avpicture_get_size(AV_PIX_FMT_RGB24, _pCodecCtx->width,_pCodecCtx->height);
    _out_buffer = static_cast<uint8_t *>( av_malloc(static_cast<size_t>(_numBytes) * sizeof(uint8_t)));
    avpicture_fill((AVPicture *) _pFrameRGB, _out_buffer, AV_PIX_FMT_RGB24,
                   _pCodecCtx->width, _pCodecCtx->height);
    _img_convert_ctx = sws_getContext(_pCodecCtx->width, _pCodecCtx->height, _pCodecCtx->pix_fmt,
                                      _pCodecCtx->width, _pCodecCtx->height, AV_PIX_FMT_RGB24, SWS_BICUBIC, nullptr, nullptr, nullptr);

    //    getchar();
    //设置同时解码的帧数
    _pCodecCtx->thread_count=2;
    cout<<"_frame_rate:"<<_frame_rate<<endl;
    cout<<"buffer size(f):"<<v_buflength*static_cast<uint>(_frame_rate)/1000<<endl;
    _packetBuffer=new AVPacketBuffer(v_buflength*static_cast<uint>(_frame_rate)/1000);


    fflush(stdout);

    pthread_t pid;
    int flag=pthread_create(&pid,nullptr,run,this);
    if(flag != 0){
        return;
    }

    //暂停一定时间，使缓存数据填满
    while (true) {
        if(_packetBuffer->_isReady){
            _isValid = true;
            return;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

}



RtspEncoder::~RtspEncoder(){
#ifdef DEBUG_RTSPENCODER
    cout<<__func__<<"start"<<endl;
#endif

}


bool RtspEncoder::isValid(void) const{
    return _isValid;
}

int RtspEncoder::packet2ImageBuf(AVPacket* ppkt){
#ifdef DEBUG_RTSPENCODER
    cout<<__func__<<"start"<<endl;
#endif

    int ret=-1;
    int got_picture=0;
    pthread_mutex_lock(&_mutex_encoder);
    int  ret_decode = avcodec_decode_video2(_pCodecCtx,
                                            _pFrame, &got_picture,
                                            ppkt);

    if (ret_decode < 0) {
        cout<<"avcodec_decode_video2 fail "<<endl;
    }
    if(got_picture){
        sws_scale(_img_convert_ctx,
                  (uint8_t const * const *)(_pFrame->data) ,
                  _pFrame->linesize, 0,
                  _pCodecCtx->height,
                  _pFrameRGB->data,
                  _pFrameRGB->linesize);
        ret=0;

    }

    pthread_mutex_unlock(&_mutex_encoder);

    return ret;

}





//获取该时间点回退 v_timeoffset的图片
// 首先找到这一图片之前关键帧
// 然后从该关键帧开始逐帧解码直至获取该图片
int RtspEncoder::getSnapShot(unsigned char** pdata,
                             unsigned int & v_width,
                             unsigned int & v_height,
                             int v_timeoffset ){
#ifdef DEBUG_RTSPENCODER
    cout<<__func__<<"start"<<endl;
#endif
    if(_isValid){
        _isValid=false;
    }
    else{
        cout<<"encoder is invalid!"<<endl;
        return -1;
    }

    //时间转换成帧
    int tmpframe=v_timeoffset*_frame_rate/1000;
    int ret=-1;
    _packetBuffer->setThreadLock();
    int offset=0;
    AVPacketNode* keynode=_packetBuffer->findKeyFrame(tmpframe,offset);
    cout<<"tmpframe:"<<tmpframe<<endl;
    cout<<"offset:"<<offset<<endl;

    if(keynode != nullptr){
        avcodec_flush_buffers(_pCodecCtx);

        //从关键帧开始解码，知道解出所需要的帧
        while(offset>=0||(ret!=0)){
            offset--;
            ret=packet2ImageBuf(&keynode->_packet);
            keynode=keynode->_next;
        }

        if(ret == 0){

            uint size=static_cast<uint>(_numBytes) * sizeof(uint8_t);
            * pdata=static_cast<unsigned char*>(malloc(size));
            cout<<"size:"<<size<<endl;
            memcpy(*pdata,_out_buffer,size);
            v_width=static_cast<uint>(_pCodecCtx->width);
            v_height=static_cast<uint>(_pCodecCtx->height);
        }
        avcodec_flush_buffers(_pCodecCtx);

    }
    _packetBuffer->setTreadUnlock();

    _isValid=true;
    return ret;

}

#ifdef DEBUG_RTSPENCODER

#define DEBUG_getSnapShotV2

#endif

#define DEBUG_getSnapShotV2


//1. 设置全局变量，以便传输实时传输的图片
//2. 解码缓存中的图片
//    找到关键帧
//    解码所有帧为图片，隔一定时间间隔返回以张图片
//    解码出的图片通过回调函数返回
int RtspEncoder::getSnapShotV2(void (*callbak_getimage)(unsigned char *, unsigned int, unsigned int),
                               int v_length, int v_interval, int v_timeoffset ){


#ifdef DEBUG_getSnapShotV2
    cout<<__func__<<"start"<<endl;
#endif

    if(_isValid){
        _isValid=false;
    }
    else{
        return -1;
    }
    int ret=0;


    _callbak_getimage=callbak_getimage;
    _snap_time=v_length*_frame_rate/1000;
    _snap_interval=v_interval*_frame_rate/1000;
    int frame_offset=v_timeoffset*_frame_rate/1000;
    _packetBuffer->setThreadLock();
    int offset=0;
    AVPacketNode* keynode=_packetBuffer->findKeyFrame(frame_offset,offset);
#ifdef DEBUG_getSnapShotV2
    cout<<"keynode offset:"<<offset<<endl;
#endif
    if(keynode != nullptr){
        avcodec_flush_buffers(_pCodecCtx);

        int count_interval=1;
        for(int i=0;i<=offset;i++){
#ifdef DEBUG_getSnapShotV2
            cout<<"test:"<<i<<endl;
#endif
            //            continue;
            int ret=packet2ImageBuf(&keynode->_packet);

            if(count_interval == _snap_interval){
#ifdef DEBUG_getSnapShotV2
                cout<<"count_interval:"<<count_interval<<endl;
#endif
                if(ret == 0){
                    uint size=static_cast<uint>(_numBytes) * sizeof(uint8_t);
                    unsigned char* pdata=static_cast<unsigned char*>(malloc(size));
                    memcpy(pdata,_out_buffer,size);
                    (*callbak_getimage)(pdata,
                                        static_cast<uint>(_pCodecCtx->width),
                                        static_cast<uint>(_pCodecCtx->height));
                    free(pdata);
                    pdata=nullptr;
                }
#ifdef DEBUG_getSnapShotV2
                else{
                    cout<<"fail to encode pkt"<<endl;
                }
#endif
                count_interval=1;
            }
            count_interval++;
            keynode=keynode->_next;

        }
        avcodec_flush_buffers(_pCodecCtx);

    }
#ifdef DEBUG_getSnapShotV2
    else{
        ret=-1;
        cout<<"keynode == nullptr"<<endl;
    }
#endif
    _packetBuffer->setTreadUnlock();

    std::this_thread::sleep_for(std::chrono::milliseconds(v_length-offset*1000/_frame_rate));

    pthread_mutex_lock(&_mutex_snapshot);
    _callbak_getimage=nullptr;
    pthread_mutex_unlock(&_mutex_snapshot);

#ifdef DEBUG_getSnapShotV2
    cout<<__func__<<" end"<<endl;
#endif

    _isValid=true;

    return ret;

}

#ifdef DEBUG_RTSPENCODER
#define DEBUG_recordVideo
#endif

//#define DEBUG_recordVideo

void printAVStream(AVStream* pdata){
    printf("index:%d\n",pdata->index);
}




int RtspEncoder::recordVideo(int v_length, string video_path, int v_timeoffset ){
#ifdef DEBUG_recordVideo
    cout<<__func__<<"start"<<endl;
#endif

    if(_isValid){
        _isValid=false;
    }
    else{
        return -1;
    }

    int ret=0;

    _snap_time=v_length*_frame_rate/1000;
    int frame_offset=v_timeoffset*_frame_rate/1000;
    _packetBuffer->setThreadLock();
    pthread_mutex_lock(&_mutex_encode_video);
    avformat_alloc_output_context2(&_o_pFormatCtx, nullptr, nullptr, video_path.c_str());

    bool flag_reset_record=false;
    AVStream* o_video_stream = avformat_new_stream(_o_pFormatCtx, nullptr);
    {
        AVCodecContext *c;
        c = o_video_stream->codec;
        c->bit_rate = 40000;
        c->codec_id = _i_video_stream->codec->codec_id;
        c->codec_type = _i_video_stream->codec->codec_type;
        o_video_stream->time_base.num = _i_video_stream->time_base.num;
        o_video_stream->time_base.den = _i_video_stream->time_base.den;
        c->width = _i_video_stream->codec->width;
        c->height = _i_video_stream->codec->height;
        c->pix_fmt = _i_video_stream->codec->pix_fmt;
        c->flags = _i_video_stream->codec->flags;
        c->flags |= CODEC_FLAG_GLOBAL_HEADER;
        c->me_range = _i_video_stream->codec->me_range;
        c->max_qdiff = _i_video_stream->codec->max_qdiff;
        c->qmin = _i_video_stream->codec->qmin;
        c->qmax = _i_video_stream->codec->qmax;
        c->qcompress = _i_video_stream->codec->qcompress;
    }

    avio_open(&_o_pFormatCtx->pb, video_path.c_str(), AVIO_FLAG_WRITE);
    avformat_write_header(_o_pFormatCtx, nullptr);

    int offset=0;
    AVPacketNode* keynode=_packetBuffer->findKeyFrame(frame_offset,offset);
    cout<<"offset:"<<offset<<endl;

    if(keynode != nullptr){
        for(int i=0;i<=offset;i++){
            if(!flag_reset_record){
                flag_reset_record=true;
                _video_pts_record=keynode->_packet.pts;
                _video_dts_record=keynode->_packet.dts;
            }
            int64_t tmppts=keynode->_packet.pts;
            int64_t tmpdts=keynode->_packet.pts;
            keynode->_packet.pts=tmppts-_video_pts_record;
            keynode->_packet.dts=tmpdts-_video_dts_record;
            av_interleaved_write_frame(_o_pFormatCtx, &keynode->_packet);
            keynode->_packet.pts=tmppts;
            keynode->_packet.dts=tmpdts;
            keynode=keynode->_next;
        }
    }
    else{
        ret=-1;
    }
    pthread_mutex_unlock(&_mutex_encode_video);

    _packetBuffer->setTreadUnlock();

#ifdef DEBUG_recordVideo
    cout<<__func__<<"sleep_for start"<<endl;
#endif
    std::this_thread::sleep_for(std::chrono::milliseconds(v_length-offset*1000/_frame_rate));
#ifdef DEBUG_recordVideo
    cout<<__func__<<"sleep_for end"<<endl;
#endif
    pthread_mutex_lock(&_mutex_encode_video);
    av_write_trailer(_o_pFormatCtx);
    avio_close(_o_pFormatCtx->pb);
    avformat_free_context(_o_pFormatCtx);
    _o_pFormatCtx=nullptr;
    pthread_mutex_unlock(&_mutex_encode_video);

#ifdef DEBUG_recordVideo
    cout<<__func__<<"end"<<endl;
#endif

    _isValid=true;
    return 0;
}


//同时获取图片和视频
#ifdef DEBUG_RTSPENCODER
#define DEBUG_getSnapShotAndVideo
#endif
//#define DEBUG_getSnapShotAndVideo

int RtspEncoder::getSnapShotAndVideo(void (*callbak_getimage)(unsigned char *, unsigned int, unsigned int),
                                     int v_length, int v_interval,string video_path, int v_timeoffset ){

#ifdef DEBUG_getSnapShotAndVideo
    cout<<__func__<<"start"<<endl;
#endif

    if(_isValid){
        _isValid=false;
    }
    else{
        return -1;
    }
    int ret=0;


    //抓图函数初始化
    pthread_mutex_lock(&_mutex_snapshot);
    _callbak_getimage=callbak_getimage;
    pthread_mutex_unlock(&_mutex_snapshot);

#ifdef DEBUG_getSnapShotAndVideo
    cout<<__func__<<"_callbak_getimage set"<<endl;
#endif
    int frame_offset=v_timeoffset*_frame_rate/1000;
    _snap_time=v_length*_frame_rate/1000;
    _snap_interval=v_interval*_frame_rate/1000;
    _video_pts_record=0;
    _video_dts_record=0;
    _packetBuffer->setThreadLock();
    //视频录制初始化
    avformat_alloc_output_context2(&_o_pFormatCtx, nullptr, nullptr, video_path.c_str());
    bool flag_reset_record=false;
    AVStream* o_video_stream = avformat_new_stream(_o_pFormatCtx, nullptr);
    {
        AVCodecContext *c;
        c = o_video_stream->codec;
        c->bit_rate = 40000;
        c->codec_id = _i_video_stream->codec->codec_id;
        c->codec_type = _i_video_stream->codec->codec_type;
        o_video_stream->time_base.num = _i_video_stream->time_base.num;
        o_video_stream->time_base.den = _i_video_stream->time_base.den;
        c->width = _i_video_stream->codec->width;
        c->height = _i_video_stream->codec->height;
        c->pix_fmt = _i_video_stream->codec->pix_fmt;
        c->flags = _i_video_stream->codec->flags;
        c->flags |= CODEC_FLAG_GLOBAL_HEADER;
        c->me_range = _i_video_stream->codec->me_range;
        c->max_qdiff = _i_video_stream->codec->max_qdiff;
        c->qmin = _i_video_stream->codec->qmin;
        c->qmax = _i_video_stream->codec->qmax;
        c->qcompress = _i_video_stream->codec->qcompress;
    }

    avio_open(&_o_pFormatCtx->pb, video_path.c_str(), AVIO_FLAG_WRITE);
    avformat_write_header(_o_pFormatCtx, nullptr);

    int offset=0;
    AVPacketNode* keynode=_packetBuffer->findKeyFrame(frame_offset,offset);
#ifdef DEBUG_getSnapShotAndVideo
    cout<<"keynode offset:"<<offset<<endl;
#endif
    if(keynode != nullptr){
        avcodec_flush_buffers(_pCodecCtx);

        int count_interval=1;
        for(int i=0;i<=offset;i++){
#ifdef DEBUG_getSnapShotAndVideo
            cout<<"test:"<<i<<endl;
#endif
            //            continue;
            int ret=packet2ImageBuf(&keynode->_packet);

#ifdef DEBUG_getSnapShotAndVideo
            cout<<__func__<<" ThreadID:"<<this_thread::get_id()<<endl;
            cout<<"edcode:"<<i<<endl;
#endif
            if(count_interval == _snap_interval){
#ifdef DEBUG_getSnapShotAndVideo
                cout<<"count_interval:"<<count_interval<<endl;
#endif
                if(ret == 0){
                    uint size=static_cast<uint>(_numBytes) * sizeof(uint8_t);
                    unsigned char* pdata=static_cast<unsigned char*>(malloc(size));
                    memcpy(pdata,_out_buffer,size);
                    (*callbak_getimage)(pdata,
                                        static_cast<uint>(_pCodecCtx->width),
                                        static_cast<uint>(_pCodecCtx->height));
                    free(pdata);
                    pdata=nullptr;
                }
#ifdef DEBUG_getSnapShotAndVideo
                else{
                    cout<<"fail to encode pkt"<<endl;
                }
#endif
                count_interval=1;
            }

            //将帧存入视频
            if(!flag_reset_record){
                flag_reset_record=true;
                _video_pts_record=keynode->_packet.pts;
                _video_dts_record=keynode->_packet.dts;
            }
            int64_t tmppts=keynode->_packet.pts;
            int64_t tmpdts=keynode->_packet.pts;
            keynode->_packet.pts=tmppts-_video_pts_record;
            keynode->_packet.dts=tmpdts-_video_dts_record;
            av_interleaved_write_frame(_o_pFormatCtx, &keynode->_packet);
            keynode->_packet.pts=tmppts;
            keynode->_packet.dts=tmpdts;
            \
            count_interval++;
            keynode=keynode->_next;

        }
        //清空图片解码器的缓存，以免对后续解码产生影响
        avcodec_flush_buffers(_pCodecCtx);

    }
    else{
        ret=-1;
#ifdef DEBUG_getSnapShotAndVideo
        cout<<"keynode == nullptr"<<endl;
#endif

    }
    _packetBuffer->setTreadUnlock();


    //等待一段时间，另一线程进行实时视频与图片的抓取
    std::this_thread::sleep_for(std::chrono::milliseconds(v_length-offset*1000/_frame_rate));

#ifdef DEBUG_getSnapShotAndVideo
    cout<<"stop to record"<<endl;
#endif
    //停止实时视频流中的数据抓取
    pthread_mutex_lock(&_mutex_encode_video);
    av_write_trailer(_o_pFormatCtx);
    avio_close(_o_pFormatCtx->pb);
    avformat_free_context(_o_pFormatCtx);
    _o_pFormatCtx=nullptr;
    pthread_mutex_unlock(&_mutex_encode_video);
    pthread_mutex_lock(&_mutex_snapshot);
    _callbak_getimage=nullptr;
    pthread_mutex_unlock(&_mutex_snapshot);
#ifdef DEBUG_getSnapShotAndVideo
    cout<<"end"<<endl;
#endif

    _isValid =true;
    return ret;
}


void *run(void* v_pencoder){
#ifdef DEBUG_RTSPENCODER
    cout<<__func__<<"start"<<endl;
#endif


    RtspEncoder* encoder=static_cast<RtspEncoder*>(v_pencoder);

    int last_pts = 0;
    int last_dts = 0;

    int64_t pts, dts;

    while (1)
    {


        AVPacket i_pkt;
        av_init_packet(&i_pkt);
        i_pkt.size = 0;
        i_pkt.data = nullptr;

        if (av_read_frame(encoder->_pFormatCtx, &i_pkt) <0 )
            break;
#ifdef DEBUG_RTSPENCODER
        cout<<"live stream "<<endl;
        fflush(stdout);
#endif

        encoder->_packetBuffer->setPacketNode(i_pkt);

        //如果反调函数不为空，则会解码图片，并以特定时间间隔返回图片
        pthread_mutex_lock(&encoder->_mutex_snapshot);

        if(encoder->_callbak_getimage != nullptr){
            static int count_interval=1;
            int ret=encoder->packet2ImageBuf(&i_pkt);
            if(count_interval == encoder->_snap_interval){
                if(ret == 0){
#ifdef DEBUG_RTSPENCODER
                    cout<<"image in live stream return"<<endl;
                    fflush(stdout);
#endif
                    uint size=static_cast<uint>(encoder->_numBytes) * sizeof(uint8_t);
                    unsigned char* pdata=static_cast<unsigned char*>(malloc(size));
                    memcpy(pdata,encoder->_out_buffer,size);
                    (*encoder->_callbak_getimage)(pdata,
                                                  static_cast<uint>(encoder->_pCodecCtx->width),
                                                  static_cast<uint>(encoder->_pCodecCtx->height));
                    free(pdata);
                    pdata=nullptr;
                }
#ifdef DEBUG_RTSPENCODER
                else{
                    cout<<"live stream fail to encode image"<<endl;
                }
#endif

                count_interval=1;
            }
            count_interval++;
        }
#ifdef DEBUG_RTSPENCODER
        else{
            cout<<"encoder->_callbak_getimage == nullptr"<<endl;
        }
#endif
        pthread_mutex_unlock(&encoder->_mutex_snapshot);


        pthread_mutex_lock(&encoder->_mutex_encode_video);
        if(encoder->_o_pFormatCtx != nullptr){

            int64_t tmppts=i_pkt.pts;
            int64_t tmpdts=i_pkt.pts;
            i_pkt.pts=tmppts-encoder->_video_pts_record;
            i_pkt.dts=tmpdts-encoder->_video_dts_record;
            av_interleaved_write_frame(encoder->_o_pFormatCtx, &i_pkt);
            //            av_interleaved_write_frame(_o_pFormatCtx, &i_pkt);
            i_pkt.pts=tmppts;
            i_pkt.dts=tmpdts;
        }
        pthread_mutex_unlock(&encoder->_mutex_encode_video);

        //        cout<<"i_pkt.pts:"<<i_pkt.pts<<"i_pkt.dts:"<<i_pkt.dts<<endl;


        /*
      * pts and dts should increase monotonically
      * pts should be >= dts
      */
        //        pts = i_pkt.pts;
        //        i_pkt.pts += last_pts;
        //        dts = i_pkt.dts;
        //        i_pkt.dts += last_dts;
        //        i_pkt.stream_index = 0;
    }
}


