#include "aes_cpp.h"
#include "hex/hex.h"

void printData(char *s, const void* data, int length) {
  printf("%s:",s);
  unsigned char *d = (unsigned char*)data;
  for (int i = 0;i<length;i++) {
    printf("%02x ",d[i]);
  }
  printf("\n");
}

void AesEncode(std::string aes_key, std::string data,
               std::string& secret_data) {
  // key 在数据库或内存中，以16进制存储
  // 使用的时候要转成 unsigned char
  std::string aes_key_buff = hexencoder::DecodeHexString(aes_key);
  unsigned char* key_uchar = (unsigned char*)(aes_key_buff.data());

  // 要加密的数据转成 char
  char* data_char = (char*)malloc(data.length()+1);
  memcpy(data_char,data.data(),data.length());
  data_char[data.length()] = 0;

  // 计算密文的可能长度。
  int data_length = data.length() + 32;

  unsigned char* secret_data_uchar = (unsigned char*)malloc(data_length);
  memset(secret_data_uchar,0,data_length);

  int len = AesEncrypt(key_uchar, data_char, secret_data_uchar);
  // 密文是2进制数据，无法放进 JSON 里传输，需要转成 16 进制的字符串
  std::string secret_data_str = std::string(secret_data_uchar,
                                            secret_data_uchar+len);


  secret_data = hexencoder::EncodeToHexString(secret_data_str);

  free(data_char);
  free(secret_data_uchar);
}

void AesDecode(std::string aes_key, std::string secret_data, std::string& data) {
  // key 在数据库或内存中，以16进制存储
  // 使用的时候要转成 unsigned char
  std::string aes_key_buff = hexencoder::DecodeHexString(aes_key);
  unsigned char* key_uchar = (unsigned char*)(aes_key_buff.data());

  // 密文转成二进制数据
  std::string secret_data_str = hexencoder::DecodeHexString(secret_data);

  char *secret_data_char = const_cast<char*>(secret_data_str.data());
  unsigned char *secret_data_uchar = (unsigned char*)(secret_data_char);

  // 计算明文可能需要的长度
  int buff_length = secret_data_str.length();

  char* data_char = (char*)malloc(buff_length);

  memset(data_char,0,buff_length);

  AesDecript(key_uchar, secret_data_uchar, buff_length, data_char);

  data = data_char;

  free(data_char);
}
