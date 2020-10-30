#include "export.h"
#include <stdio.h>
#include <stdlib.h>


//打开文件
//  若不能打开,return -1
//读取key和value
//  if key == encrypted
//    return 0
//  else
//    return 1
int getEncryptedString(const char* v_path,char* v_str){
  int ret=-1;
  FILE *fp;
  fp=fopen(v_path,"r");
  if(fp == NULL){
    return ret;
  }
  char buf[128];
  if(fgets(buf,128,fp) != NULL){
    char key[16];
    sscanf(buf,"%[^:]:%[^:]",key,v_str);
    ret =0;
  }
  else{
    ret=1;
  }

  fclose(fp);
  return ret;




}
