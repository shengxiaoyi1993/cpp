#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include<sys/types.h>
#include<unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>

static int readBuferInRam(
        unsigned int v_addr,
        unsigned int v_size,
        unsigned char** ppdata){
    int fd;
    *ppdata=(unsigned char *)malloc(v_size*sizeof(unsigned char));
    if(*ppdata == NULL){
      printf("failed MALLOC.\n");
      fflush(stdout);
      return -1;
    }

    memset(*ppdata,'\0',v_size*sizeof(unsigned char));
    fd = open("/dev/mem",O_RDWR);
    if(fd< 0)
    {
        printf("open /dev/mem failed.\n");
        fflush(stdout);
        return -1;
    }
    ssize_t size_SEEK =lseek(fd,v_addr,SEEK_SET);
    printf("size_SEEK:%d\n", size_SEEK);

    ssize_t size=read(fd,*ppdata,v_size);
    printf("errno:%d\n", errno);


    close(fd);
    return size;
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


    printf("HELLO.\n");
    fflush(stdout);

    close(fd);
    return ret;
}


int readAndWrite(){
  const char* path="imagebuffer.txt";

  unsigned int width=1024*4;
  unsigned int height=1024*4;
  unsigned int addr=0x60000000;
  // unsigned int width=8;
  // unsigned int height=8;
  // unsigned int addr=0;
  unsigned char* data=NULL;

  int size = readBuferInRamWithMmap(addr,height*width*sizeof(unsigned char),&data);
  printf("size:%d\n", size);
  if(size >0){
    FILE *fp=fopen(path,"w");
    if(fp != NULL){
      fwrite(data,width*height,sizeof(unsigned char),fp);
      fclose(fp);
      printf("%s\n", "succeed to save buffer !");
    }
    else{
      printf("%s\n", "fail to open file !");
    }
  }
  else{
    printf("%s\n", "fail to get buffer !");
  }
  return 0;
}


int main(void)
{
  readAndWrite();
}
