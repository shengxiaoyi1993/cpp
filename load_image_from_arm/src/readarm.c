#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#define  READ_REG32(reg)  ( *((volatile int *) (reg)) )
#define  ALLOC_SIZE   (1024)


static int read_type()
{
								void * map_base;
								FILE *f;
								int type,fd;

								fd = open("/dev/mem", O_RDWR | O_SYNC);
								if (fd) {
																printf("Success to open /dev/mem fd=%08x\n", fd);
								}
								else {
																printf("Fail to open /dev/mem fd=%08x\n", fd);
								}
								map_base = mmap(0, ALLOC_SIZE, PROT_READ, MAP_PRIVATE, fd, 0x35 004 000);
								if(NULL != map_base) {
																printf("mmap suceed\n");
								}
								else{
																printf("mmap failed\n");
																return 0;
								}
								printf("map_base：%u\n",map_base);

								type = READ_REG32(map_base + 0x20);

								printf("READ_REG32 suceed\n");

								close(fd);
								munmap(map_base, ALLOC_SIZE);
								printf("munmap suceed\n");

								printf("reg32[%08x] = value[%08x] \n", map_base, type);

								type = (type & ( 1 << 27 )) >> 27;

								printf("reg32[%08x] = value[%08x] \n", map_base, type);

								return type;
}


static int readBuferInRam(
								unsigned int v_addr,
								unsigned int v_size,
								unsigned char** ppdata){
								int fd;
								*ppdata=(char *)malloc(v_size*sizeof(unsigned char));
								memset(*ppdata,'\0',v_size*sizeof(unsigned char));
								fd = open("/dev/mem",O_RDWR);
								if(fd< 0)
								{
																printf("open /dev/mem failed.\n");
																return 0;
								}

								ssize_t size=read(fd,*ppdata,v_size);
								close(fd);
							  return size;
}



int main(){
								// read_type();
}
