#include "response_data.h"
#include "aes_cpp.h"
const std::string ResponseData::key_data = "data";
const std::string ResponseData::key_secret_data = "secret_data";

const std::string ResponseData::key_key_type = "key_type";
const std::string ResponseData::TypePublic = "public";
const std::string ResponseData::TypeSecret = "private";
const std::string ResponseData::TypeNoKey = "none";

// 16进制的字符串，因为hash数值可能超过127，不能用有效字符显示，所以必须转成纯字符存储
// 这里转成16进制
const std::string ResponseData::kPubKey =
    "38506c694544694f575352656434324376793731384e7542493331537252594a";


ResponseData::ResponseData()
{
  _data = "";
  _secret_data = "";
  _key_type = "";
}

ResponseData::ResponseData(std::string skey, std::string key_type,
                           std::string origin_data) {
  _data = origin_data;
  _key_type = key_type;
  _secret_data = "";

  if (key_type != TypeNoKey) {
      if (key_type == TypeSecret) {
          AesEncode(skey, _data, _secret_data);
        } else {
         AesEncode(kPubKey,_data,_secret_data);
      }
      _data = "";
  }
}

ResponseData::~ResponseData(){}

std::string ResponseData::Json() {
  neb::CJsonObject obj;
  obj.Add(key_key_type,_key_type);
  obj.Add(key_secret_data,_secret_data);
  obj.Add(key_data,_data);

  return obj.ToString();
}

ResponseData ResponseData::FromJson(std::string json) {
  neb::CJsonObject obj(json);

  ResponseData b;

  obj.Get(key_key_type,b._key_type);
  obj.Get(key_secret_data, b._secret_data);
  obj.Get(key_data,b._data);

  return b;
}

int ResponseData::DecodeSecretData(std::string skey) {
   //std::cout << "Key stype = " << _key_type << std::endl;

  if (_key_type == TypePublic) {

    AesDecode(kPubKey, _secret_data, _data);
     //std::cout << "decode public:" << _secret_data << "=>" << _data << std::endl;
  } else if (_key_type == TypeSecret) {
    AesDecode(skey, _secret_data, _data);
     //std::cout << "decode private:" << _secret_data << "=>" << _data << std::endl;
  }
  return 0;
}
