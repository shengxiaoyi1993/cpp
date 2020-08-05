#ifndef BASIC_H
#define BASIC_H
#include <iostream>
#include <string>

/**
 * @brief saveFile 以文件形式保存某个字符串
 * @param content
 * @param file_dst
 */
void saveFile(char* content,std::string file_dst) ;

/**
 * @brief getStringFromFile 以字符串方式读出某个文件
 * @param dirpath
 * @param content
 * @return
 */
int getStringFromFile(std::string dirpath,char** content);

int getStringFromFile(std::string dirpath,char** content,int & v_size);


std::string integerToString(int num);


/**
 * @brief close_all_fd 关闭某一进程的文件描述符
 * @param ppid
 * @return
 */
int close_all_fd(int ppid);


#endif
