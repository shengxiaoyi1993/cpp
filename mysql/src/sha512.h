#ifndef SHA512_H
#define SHA512_H
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

using namespace std;

std::string hash512(std::vector<unsigned char> msg_param);


std::string getSha512ForUint(uint v_num);

/**
 * @brief getNumFrom 获取一个随即获取随机数值的SHA512编码的字符串
 * @param v_limit
 * @param v_quentity
 * @return
 */



vector<string> getNumFrom(uint v_limit,uint v_quentity);

vector<string> getRangeNumList(uint v_low,uint v_high);


#endif // SHA512_H
