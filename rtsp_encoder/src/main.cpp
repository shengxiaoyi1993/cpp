#include<iostream>
#include "export.h"

using namespace std;

void cb_getimage(unsigned char * pdata,unsigned int v_width ,unsigned int v_height ){

    static int num=0;
    cout<<num<<": "<<"v_width: "<<v_width<<"v_height: "<<v_height<<endl;

    //
    // //转换成Mat图片
    // cv::Mat mat(v_height,v_width,CV_8UC3,pdata);
    //
    // //RGBRGB->BGRBGR
    // cv::cvtColor(mat,mat,cv::COLOR_RGB2BGR);
    //
    // QString path= QString::number(num)+".jpg";
    // cv::imwrite(path.toStdString(),mat);
    // cout<<num<<" rows:"<<mat.rows<<"cols:"<<mat.cols<<endl;

    //    QImage image_tmp(pdata,v_width,v_height,QImage::Format_RGB888);
    //    image_tmp.save(QString::number(num)+".jpg");
    num++;
}




 int main() {
   dm::saveRtspAsJpg("rtsp://admin:admin123@192.168.1.10:554/user=admin_password=tlJwpbo6_channel=1_stream=0.sdp?real_stream",100,
                     "sxy.mp4",cb_getimage);
  return 0;
}
