#ifndef AES_QT_H
#define AES_QT_H

#include <iostream>
#include "aes/aes.h"
void AesEncode(std::string aes_key, std::string data, std::string &secret_data);
void AesDecode(std::string aes_key, std::string secret_data, std::string &data);

#endif  // AES_QT_H
