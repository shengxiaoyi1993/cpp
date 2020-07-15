#include "mediaproc.h"
#include <time.h>
#include <ctime>
#include <vector>
#include "unistd.h"


using namespace std;

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
    AVStream *i_video_stream=NULL;
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
    pCodecCtx->thread_count=1;
    printf("pCodecCtx->thread_count:%d\n",pCodecCtx->thread_count);

    int num = 1;
    bool encodesucceed=false;

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
            }
            else{
                continue;
            }

            if (i_pkt.stream_index == videoindex) {

                AVPacket  tmppkt;
                av_init_packet(&tmppkt);
                av_free_packet(&tmppkt);
                av_copy_packet(&tmppkt,&i_pkt);

                int got_picture;
                int  ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture,&tmppkt);


                if (ret < 0) {
                    cout<<"avcodec_decode_video2 fail "<<endl;
                }
                if(got_picture){
                    sws_scale(img_convert_ctx,
                              (uint8_t const * const *) pFrame->data,
                              pFrame->linesize, 0, pCodecCtx->height, pFrameRGB->data,
                              pFrameRGB->linesize);
                    if(callbak_getimage!= nullptr){
                        (*callbak_getimage)(out_buffer,pCodecCtx->width,pCodecCtx->height);
                    }
                    //使用回调函数上传数据
                }
            }
        }


        av_interleaved_write_frame(o_pFormatCtx, &i_pkt);
        av_free_packet(&i_pkt);

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

    avcodec_register_all();
    av_register_all();
    avformat_network_init();
    pFormatCtx=NULL;

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
        c->width = i_video_stream->codec->width;
        c->height = i_video_stream->codec->height;
        c->pix_fmt = i_video_stream->codec->pix_fmt;
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

    time_t start_time;
    time_t current_tine;

    std::time (&start_time);//获取Unix时间戳。


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

        av_interleaved_write_frame(o_pFormatCtx, &i_pkt);


    }

    avformat_close_input(&pFormatCtx);
    av_write_trailer(o_pFormatCtx);


    avio_close(o_pFormatCtx->pb);
    avformat_free_context(o_pFormatCtx);

    return Normal;
}



//记录高度顺序的列表
//将列表中的最大值逐个算出，存入列表
int getSeq(vector<int> nums,vector<int>& seqs){
    int tmp=0;
    int tmpseq=0;
    size_t size_nums=nums.size();
    seqs.resize(size_nums);

    for(uint i=0;i<size_nums;i++){
        seqs[i]=i;
    }
    for(size_t i=0;i<size_nums;i++){
        for(size_t j=0;j<size_nums-i-1;j++){
            if(nums[j]<nums[j+1]){
                tmp=nums[j];
                nums[j]=nums[j+1];
                nums[j+1]=tmp;
                tmpseq=seqs[j];
                seqs[j]=seqs[j+1];
                seqs[j+1]=tmpseq;
            }
        }
    }
    return 0;

}


