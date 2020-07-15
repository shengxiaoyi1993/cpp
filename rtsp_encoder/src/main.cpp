#include<iostream>
#include <thread>
#include "mediaproc.h"
#include "unistd.h"
#include "rtsp_encoder.h"
#include <opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;

std::string integerToString(int num){
    stringstream ss;
    ss.clear();
    ss.str("");
    string tmps;
    ss<<num;
    ss>>tmps;
    return tmps;
}


void cb_getimage(unsigned char * pdata,unsigned int v_width ,unsigned int v_height ){

    static int num=0;
    cout<<num<<": "<<"v_width: "<<v_width<<"v_height: "<<v_height<<endl;
    //转换成Mat图片
    cv::Mat mat(v_height,v_width,CV_8UC3,pdata);

    //RGBRGB->BGRBGR
    cv::cvtColor(mat,mat,cv::COLOR_RGB2BGR);

    string path= integerToString(num)+"_imagefromexport.jpg";
    cv::imwrite(path,mat);
    cout<<num<<" rows:"<<mat.rows<<"cols:"<<mat.cols<<endl;
    num++;
}
void testStaticFunc();
void testRtspEncoder();

void test_getSnapShot();
void test_getSnapShotV2();
void test_recordVideo();
void test_getSnapShotAndVideo();
void test_getSeq();


int main() {
    //    testRtspEncoder();
    testStaticFunc();



    return 0;
}


void testRtspEncoder(){
    //    test_getSnapShot();
    //    test_getSnapShotV2();
    //    test_recordVideo();
    test_getSnapShotAndVideo();

}

void test_getSeq(){
    vector<int> nums;

    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(7);
    nums.push_back(5);
    nums.push_back(9);
    nums.push_back(3);

    vector<int> seqs;
    for(uint i=0;i<seqs.size();i++){
        cout<<seqs[i]<<" ";
    }
    cout<<endl;

}


/**
 * @brief test_getSnapShot
 *
 */
void test_getSnapShot(){
    //1. 截取一次图片并保存 成功
    //2. 连续两次截图成功
    //3. 循环截图，有略微的内存泄露，仅仅是空转状态也会内存泄露
    //4. 快速取图时，有时会出现图片只有半张的情况（1秒一张进行保存时，图片完整），应该是保存图片时出现的问题
    string rtspurl="rtsp://admin:admin123@192.168.1.10:554/user=admin_password=tlJwpbo6_channel=1_stream=0.sdp?real_stream";
    RtspEncoder encoder(rtspurl,5000);
    uchar *pdata=nullptr;
    uint v_width;
    uint v_height;
    int v_time=0;

    int ret = encoder.getSnapShot(&pdata,v_width,v_height,v_time);
    if(pdata == nullptr){
        return;
    }
    if(ret ==0 ){
        cout<<"succeed to get image"<<endl;
        //转换成Mat图片
        cv::Mat mat(v_height,v_width,CV_8UC3,pdata);
        //        //RGBRGB->BGRBGR
        cv::cvtColor(mat,mat,cv::COLOR_RGB2BGR);
        string path= "singleimage.jpg";
        cv::imwrite(path,mat);
        free(pdata);
        pdata=nullptr;
    }
    else{
        cout<<"fail to get image"<<endl;
    }
    sleep(5);


    //第二次截图
    while(true){
        int ret2 = encoder.getSnapShot(&pdata,v_width,v_height,v_time);
        if(pdata == nullptr){
            return;
        }
        if(ret2 ==0 ){
            cout<<"succeed to get image"<<endl;
            //转换成Mat图片
            cv::Mat mat(v_height,v_width,CV_8UC3,pdata);
            //        //RGBRGB->BGRBGR
            cv::cvtColor(mat,mat,cv::COLOR_RGB2BGR);
            string path= "singleimage2.jpg";
            cv::imwrite(path,mat);
            //            sleep(1);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));

            free(pdata);
            pdata=nullptr;
        }
        else{
            cout<<"fail to get image"<<endl;
        }
    }


    cout<<__func__<<" end!"<<endl;
    getchar();
}


void test_getSnapShotV2(){
    //测试结果
    //1. 截图20s，得到45张图片，得到的图片数量可能与计算间隔有一些差别，因为帧是非连续的，截图是逐帧截取的
    //2. 连续两次调用正常
    //3. 循环调用正常
    //4. 当回退时间与缓存长度过于接近时，可能找不到关键帧而,因此保险一点的做法是缓存长度+回退时间>1000
    //5. 增加60s的缓存，内存使用增加40M

    string rtspurl="rtsp://admin:admin123@192.168.1.10:554/user=admin_password=tlJwpbo6_channel=1_stream=0.sdp?real_stream";
    //初始化
    RtspEncoder encoder(rtspurl,70000);

    //参数
    int totaltime=10000;//ms
    int intervaltime=500;//间隔时间
    int v_offsettime=-4000;//该值一般为非正数，其绝对值表示提前多少时间进行截图

    int ret=encoder.getSnapShotV2(cb_getimage,totaltime,intervaltime,v_offsettime);
    if(ret == 0){
        cout<<"succeed"<<endl;
    }
    else{
        cout<<"failed"<<endl;
    }

    //    while (true) {
    //        int ret2=encoder.getSnapShotV2(cb_getimage,totaltime,intervaltime,v_offsettime);
    //        if(ret2 == 0){
    //            cout<<"succeed"<<endl;
    //        }
    //        else{
    //            cout<<"failed"<<endl;
    //        }
    //    }

    getchar();
}

void test_recordVideo(){
    //测试
    //1.单词截取正常
    //2. 多次循环录制正常
    string rtspurl="rtsp://admin:admin123@192.168.1.10:554/user=admin_password=tlJwpbo6_channel=1_stream=0.sdp?real_stream";
    RtspEncoder encoder(rtspurl,10000);
    int totaltime=5000;//ms
    int v_offsettime=0;//该值一般为非正数，其绝对值表示提前多少时间进行截图

    int ret= encoder.recordVideo(totaltime,"1926.mp4",v_offsettime);
    if(ret == 0){
        cout<<"succeed"<<endl;
    }
    else{
        cout<<"fail"<<endl;
    }

    int count=0;
    while (true) {
        int ret2= encoder.recordVideo(totaltime,integerToString(count)+"_incycle.mp4",v_offsettime);
        if(ret == 0){
            cout<<"succeed"<<endl;
        }
        else{
            cout<<"fail"<<endl;
        }
        count++;
    }


    //    getchar();

}


void test_getSnapShotAndVideo(){

    //测试
    //1.单次，连续多次与循环多次均运行正常
    string rtspurl="rtsp://admin:admin123@192.168.1.10:554/user=admin_password=tlJwpbo6_channel=1_stream=0.sdp?real_stream";
    RtspEncoder encoder(rtspurl,10000);

    //参数
    int totaltime=10000;//ms
    int intervaltime=500;//间隔时间
    int v_offsettime=-4000;//该值一般为非正数，其绝对值表示提前多少时间进行截图

    int ret =encoder.getSnapShotAndVideo(cb_getimage,totaltime,intervaltime,
                                         "getSnapShotAndVideo.mp4",v_offsettime);
    if(ret == 0){
        cout<<"succeed !"<<endl;
    }
    else{
        cout<<"fail !"<<endl;
    }

    while(true){
        int ret2 =encoder.getSnapShotAndVideo(cb_getimage,totaltime,intervaltime,
                                              "getSnapShotAndVideo.mp4",v_offsettime);
        if(ret == 0){
            cout<<"succeed !"<<endl;
        }
        else{
            cout<<"fail !"<<endl;
        }
    }

    getchar();
}



void testStaticFunc(){
    saveRtspAsJpg("rtsp://admin:admin123@192.168.1.10:554/user=admin_password=tlJwpbo6_channel=1_stream=0.sdp?real_stream",
                  10,"sxy.mp4",cb_getimage);

//    //运行正常
//    SaveToH264("rtsp://admin:admin123@192.168.1.10:554/user=admin_password=tlJwpbo6_channel=1_stream=0.sdp?real_stream",
//               20, "sxy.mp4");

    return;
}
