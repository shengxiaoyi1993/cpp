#include "export.h"
#include <stdio.h>

const char * g_path="/home/sxy/Github/cpp/scan_string/resources/encrypted.txt";
int main(){
  char encryptedstring[64];
  int flag =getEncryptedString(g_path,encryptedstring);
  if(flag == 0){
    printf("%s\nencryptedstring:%s\n","succeed to getEncryptedString !",encryptedstring );
  }
  else{
    printf("%s\n","fail to getEncryptedString" );
  }
  return 0;
}
