#include<iostream>
#include "device.h"
 int main() {
  string path_register_info="/home/sxy/Github/cpp/register/resources/register_info.json";
  DeviceIO device_test(path_register_info);

  return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include "dvt-uio.h"
#include "out_drv.h"

using namespace std;

#define WR 0
#define RD 1

#define MAP_REG_SIZE 0x10000
#define MAP_PB_SIZE 0x07f00000

void usage(char *command)
{
  printf("%s:\n", command);
  printf("  -d <UIO_DEV_FILE>   UIO device file. e.g. /dev/uio0\n");
  printf("  -o                  Address Offset\n");
  printf("  -r                  Read\n");
  printf("  -w <VALUE>          Write Value\n");
  printf("  -m <NO>             Memory Number\n");
  printf("  -h                  Help\n");
  return;
}

int main(int argc, char *argv[])
{
  int c;

  char *uiod;
  int offset=0;
  int rnw=RD;
  int wr_word = 0;
  int map_n = 0;

  uint32_t value;

  while((c = getopt(argc, argv, "d:o:rw:m:h")) != -1) {
    switch(c) {
      case 'd':
        uiod = optarg;
        printf("%s: Device ID = %s\n", argv[0], uiod);
        break;
      case 'o':
        offset = atoi(optarg);
        printf("%s: Reg Offset = %8x\n", argv[0], offset);
        break;
      case 'r':
        rnw = RD;
        printf("%s: RNW = RD\n", argv[0]);
        break;
      case 'w':
        rnw = WR;
        wr_word = atoi(optarg);
        printf("%s: RNW =WR, write_data = %8x\n", argv[0], wr_word);
        break;
      case 'm':
        map_n = atoi(optarg);
        printf("%s: Map Number = %d\n", argv[0], map_n);
        break;
      case 'h':
        usage(argv[0]);
        return 0;
      default :
        printf("%s: Invalid Option: %c\n", argv[0], (char)c);
        usage(argv[0]);
        return -1;
    }
  }

  UIO dvt_uio(uiod);
  UIO_mmap mmap_regs(dvt_uio, 0, MAP_REG_SIZE);
  UIO_mmap mmap_pb(dvt_uio, 1, MAP_PB_SIZE);

  if (map_n == 0) {
    if (rnw == RD) {
      printf("%s: Read mmap regs %d = 0x%8x\n", argv[0], offset, value);
    } else {
      mmap_regs.wreg32(offset, wr_word);
      printf("%s: Write mmap regs %d = 0x%8x\n", argv[0], offset, wr_word);
    }
  } else {
    if (rnw == RD) {
      value = mmap_pb.rreg32(offset);
      printf("%s: Read mmap PB %d = 0x%8x\n", argv[0], offset, value);
    } else {
      mmap_pb.wreg32(offset, wr_word);
      printf("%s: Write mmap regs %d = 0x%8x\n", argv[0], offset, wr_word);
    }
  }

  // cout << "Hello, PetaLinux World!\n";
  // cout << "cmdline args:\n";
  // while(argc--)
  //   cout << *argv++ << endl;



  return 0;
}
