

#ifndef JPEG_OP_H
#define JPEG_OP_H
/*
* Copyright (c) 2021-04-22, DigitalVersion Inc. - All Rights Reserved
*
********************************************************************************
*
* @Author: shengxiaoyi2014@icloud.com (XiaoYi Sheng)
*
********************************************************************************
*
* @Usage:
*   1. 纯c/c++实现读取jpeg图片中的信息
*   2. 将相同宽度和压缩变量的图片快速拼接成一张(非解压)
*   3. 该模块需要有特定的编码模块配合
*
********************************************************************************
*
*/




#include <iostream>

using  namespace std;


namespace jpeg_op {


/**
 * @brief getJPEGSize
 *  - 获取jpeg图片的长和宽
 * @param v_filename
 *  - 图片路径
 * @param v_width
 *
 * @param v_height
 * @return
 */
int getJPEGSize(const string &v_filename,unsigned &v_width,unsigned & v_height);


/**
 * @brief setJPEGSize
 *  - 修改JPEG图片中的width,height
 * @param v_filename
 *  - 同getJPEGSize
 * @param v_width
 * @param v_height
 * @return
 */
int setJPEGSize(const string &v_filename,unsigned &v_width,unsigned &v_height);


/**
 * @brief appendJPEG
 *  - 将v_file_app添加到v_file_target文件中,要求图片拥有相同的宽度,及其他表如DHT/DQT等相同
 *  - 该函数不会将图片进行解码,而是修改图片的尺寸(高度),并将被添加的数据拷贝到目标图片原数据之后
 *  - v_file_target会被删除后重新创建,v_file_src与v_file_app可以是同一个
 * @param v_file_target
 *  - 目标图片路径,保存为该图片
 * @param v_file_src
 *  - 源数据文件
 * @param v_file_app
 *  - 将要添加的图片路径
 * @return
 */
int appendJPEG(const string &v_file_target,const string &v_file_src,const string &v_file_app);

/**
 * @brief appendJPEG
 *  - 将v_file_app添加到v_file_target文件中,要求图片拥有相同的宽度,及其他表如DHT/DQT等相同
 *  - 该函数不会将图片进行解码,而是修改图片的尺寸(高度),并将被添加的数据拷贝到目标图片原数据之后
 *  - 将v_file_app文件的数据添加到v_file_target后,注意v_file_target需要是图片文件,且与v_file_app不是同一个
 * @param v_file_target
 * @param v_file_app
 * @return
 */
int appendJPEG(const string &v_file_target,const string &v_file_app);

}



#endif


