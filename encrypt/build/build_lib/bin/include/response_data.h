#ifndef RESPONSE_DATA_H
#define RESPONSE_DATA_H

#include <iostream>

/**
 * 负责把服务器的返回值解密成明文
 */

class ResponseData
{
public:
  ResponseData();

  // 把要返回给客户端的数据 origin_data 加密，密文存放在 _secret_data 里。
  ResponseData(std::string skey, std::string key_type, std::string origin_data);
  ~ResponseData();

  // json 是服务器返回的json字符串
  static ResponseData FromJson(std::string json);

  // 使用skey解密 _secret_data，结果存放在 _data 里。
  int DecodeSecretData(std::string skey);
  std::string Json();

  std::string _secret_data;
  std::string _data;
  std::string _key_type;

  static const std::string TypePublic;
  static const std::string TypeSecret;
  static const std::string TypeNoKey;

private:
  static const std::string key_secret_data;
  static const std::string key_data;
  static const std::string key_key_type;

  // 加解密的公钥
  static const std::string kPubKey;


};

#endif // RESPONSE_DATA_H
