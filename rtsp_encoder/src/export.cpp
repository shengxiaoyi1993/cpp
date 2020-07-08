#include "export.h"
#include <time.h>
#include <ctime>


using namespace std;
namespace dm {

int saveRtspAsJpg(const char* rtsp_url, int time,
                  const char* video_path,
                  void (*callbak_getimage)(unsigned char *, unsigned int,unsigned int)){

    time_t start_time;
    std::time (&start_time);//获取Unix时间戳。

    AVFormatContext *pFormatCtx;
    int             i, videoindex;
    AVCodecContext  *pCodecCtx;
    AVCodec         *pCodec;
    AVFrame *pFrame;
    uint8_t *out_buffer;
    AVStream *i_video_stream;
    AVFormatContext *o_pFormatCtx;
    AVStream *o_video_stream;

    struct SwsContext *img_convert_ctx;
    avcodec_register_all();
    av_register_all();
    avformat_network_init();
        pFormatCtx=NULL;
//    pFormatCtx = avformat_alloc_context();

    AVDictionary* opts = NULL;
    av_dict_set(&opts, "stimeout", "6000000", 0);
    av_dict_set(&opts, "rtsp_transport", "tcp", 0);

    if (avformat_open_input(&pFormatCtx, rtsp_url, NULL,&opts) != 0)////打开网络流或文件流
    {
        printf("Couldn't open input stream.\n");
        return OperateFail;
    }

    //改善查找解码器的关键语句
        pFormatCtx->probesize = 100 *1024;
    if (avformat_find_stream_info(pFormatCtx,NULL)<0)
    {
        printf("Couldn't find stream information.\n");
        return OperateFail;
    }

    videoindex = -1;
    for (i = 0; i<pFormatCtx->nb_streams; i++)
        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            videoindex = i;
            i_video_stream = pFormatCtx->streams[i];

            break;
        }

    if (videoindex == -1)
    {
        printf("Didn't find a video stream.\n");
        return OperateFail;
    }

    avformat_alloc_output_context2(&o_pFormatCtx, NULL, NULL, video_path);
    o_video_stream = avformat_new_stream(o_pFormatCtx, NULL);

    {
        AVCodecContext *c;
        c = o_video_stream->codec;
        c->bit_rate = 400000;
        c->codec_id = i_video_stream->codec->codec_id;
        c->codec_type = i_video_stream->codec->codec_type;
        c->time_base.num = i_video_stream->time_base.num;
        c->time_base.den = i_video_stream->time_base.den;
        fprintf(stderr, "time_base.num = %d time_base.den = %d\n",
                c->time_base.num, c->time_base.den);
        c->width = i_video_stream->codec->width;
        c->height = i_video_stream->codec->height;
        c->pix_fmt = i_video_stream->codec->pix_fmt;
        printf("%d %d %d", c->width, c->height, c->pix_fmt);
        c->flags = i_video_stream->codec->flags;
        c->flags |= CODEC_FLAG_GLOBAL_HEADER;
        c->me_range = i_video_stream->codec->me_range;
        c->max_qdiff = i_video_stream->codec->max_qdiff;

        c->qmin = i_video_stream->codec->qmin;
        c->qmax = i_video_stream->codec->qmax;

        c->qcompress = i_video_stream->codec->qcompress;
    }

    avio_open(&o_pFormatCtx->pb, video_path, AVIO_FLAG_WRITE);
    avformat_write_header(o_pFormatCtx, NULL);

    pCodecCtx=pFormatCtx->streams[videoindex]->codec;
    pCodec=avcodec_find_decoder(pCodecCtx->codec_id);

    if (i_video_stream == NULL)
    {
        printf( "didn't find any video stream\n");
        return  OperateFail;
    }

    if(pCodec==NULL)
    {
        printf("Codec not found.\n");
        return -1;
    }
    if(avcodec_open2(pCodecCtx, pCodec,NULL)<0)
    {
        printf("Could not open codec.\n");
        return -1;
    }

    int last_pts = 0;
    int last_dts = 0;

    int64_t pts, dts;
    time_t current_tine;
    pFrame=av_frame_alloc();
    AVFrame  *    pFrameRGB = av_frame_alloc();
    int numBytes = avpicture_get_size(AV_PIX_FMT_RGB24, pCodecCtx->width,pCodecCtx->height);
    cout<<"numBytes:"<<numBytes<<endl;
    out_buffer = (uint8_t *) av_malloc(numBytes * sizeof(uint8_t));
    avpicture_fill((AVPicture *) pFrameRGB, out_buffer, AV_PIX_FMT_RGB24,
                   pCodecCtx->width, pCodecCtx->height);
    img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
                                     pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_RGB24, SWS_BICUBIC, NULL, NULL, NULL);

    //设置同时解码的帧数
    pCodecCtx->thread_count=2;
    printf("pCodecCtx->thread_count:%d\n",pCodecCtx->thread_count);

    int num = 1;
    bool encodesucceed=false;
//    AVPacket first_pkt;
//    av_init_packet(&first_pkt);
//    first_pkt.size = 0;
//    first_pkt.data = NULL;
    bool encodefirstframe=false;
    while (1)
    {
        num++;
        std::time (&current_tine);//获取Unix时间戳。
        if(current_tine - start_time > time){
            break;
        }
        AVPacket i_pkt;
        av_init_packet(&i_pkt);
        i_pkt.size = 0;
        i_pkt.data = NULL;
        if (av_read_frame(pFormatCtx, &i_pkt) <0 )
            break;


        if((AV_PKT_FLAG_KEY == i_pkt.flags&&callbak_getimage!=nullptr)||(!encodesucceed)){
            if(AV_PKT_FLAG_KEY == i_pkt.flags){
//                if(!encodesucceed){
//                    av_copy_packet(&first_pkt,&i_pkt);
//                }

                cout<<"isKey: "<<num<<" "<<current_tine<<endl;
            }
            else{
                cout<<"isnotKey: "<<num<<" "<<current_tine<<endl;
            }
//            HAVE_THREADS && avctx->active_thread_type & FF_THREAD_FRAME
//            printf("pCodecCtx->active_thread_type:%d\n",pCodecCtx->active_thread_type);
//            printf("FF_THREAD_FRAME:%d\n",FF_THREAD_FRAME);

            if (i_pkt.stream_index == videoindex) {
                int got_picture;
                int  ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture,&i_pkt);
                //                cout<<"got_picture: "<<got_picture<<endl;

                printf("pFrame：%d\n",pFrame->key_frame);
                printf("i_pkt%d\n",i_pkt.flags);
                if (ret < 0) {
                    cout<<"avcodec_decode_video2 fail "<<endl;
                    //        break ;
                }
                if(got_picture){
//                    if(!encodefirstframe){
//                        encodefirstframe=true;
//                        int got_first_picture;
//                        int  ret_first = avcodec_decode_video2(pCodecCtx, pFrame, &got_first_picture,&first_pkt);
//                        //                cout<<"got_picture: "<<got_picture<<endl;

//                        if (ret_first < 0) {
//                            cout<<"avcodec_decode_video2 fail "<<endl;
//                            //        break ;
//                        }
//                        if(got_picture){
//                            sws_scale(img_convert_ctx,
//                                      (uint8_t const * const *) pFrame->data,
//                                      pFrame->linesize, 0, pCodecCtx->height, pFrameRGB->data,
//                                      pFrameRGB->linesize);
//                            callbak_getimage(out_buffer,pCodecCtx->width,pCodecCtx->height);
//                            printf("first image endecode");
//                        }
//                        av_free_packet(&first_pkt);
//                    }
                    encodesucceed=true;
                    sws_scale(img_convert_ctx,
                              (uint8_t const * const *) pFrame->data,
                              pFrame->linesize, 0, pCodecCtx->height, pFrameRGB->data,
                              pFrameRGB->linesize);

                    //                    QImage tmpImg((uchar *)out_buffer,pCodecCtx->width,pCodecCtx->height,QImage::Format_RGB888);
                    //                    static int seq_image=0;
                    //                    tmpImg.save(QString::number(seq_image)+".jpg");
                    //                    seq_image++;
                    //                    cout<<"seq_image:"<<seq_image<<endl;

                    //使用回调函数上传数据
                    callbak_getimage(out_buffer,pCodecCtx->width,pCodecCtx->height);
                }
            }
        }


        av_interleaved_write_frame(o_pFormatCtx, &i_pkt);
        av_free_packet(&i_pkt);
        /*
      * pts and dts should increase monotonically
      * pts should be >= dts
      */
        //        i_pkt.flags |= AV_PKT_FLAG_KEY;
        pts = i_pkt.pts;
        i_pkt.pts += last_pts;
        dts = i_pkt.dts;
        i_pkt.dts += last_dts;
        i_pkt.stream_index = 0;
    }
    last_dts += dts;
    last_pts += pts;


    avformat_close_input(&pFormatCtx);
    av_write_trailer(o_pFormatCtx);
    avio_close(o_pFormatCtx->pb);
    avformat_free_context(o_pFormatCtx);

    return Normal;
}



int SaveToH264(const char* rtsp_url,int time,const char* video_path){


    AVFormatContext *pFormatCtx;
    int             i, videoindex;
    AVCodecContext  *pCodecCtx;
    AVCodec         *pCodec;
    AVFrame *pFrame, *pFrameYUV;
    uint8_t *out_buffer;
    AVPacket *packet;
    AVStream *i_video_stream;
    AVStream *o_video_stream;
    AVFormatContext *o_pFormatCtx;

    //video_mutex.lock();

    struct SwsContext *img_convert_ctx;
    // 改成你自己的 URL
    //  char filepath[] = "rtsp://admin:admin123@192.168.1.118:554/cam/realmonitor?channel=1&subtype=0&unicast=true&proto=Onvif";
    avcodec_register_all();
    av_register_all();
    avformat_network_init();
    //  pFormatCtx = avformat_alloc_context();
    pFormatCtx=NULL;
    //  AVIOInterruptCB cb = {CallBackFunc, NULL};
    //  pFormatCtx->interrupt_callback = cb;
    //这个没什么用
    //  pFormatCtx->flags |= AVFMT_FLAG_NONBLOCK;
    AVDictionary* opts = NULL;
    av_dict_set(&opts, "stimeout", "6000000", 0);
    av_dict_set(&opts, "rtsp_transport", "tcp", 0);

    if (avformat_open_input(&pFormatCtx, rtsp_url, NULL,&opts) != 0)////打开网络流或文件流
    {
        printf("Couldn't open input stream.\n");
        return OperateFail;
    }
    //qDebug()<<"*****ready to open video******"<<endl;
    if (avformat_find_stream_info(pFormatCtx, NULL)<0)

    {
        printf("Couldn't find stream information.\n");
        return OperateFail;
    }

    videoindex = -1;
    for (i = 0; i<pFormatCtx->nb_streams; i++)
        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            videoindex = i;
            i_video_stream = pFormatCtx->streams[i];

            break;
        }

    if (videoindex == -1)
    {
        printf("Didn't find a video stream.\n");
        return OperateFail;
    }
    if (i_video_stream == NULL)
    {
        printf( "didn't find any video stream\n");
        return  OperateFail;
    }

    avformat_alloc_output_context2(&o_pFormatCtx, NULL, NULL, video_path);

    o_video_stream = avformat_new_stream(o_pFormatCtx, NULL);

    {
        AVCodecContext *c;
        c = o_video_stream->codec;
        c->bit_rate = 400000;
        c->codec_id = i_video_stream->codec->codec_id;
        c->codec_type = i_video_stream->codec->codec_type;
        c->time_base.num = i_video_stream->time_base.num;
        c->time_base.den = i_video_stream->time_base.den;
        fprintf(stderr, "time_base.num = %d time_base.den = %d\n", c->time_base.num, c->time_base.den);
        c->width = i_video_stream->codec->width;
        c->height = i_video_stream->codec->height;
        c->pix_fmt = i_video_stream->codec->pix_fmt;
        printf("%d %d %d", c->width, c->height, c->pix_fmt);
        c->flags = i_video_stream->codec->flags;
        c->flags |= CODEC_FLAG_GLOBAL_HEADER;
        c->me_range = i_video_stream->codec->me_range;
        c->max_qdiff = i_video_stream->codec->max_qdiff;

        c->qmin = i_video_stream->codec->qmin;
        c->qmax = i_video_stream->codec->qmax;

        c->qcompress = i_video_stream->codec->qcompress;
    }


    avio_open(&o_pFormatCtx->pb, video_path, AVIO_FLAG_WRITE);

    avformat_write_header(o_pFormatCtx, NULL);

    // video_mutex.unlock();

    int last_pts = 0;
    int last_dts = 0;

    int64_t pts, dts;
    time_t start_time;
    time_t current_tine;
    std::time (&start_time);//获取Unix时间戳。

    int num = 1;
    while (1)
    {
        std::time (&current_tine);//获取Unix时间戳。
        if(current_tine - start_time > time){
            break;
        }
        AVPacket i_pkt;
        av_init_packet(&i_pkt);
        i_pkt.size = 0;
        i_pkt.data = NULL;
        if (av_read_frame(pFormatCtx, &i_pkt) <0 )
            break;
        /*
      * pts and dts should increase monotonically
      * pts should be >= dts
      */
        i_pkt.flags |= AV_PKT_FLAG_KEY;
        pts = i_pkt.pts;
        i_pkt.pts += last_pts;
        dts = i_pkt.dts;
        i_pkt.dts += last_dts;
        i_pkt.stream_index = 0;


        printf("frame %d %s\n", num++,video_path);

        av_interleaved_write_frame(o_pFormatCtx, &i_pkt);

    }
    last_dts += dts;
    last_pts += pts;

    //video_mutex.lock();

    avformat_close_input(&pFormatCtx);

    av_write_trailer(o_pFormatCtx);

    //avcodec_close(o_pFormatCtx->streams[0]->codec);
    //av_freep(&o_pFormatCtx->streams[0]->codec);
    //av_freep(&o_pFormatCtx->streams[0]);

    //AVStream *st;

    //o_pFormatCtx->streams[0]-
    avio_close(o_pFormatCtx->pb);
    avformat_free_context(o_pFormatCtx);

    //video_mutex.unlock();

    //  pCodecCtx = pFormatCtx->streams[videoindex]->codec;
    //  pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
    //  if (pCodec == NULL)
    //  {
    //    printf("Codec not found.\n");
    //    return OperateFail;
    //  }

    //  if (avcodec_open2(pCodecCtx, pCodec, NULL)<0)
    //  {
    //    printf("Could not open codec.\n");
    //    return OperateFail;
    //  }

    //  pFrame = av_frame_alloc();
    //  pFrameYUV = av_frame_alloc();
    //  out_buffer = (uint8_t *)av_malloc(avpicture_get_size(PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height));
    //  avpicture_fill((AVPicture *)pFrameYUV, out_buffer, PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height);

    //  //Output Info---输出一些文件（RTSP）信息
    //  //  printf("---------------- File Information ---------------\n");
    //  //  av_dump_format(pFormatCtx, 0, rtsp_url, 0);
    //  //  printf("-------------------------------------------------\n");

    //  img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
    //                                   pCodecCtx->width, pCodecCtx->height, PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);

    //  packet = (AVPacket *)av_malloc(sizeof(AVPacket));

    //  remove(video_path);

    //  FILE *fpSave;
    //  if ((fpSave = fopen(video_path, "ab")) == NULL){
    //    //qDebug()<<"can not open video"<<endl;
    //    return OperateFail ;

    //  }
    //  time_t start_time;
    //  time_t current_tine;
    //  std::time (&start_time);//获取Unix时间戳。
    //  for (;;)
    //  {
    //    std::time (&current_tine);//获取Unix时间戳。
    //    if(current_tine - start_time > time){
    //      break;
    //    }
    //    //   printf("test time:%d\n",t);
    //    //------------------------------
    //    if (av_read_frame(pFormatCtx, packet) >= 0)
    //    {
    //      if (packet->stream_index == videoindex)
    //      {
    //        fwrite(packet->data, 1, packet->size, fpSave);//写数据到文件中
    //      }
    //      av_free_packet(packet);
    //    }
    //  }


    //--------------
    //  av_frame_free(&pFrameYUV);
    //  av_frame_free(&pFrame);
    //  avcodec_close(pCodecCtx);
    //  avformat_close_input(&pFormatCtx);
    //  printf("intercept video end....\n");

    return Normal;
}




}//namespace end
