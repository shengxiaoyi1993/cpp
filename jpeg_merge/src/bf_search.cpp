#include "bf_search.h"
#include "assert.h"



void freePosition(struct Position* p_pos){
  if(p_pos != NULL){
    freePosition(p_pos->next);
    free(p_pos);
    p_pos=NULL;
  }
  return;

}


struct Position * searchItem(const char* fileName, char item[], int itemSize, int v_count)
{
  struct Position * findItemPositions = NULL,*p,*q;

  FILE * infile = fopen(fileName,"rb");

  if (infile == NULL ) {
    perror("fopen()");
    printf("%s:Fail to fopen %s\n",__func__,fileName);
    return findItemPositions;
  }


  char *temp = (char*)malloc(itemSize*sizeof(char));
  assert(temp);

  int counter=v_count;

  while(fread(temp,itemSize,1,infile) != 0 && counter>0 )
  {

    // 找到匹配项
    if(memcmp(item,temp,itemSize)==0)
    {
      counter--;

      if(findItemPositions == NULL)
      {
        findItemPositions = (struct Position*)malloc(sizeof(struct Position));
        findItemPositions -> start  = ftell(infile)-itemSize;
        findItemPositions -> end= ftell(infile)-1;
        findItemPositions -> next  = NULL;
        p = findItemPositions;

      }
      else
      {
        q = (struct Position*)malloc(sizeof(struct Position));
        q -> start  = ftell(infile)-itemSize;
        q -> end= ftell(infile)-1;
        q -> next = NULL;
        p->next = q;
        p = q;
      }

    }//end of match
    else{
      // 文件指针回溯
      fseek(infile,-(itemSize-1),SEEK_CUR);

    }//end of not match
  }

  fclose(infile);
  infile=NULL;
  free(temp);
  temp=NULL;

  return findItemPositions;

}

struct Position * searchItemReverse(const char* fileName,char item[],int itemSize,int v_count){
  struct Position * findItemPositions = NULL,*p,*q;

  FILE * infile = fopen(fileName,"rb");

  if (infile == NULL ) {
    perror("fopen()");
    printf("%s:Fail to fopen %s\n",__func__,fileName);
    return findItemPositions;
  }


  char *temp = (char*)malloc(itemSize*sizeof(char));
  assert(temp);

  int counter=v_count;

  //定位到最末尾的位置,恰好读取目标尺寸的数据

  fseek(infile,-itemSize,SEEK_END);

  //之后每次读取数据都会定位到该前一个字节
  while(fread(temp,itemSize,1,infile) != 0 && counter>0 )
  {
    // 找到匹配项
    if(memcmp(item,temp,itemSize)==0)
    {
      counter--;

      if(findItemPositions == NULL)
      {
        findItemPositions = (struct Position*)malloc(sizeof(struct Position));
        findItemPositions -> start  = ftell(infile)-itemSize;
        findItemPositions -> end= ftell(infile)-1;
        findItemPositions -> next  = NULL;
        p = findItemPositions;

      }
      else
      {
        q = (struct Position*)malloc(sizeof(struct Position));
        q -> start  = ftell(infile)-itemSize;
        q -> end= ftell(infile)-1;
        q -> next = NULL;
        p->next = q;
        p = q;
      }

    }//end of match
    else{
      // 文件指针回溯
      fseek(infile,-(itemSize+1),SEEK_CUR);

    }//end of not match
  }

  fclose(infile);
  infile=NULL;
  free(temp);
  temp=NULL;

  return findItemPositions;
}



/// 打开文件
/// 读取数据
int getValue(const char* fileName,char item[],unsigned int itemSize,int v_offset){
  int ret;
  ///确定
  FILE * fp=fopen(fileName,"rb");
  if (fp == NULL) {
    printf("%s:Fail to open\n",__func__);
    return -1;
  }

  fseek(fp,v_offset,SEEK_CUR);
  size_t size_read =fread(item,1,itemSize,fp);
  fclose(fp);
  if (size_read == itemSize ) {
    ret=0;
  }
  else{
    printf("itemSize:%d v_offset:%d size_read:%lu\n",itemSize,v_offset,size_read);
    perror("fread()");
    printf("%s:Fail to read\n",__func__);
    ret =-1;
  }
  return ret;

}



int setValue(const char* fileName, char item[], unsigned int itemSize, int v_offset){
  int ret;
  ///确定,可读写方式打开二进制文件
  FILE * fp=fopen(fileName,"rb+");
  if (fp == NULL) {
    printf("%s:Fail to open\n",__func__);
    return -1;
  }

  fseek(fp,v_offset,SEEK_CUR);
  size_t size_write =fwrite(item,1,itemSize,fp);
  fclose(fp);
  if (size_write == itemSize ) {
    ret=0;
  }
  else{
    printf("itemSize:%d v_offset:%d size_write:%lu\n",itemSize,v_offset,size_write);
    perror("fwrite()");
    printf("%s:Fail to write\n",__func__);
    ret =-1;
  }
  return ret;

}

/// 读取为v_file_src大小,分析范围是否合适
/// 创建新文件
/// 将待删除内容的前面部分添加到新文件
/// 将后面内容追加到新文件
int rmAndCopy(const char* v_file_target,
              const char* v_file_src,
              unsigned int v_offset_start,
              unsigned int v_offset_end){
  FILE *fp_src=fopen(v_file_src,"rb");
  if (fp_src == NULL) {
    perror("fopen()");
    return -1;
  }

  fseek(fp_src,0L,SEEK_END);
  long intsize=ftell(fp_src);
  if (!(v_offset_start<=v_offset_end&&v_offset_end<intsize)) {
    printf("filezise:%ld\n",intsize);
    printf("v_offset_start:%d\n",v_offset_start);
    printf("v_offset_end:%d\n",v_offset_end);
    printf("%s:range of offset is wrong!\n",__func__);
    return -1;
  }

  FILE *fp_target=fopen(v_file_target,"wb+");
  if (fp_target == NULL) {
    printf("%s:Fail to create %s\n",__func__,v_file_target);
    fclose(fp_src);
    fp_src=NULL;
    return -1;
  }

  char *p_front=(char*)malloc(sizeof (char)*v_offset_start);
  char *p_back=(char*)malloc(sizeof (char)*(intsize-v_offset_start));
  assert(p_front);
  assert(p_back);

  fseek(fp_src,0L,SEEK_SET);
  int size_read_front=fread(p_front,sizeof (char),v_offset_start,fp_src);
  if (size_read_front != v_offset_start) {
    printf("size_read_back:%d\n",size_read_front);
    printf("size_back:%ld\n",v_offset_start);
    printf("%s:Fail to fread %s\n",__func__,v_file_src);
    fclose(fp_src);
    fp_src=NULL;
    free(p_front);
    p_front=NULL;
    free(p_back);
    p_back=NULL;
    return -1;
  }

  fseek(fp_src,v_offset_end+1,SEEK_SET);
  long size_back=intsize-(v_offset_end+1);
  int size_read_back=fread(p_back,sizeof (char),size_back,fp_src);
  if (size_read_back != size_back) {
    printf("size_read_back:%d\n",size_read_back);
    printf("size_back:%ld\n",size_back);
    printf("%s:Fail to fread %s\n",__func__,v_file_src);
    fclose(fp_src);
    fp_src=NULL;
    free(p_front);
    p_front=NULL;
    free(p_back);
    p_back=NULL;
    return -1;
  }

  size_t size_write_front= fwrite(p_front,sizeof (char),v_offset_start,fp_target);
  if (size_write_front != v_offset_start) {
    printf("%s:Fail to fwrite %s\n",__func__,v_file_target);
    fclose(fp_src);
    fclose(fp_target);

    fp_src=NULL;
    free(p_front);
    p_front=NULL;
    free(p_back);
    p_back=NULL;
    return -1;
  }


  size_t size_write_back= fwrite(p_back,sizeof (char),size_back,fp_target);
  if (size_write_back != size_back) {
    printf("%s:Fail to fwrite %s\n",__func__,v_file_target);
    fclose(fp_src);
    fclose(fp_target);

    fp_src=NULL;
    free(p_front);
    p_front=NULL;
    free(p_back);
    p_back=NULL;
    return -1;
  }


  fclose(fp_src);
  fclose(fp_target);

  fp_src=NULL;
  free(p_front);
  p_front=NULL;
  free(p_back);
  p_back=NULL;
  return 0;



}



