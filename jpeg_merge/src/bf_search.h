#ifndef BF_SEARCH_H
#define BF_SEARCH_H

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
*  1. 二进制文件的数据检索
*  2. 二进制文件的某几个字节的改写
*
********************************************************************************
*
*/

#include <vector>
#include <iostream>
#include <stdio.h>

#include <string.h>

#include <stdlib.h>



struct Position

{
  long start;

  long end;

  struct Position * next;

};


void freePosition(struct Position* p_pos);

/**
 * @brief searchItem
 *  - 在文件中正向查找二进制数据
 * @param fileName
 *  - 文件名
 * @param item
 *  - 目标数据
 * @param itemSize
 *  - 目标数据大小
 * @param v_count
 *  - 目标数据数量,如v_count=1时,查找到一个就立刻返回
 * @return
 */
struct Position * searchItem(const char* fileName,char item[],int itemSize,int v_count=1 );

/**
 * @brief searchItem
 *  - 在文件中反向查找二进制数据
 * @param fileName
 *  - 文件名
 * @param item
 *  - 目标数据
 * @param itemSize
 *  - 目标数据大小
 * @param v_count
 *  - 目标数据数量,如v_count=1时,查找到一个就立刻返回
 * @return
 */
struct Position * searchItemReverse(const char* fileName,char item[],int itemSize,int v_count=1);



/**
 * @brief getValue
 *  - 获取二进制文件指定字节处的数据
 * @param fileName
 *  - 文件名
 * @param item
 *  - 结果保存数组
 * @param itemSize
 *  - item数组长度
 * @param v_offset
 *  - 查找结果距离文件起始的偏移距离
 * @return
 */
int getValue(const char* fileName, char item[], unsigned int itemSize, int v_offset);


/**
 * @brief setValue
 *  - 将二进制数据写入指定位置
 * @param fileName
 * @param item
 * @param itemSize
 * @param v_offset
 * @return
 */
int setValue(const char* fileName, char item[], unsigned int itemSize, int v_offset);

/**
 * @brief rmAndCopy
 *  - 创建v_file_target新文件,将删除数据后的内容复制到新的文件
 *  - 注意删除的内容范围不要超出文件大小
 * @param v_file_target
 *  - 创建的新文件的路径
 * @param v_file_src
 *  - 待删除内容的源文件
 * @param v_offset_start
 *  - 待删除内容起始
 * @param v_offset_end
 *  - 待删除内容终止位置
 * @return
 */
int rmAndCopy(const char* v_file_target,
              const char* v_file_src,
              unsigned int v_offset_start,
              unsigned int v_offset_end);



#endif
