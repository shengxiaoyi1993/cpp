#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include "dvt-uio.h"
#include "out_drv.h"

using namespace std;

#define OP_WR 0
#define OP_RD 1

#define MAP_REG_SIZE 0x10000
#define MAP_PB_SIZE 0x1ff00000

void usage(char *command)
{
  printf("%s:\n", command);
  printf("  -d <UIO_DEV_FILE>   UIO device file. e.g. /dev/uio0\n");
  printf("  -h                  Help\n");
  return;
}

int main(int argc, char *argv[])
{
  int c;

  char *uiod;
  uint32_t value;

  while((c = getopt(argc, argv, "d:h")) != -1) {
    switch(c) {
      case 'd':
        uiod = optarg;
        printf("%s: Device ID = %s\n", argv[0], uiod);
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

  int wait_irq_result;
  uint32_t irq_count;
  uint32_t dvt_op, dvt_slot_reg, dvt_slot_loc;

  while(1) {
    // mmap_regs.wreg32(DVT_DVT_GR_IRQ_PORT|0xa0000000, 0x00000000);
    dvt_uio.unmask_interrupt();

    wait_irq_result = dvt_uio.wait_interrupt(1000);

    printf("wait_irq_result:%d\n",wait_irq_result );
    if (wait_irq_result == 0) {
      printf("%s: Wait IRQ Timeout\n", argv[0]);
    } else if (wait_irq_result < 0) {
      printf("%s: Wait IRQ Error\n", argv[0]);
    } else {
      printf("%s: Wait IRQ get Irq_Count = %d\n", argv[0], dvt_uio.get_irq_cnt());
      mmap_regs.wreg32(DVT_DVT_GR_IRQ_PORT, 0x00000000);
      // mmap_regs.wreg32(DVT_DVT_GR_IRQ_PORT|0xa0000000, 0x00000000);

      value = mmap_regs.rreg32(DVT_DVT_GR_IRQ_CMD);
      printf("%s: Read DVT_DVT_GR_IRQ_CMD = 0x%8x\n", argv[0], value);
      dvt_op = value & DVT_GR_IRQ_CMD_OP_MASK;
      dvt_slot_reg = (value & DVT_GR_IRQ_CMD_SIDE_INFO_MASK) >> 16;
      dvt_slot_loc = (value & 0x00000300) >> 8;
      printf("%s: dvt_op = 0x%2x, dvt_slot_reg = 0x%4x, dvt_slot_loc = 0x%2x, \n", argv[0], dvt_op, dvt_slot_reg, dvt_slot_loc);
      value = mmap_regs.rreg32(DVT_DVT_GR_RB_SLOT);
      value = value & !(1 << dvt_slot_loc);
      mmap_regs.wreg32(DVT_DVT_GR_RB_SLOT, value);
      dvt_uio.unmask_interrupt();

    }

  }



  return 0;
}
