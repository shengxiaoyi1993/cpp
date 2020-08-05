#ifndef DRIVER_H
#define DRIVER_H
#include <iostream>
#include <string>
#include "dvt-uio.h"
#include "out_drv.h"
#include "../../../lib/common/lib/channel_imagebuffer/channel_imagebuffer.h"

using namespace std;
/**
 * [Driver to control a device]
 * @param  v_devfile [device file]
 * @param  mode      [init mode]
 * @return           [description]
 */
class Driver{

public:
  enum DriverMode{
    DriverMode_IRQ_VALID=0X100,
    DriverMode_IRQ_INVALID=0X0,
    DriverMode_IRQ_BLOCK=0X1,
    DriverMode_IRQ_NOTBLOCK=0X0
  };

  explicit Driver(const string & v_devfile,unsigned int mode);
  void printPara();
  void setMode();

  unsigned int _VERSION;
  unsigned int _COMPANY_DIGI;
  unsigned int _COMPANY_VISI;
  unsigned int _COMPANY_ON;
  unsigned int _COMPANY_HZCN;
  unsigned int _IRQ_PORT_HIGH;
  unsigned int _IRQ_CMD_OP;
  unsigned int _IRQ_CMD_SIDE_INFO;
  unsigned int _IRQ_DATA_SIZE;
  unsigned int _IRQ_D0;
  unsigned int _IRQ_D1;
  unsigned int _IRQ_D2;
  unsigned int _IRQ_D3;
  unsigned int _MOS_CTRL_IIC_SL;
  unsigned int _MOS_CTRL_VS_HS_OEN;
  unsigned int _MOS_CTRL_SLAVE_MODE;
  unsigned int _MOS_FRAME_HS_INCK_CNT;
  unsigned int _MOS_FRAME_VS_LINE_CNT;
  unsigned int _RAW_LOC_H_OFFSET;
  unsigned int _RAW_LOC_H_SET_CNT;
  unsigned int _LOC_OFFSET;
  unsigned int _LOC_CNT;
  unsigned int _AE_MANU_GAIN;
  unsigned int _AE_MANU_EXP;
  unsigned int _RAW_STRIDE;
  unsigned int _RB_CTRL_WR_INIT_IRQ;
  unsigned int _RB_CTRL_WR_BLOCKING;
  unsigned int _RB_ADDR;
  unsigned int _RB_STRIDE;
  unsigned int _RB_LOC;
  unsigned int _RB_SLOT;
  unsigned int _mode;

/**
 * [getMsg listen the response of image Processing results]
 * @param v_data [description]
 * @param pdata  [Driver* transmit by void* ,to control the location the FPGA ouput image  ]
 */
  friend void getMsg(ImageBufferInArm v_data,void*pdata);
/**
 * [run run in sub thread to listen the signal of interrupt of FPGA]
 * @param  [name] [Driver* transmit by void* ]
 * @return        [description]
 */
  friend  void *run(void*);



private:

  string _devfile;

  unsigned int readPara(unsigned int v_addr,
                        unsigned int v_mask,
                        unsigned int v_shift,
                        unsigned int v_signed
                        );
  /**
   * [loadParaFromDev get para from FPGA regster, set the value of member value]
   */
  void loadParaFromDev();

  //设备文件
  UIO _dvt_uio;
  UIO_mmap _mmap_regs;
  UIO_mmap _mmap_pb;
  //message is sent to displaydemo or imageproc module by this channel
  ImageBufferChannel* _ch;

};

void getMsg(ImageBufferInArm v_data,void*pdata);
void *run(void*);

#endif
