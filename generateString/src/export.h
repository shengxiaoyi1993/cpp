#ifndef EXPORT_H



#include <vector>
#include <iostream>
#include <string>

using namespace std;
/** generateSNString 产生包含大小写字母、数字的字符串
*@param v_length    字符串长度
*@param v_hasbig    是否包含大写字母
*@param v_hassmall  是否包含小写字母
*@param v_hasnumber 是否包含数字
*
*/
string generateSNString(int v_length,bool v_hasbig,bool v_hassmall,bool v_hasnumber );

/** generateEncryptedString 产生加密字符串
*@param v_basic  可变字符部分，通常是sn码
*@param v_key    固定字符
*
*/
string generateEncryptedString(string v_basic,string v_key);

#endif
