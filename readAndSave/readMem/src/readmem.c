#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include<sys/types.h>
#include<unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>

#define DEBUG


//描述该程序的若干选择
int printHelp();

//读取内存固定物理地址中的数据
//v_addr： 内存物理地址
//v_size： 读取的数据长度（字节）
//ppdata： 保存数据的指针，空间不需要在外部申请，由该函数申请，但使用后需要手动释放内存
//return:  若读取数据成功，则输出返回得到的数据字节数
//note：   该函数涉及内存读取等系统调用，需要用root运行
static int readBuferInRamWithMmap(
        unsigned int v_addr,
        unsigned int v_size,
        unsigned char** ppdata);


int main(int argc, char const *argv[]) {
  if(argc!= 5){
    printf("\n>>Error:param not match\n\n");
    printHelp();
    return -1;
}

unsigned int addr;
unsigned int width;
unsigned int height;

sscanf(argv[1],"%x",&addr);
sscanf(argv[2],"%u",&width);
sscanf(argv[3],"%u",&height);
const char* path=argv[4];

#ifdef DEBUG
printf("addr:  0x%x\n", addr);
printf("width: %u\n", width);
printf("height:%u\n", height);
printf("path:  %s\n", path);
#endif

unsigned char* data=NULL;
int size = readBuferInRamWithMmap(addr,height*width*sizeof(unsigned char),&data);
if(size >0){
  FILE *fp=fopen(path,"w");
  if(fp != NULL){
    fwrite(data,size,sizeof(unsigned char),fp);
    fclose(fp);
    printf("%s %d\n", ">>End:succeed to save buffer ! size:",size);
  }
  else{
    printf("%s\n", ">>Error:fail to open file !");
  }
}
else{
  printf("%s\n", ">>Error:fail to get buffer !");
}
return 0;
}



int printHelp(){
  printf("please input params as below:\n" );
  printf("./readmem  [addr] [height] [width] [outputfile]\n" );
  printf("addr：  physical memory address  \n" );
  printf("note:   please run as root\n" );
  printf("e.g.:   ./readmem 0x60000000 4096 4096 imagebuffer.txt\n" );
  return 0;
}



static int readBuferInRamWithMmap(
        unsigned int v_addr,
        unsigned int v_size,
        unsigned char** ppdata){
          int ret=0;
    int fd;
    fd = open("/dev/mem",O_RDWR);
    if(fd< 0)
    {
        printf("open /dev/mem failed.\n");
        fflush(stdout);
        return -1;
    }
    *ppdata=(unsigned char *)malloc(v_size*sizeof(unsigned char));
    memset(*ppdata,'\0',v_size*sizeof(unsigned char));
    if(*ppdata == NULL){
      printf("failed MALLOC.\n");
      fflush(stdout);
      ret=-1;
    }
    else{
          void *data=mmap(NULL,sizeof(unsigned char )*v_size,
          PROT_READ|PROT_WRITE,MAP_SHARED,fd,v_addr);
          if (data == MAP_FAILED) {
                printf("failed to mmap /dev/mem!\n");
                free(*ppdata);
                *ppdata=NULL;
                ret=-1;
          }
          else{
            memcpy(*ppdata,data,sizeof(unsigned char )*v_size);
            ret=v_size;
          }
    }

    close(fd);
    return ret;
}


int readAndWrite(){
  const char* path="imagebuffer.txt";

  unsigned int width=1024*4;
  unsigned int height=1024*4;
  unsigned int addr=0x60000000;

}
