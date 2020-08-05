#include "driver.h"
#include <iomanip>
#include <stdio.h>
#include <sys/time.h>
#include "../../../lib/common/lib/channel_imagebuffer/channel_imagebuffer.h"

const unsigned int MAP_REG_SIZE=0x10000;
const unsigned int MAP_PB_SIZE=0x1ff00000;
const unsigned int OP_WR = 0;
const unsigned int OP_RD = 1;

#define DEBUG_DRIVER

#ifdef DEBUG_DRIVER

static struct timeval tv_record;
static struct timezone tz_record;
static struct timeval tv_current;
static struct timezone tz_current;
static void initTime(){

  gettimeofday(&tv_record, &tz_record);
}

static void outputTimeCost(){

  gettimeofday(&tv_current, &tz_current);
  unsigned int costtime=(tv_current.tv_sec-tv_record.tv_sec)*1000000+
      (tv_current.tv_usec-tv_record.tv_usec);
  printf("costtime:%u\n",costtime);
  initTime();
}

#endif



void getMsg(ImageBufferInArm v_data,void*pdata){
  cout<<"[start]"<<__func__<<endl;
  cout<<"_mode:"<<v_data._mode<<endl;
  //    struct  RegStruct tmpres=*(struct  RegStruct*)pdata;
  Driver* pdriver=(Driver*) pdata;

  unsigned int value = pdriver->_mmap_regs.rreg32(DVT_DVT_GR_RB_SLOT);
  value = value & !(1 << v_data._mode);
  cout<<"value:0x"<<hex<<value;
  pdriver->_mmap_regs.wreg32(DVT_DVT_GR_RB_SLOT, value);
  pdriver->_dvt_uio.unmask_interrupt();

  cout<<"[end ]"<<__func__<<endl;
  fflush(stdout);


}


Driver::Driver(const string & v_fdev,unsigned int mode):
  _mode(mode),
  _devfile(v_fdev),
  _dvt_uio(_devfile.c_str()),
  _mmap_regs(_dvt_uio,OP_WR,MAP_REG_SIZE),
  _mmap_pb(_dvt_uio,OP_RD,MAP_PB_SIZE),
  _ch(NULL)
{
#ifdef DEBUG_DRIVER
  initTime();
#endif


  _ch=new ImageBufferChannel(MsgChannel_Mode::producer,
                             ImageBufferChannel_TYPE_Display,
                             getMsg,this);
  if(_ch == nullptr){
    cerr<<"_ch is NULL"<<endl;
  }

  loadParaFromDev();
  //设置设备参数
  _mmap_regs.wreg32(DVT_DVT_GR_RB_CTRL, _mode);
  _mmap_regs.wreg32(DVT_DVT_GR_RB_SLOT, 0);
  _dvt_uio.unmask_interrupt();

  pthread_t pid;
  int flag=pthread_create(&pid,nullptr,run,this);
  if(flag != 0){
    return;
  }

}

void *run(void* v_pdata){
  Driver* pdriver=(Driver* )v_pdata;

  int wait_irq_result;
  uint32_t irq_count;
  uint32_t dvt_op, dvt_slot_reg, dvt_slot_loc;
  unsigned int value;

  while(1) {
//    pdriver->_dvt_uio.unmask_interrupt();

    wait_irq_result = pdriver->_dvt_uio.wait_interrupt(1000);

    printf("wait_irq_result:%d\n",wait_irq_result );
    if (wait_irq_result == 0) {
      printf(" Wait IRQ Timeout\n");
    } else if (wait_irq_result < 0) {
      printf(" Wait IRQ Error\n");
    } else {
#ifdef DEBUG_DRIVER
      outputTimeCost();
#endif

      printf("%s: Wait IRQ get Irq_Count = %d\n", "", pdriver->_dvt_uio.get_irq_cnt());
      cout<<"---------------------this is flag---------------------"<<endl;

      pdriver->_mmap_regs.wreg32(DVT_DVT_GR_IRQ_PORT, 0x00000000);
      value = pdriver->_mmap_regs.rreg32(DVT_DVT_GR_IRQ_CMD);
      cout<<"---------------------this is flag---------------------"<<endl;

      printf("%s: Read DVT_DVT_GR_IRQ_CMD = 0x%8x\n", "", value);
      dvt_op = value & DVT_GR_IRQ_CMD_OP_MASK;
      dvt_slot_reg = (value & DVT_GR_IRQ_CMD_SIDE_INFO_MASK) >> 16;
      dvt_slot_loc = (value & 0x00000300) >> 8;
      printf("%s: dvt_op = 0x%2x, dvt_slot_reg = 0x%4x, dvt_slot_loc = 0x%2x, \n"
             , "", dvt_op, dvt_slot_reg, dvt_slot_loc);

      unsigned int tmpaddr=pdriver->readPara(DVT_DVT_GR_IRQ_D1,
                                             DVT_GR_IRQ_D1_SRC_ADDR_L_MASK,
                                             DVT_GR_IRQ_D1_SRC_ADDR_L_SHIFT,
                                             DVT_GR_IRQ_D1_SRC_ADDR_L_SIGNED);


      //将数据添加到队列中
      int flag= pdriver->_ch->addNewImageBufferInArm(
            ImageBufferInArm(tmpaddr<<8,4096,4096,
                             dvt_slot_loc,pdriver->_dvt_uio.get_irq_cnt(),0));
    }
  }

}



unsigned int Driver::readPara(unsigned int v_addr,
                              unsigned int v_mask,
                              unsigned int v_shift,
                              unsigned int v_signed
                              ){
  (void)v_signed;
  unsigned value=_mmap_regs.rreg32(v_addr);
  return (value&v_mask)>>v_shift;
}


void Driver::loadParaFromDev(){
  //读取必要的参数
  _VERSION=readPara(DVT_DVT_GR_VERSION,
                    DVT_GR_VERSION_SVN_MASK,
                    DVT_GR_VERSION_SVN_SHIFT,
                    DVT_GR_VERSION_SVN_SIGNED);

  _COMPANY_DIGI=readPara(DVT_DVT_GR_COMPANY_DIGI,
                         DVT_GR_COMPANY_DIGI_ASCII_MASK,
                         DVT_GR_COMPANY_DIGI_ASCII_SHIFT,
                         DVT_GR_COMPANY_DIGI_ASCII_SIGNED);

  _COMPANY_VISI=readPara(DVT_DVT_GR_COMPANY_VISI,
                         DVT_GR_COMPANY_VISI_ASCII_MASK,
                         DVT_GR_COMPANY_VISI_ASCII_SHIFT,
                         DVT_GR_COMPANY_VISI_ASCII_SIGNED);

  _COMPANY_ON=readPara(DVT_DVT_GR_COMPANY_ON,
                       DVT_GR_COMPANY_ON_ASCII_MASK,
                       DVT_GR_COMPANY_ON_ASCII_SHIFT,
                       DVT_GR_COMPANY_ON_ASCII_SIGNED);

  _COMPANY_HZCN=readPara(DVT_DVT_GR_COMPANY_HZCN,
                         DVT_GR_COMPANY_HZCN_ASCII_MASK,
                         DVT_GR_COMPANY_HZCN_ASCII_SHIFT,
                         DVT_GR_COMPANY_HZCN_ASCII_SIGNED);

  _IRQ_PORT_HIGH=readPara(DVT_DVT_GR_IRQ_PORT,
                          DVT_GR_IRQ_PORT_HIGH_MASK,
                          DVT_GR_IRQ_PORT_HIGH_SHIFT,
                          DVT_GR_IRQ_PORT_HIGH_SIGNED);

  _IRQ_CMD_SIDE_INFO=readPara(DVT_DVT_GR_IRQ_CMD,
                              DVT_GR_IRQ_CMD_SIDE_INFO_MASK,
                              DVT_GR_IRQ_CMD_SIDE_INFO_SHIFT,
                              DVT_GR_IRQ_CMD_SIDE_INFO_SIGNED);

  _IRQ_CMD_OP=readPara(DVT_DVT_GR_IRQ_CMD,
                       DVT_GR_IRQ_CMD_OP_MASK,
                       DVT_GR_IRQ_CMD_OP_SHIFT,
                       DVT_GR_IRQ_CMD_OP_SIGNED);

  _IRQ_DATA_SIZE=readPara(DVT_DVT_GR_IRQ_DATA_SIZE,
                          DVT_GR_IRQ_DATA_SIZE_BYTES_MASK,
                          DVT_GR_IRQ_DATA_SIZE_BYTES_SHIFT,
                          DVT_GR_IRQ_DATA_SIZE_BYTES_SIGNED);

  _IRQ_D0=readPara(DVT_DVT_GR_IRQ_D0,
                   DVT_GR_IRQ_D0_SRC_ADDR_H_MASK,
                   DVT_GR_IRQ_D0_SRC_ADDR_H_SHIFT,
                   DVT_GR_IRQ_D0_SRC_ADDR_H_SIGNED);

  _IRQ_D1=readPara(DVT_DVT_GR_IRQ_D1,
                   DVT_GR_IRQ_D1_SRC_ADDR_L_MASK,
                   DVT_GR_IRQ_D1_SRC_ADDR_L_SHIFT,
                   DVT_GR_IRQ_D1_SRC_ADDR_L_SIGNED);

  _IRQ_D2=readPara(DVT_DVT_GR_IRQ_D2,
                   DVT_GR_IRQ_D2_DEST_ADDR_H_MASK,
                   DVT_GR_IRQ_D2_DEST_ADDR_H_SHIFT,
                   DVT_GR_IRQ_D2_DEST_ADDR_H_SIGNED);

  _IRQ_D3=readPara(DVT_DVT_GR_IRQ_D3,
                   DVT_GR_IRQ_D3_DEST_ADDR_L_MASK,
                   DVT_GR_IRQ_D3_DEST_ADDR_L_SHIFT,
                   DVT_GR_IRQ_D3_DEST_ADDR_L_SIGNED);

  _MOS_CTRL_IIC_SL=readPara(DVT_DVT_GR_MOS_CTRL,
                            DVT_GR_MOS_CTRL_SLAVE_MODE_MASK,
                            DVT_GR_MOS_CTRL_SLAVE_MODE_SHIFT,
                            DVT_GR_MOS_CTRL_SLAVE_MODE_SIGNED);

  _MOS_CTRL_VS_HS_OEN=readPara(DVT_DVT_GR_MOS_CTRL,
                               DVT_GR_MOS_CTRL_VS_HS_OEN_MASK,
                               DVT_GR_MOS_CTRL_VS_HS_OEN_SHIFT,
                               DVT_GR_MOS_CTRL_VS_HS_OEN_SIGNED);

  _MOS_CTRL_SLAVE_MODE=readPara(DVT_DVT_GR_MOS_CTRL,
                                DVT_GR_MOS_CTRL_IIC_SL_MASK,
                                DVT_GR_MOS_CTRL_IIC_SL_SHIFT,
                                DVT_GR_MOS_CTRL_IIC_SL_SIGNED);

  _MOS_FRAME_HS_INCK_CNT=readPara(DVT_DVT_GR_MOS_FRAME,
                                  DVT_GR_MOS_FRAME_VS_LINE_CNT_MASK,
                                  DVT_GR_MOS_FRAME_VS_LINE_CNT_SHIFT,
                                  DVT_GR_MOS_FRAME_VS_LINE_CNT_SIGNED);

  _MOS_FRAME_VS_LINE_CNT=readPara(DVT_DVT_GR_MOS_FRAME,
                                  DVT_GR_MOS_FRAME_HS_INCK_CNT_MASK,
                                  DVT_GR_MOS_FRAME_HS_INCK_CNT_SHIFT,
                                  DVT_GR_MOS_FRAME_HS_INCK_CNT_SIGNED);

  _RAW_LOC_H_OFFSET=readPara(DVT_DVT_GR_RAW_LOC_H,
                             DVT_GR_RAW_LOC_H_SET_CNT_MASK,
                             DVT_GR_RAW_LOC_H_SET_CNT_SHIFT,
                             DVT_GR_RAW_LOC_H_SET_CNT_SIGNED);

  _RAW_LOC_H_SET_CNT=readPara(DVT_DVT_GR_RAW_LOC_H,
                              DVT_GR_RAW_LOC_H_OFFSET_MASK,
                              DVT_GR_RAW_LOC_H_OFFSET_SHIFT,
                              DVT_GR_RAW_LOC_H_OFFSET_SIGNED);

  _LOC_OFFSET=readPara(DVT_DVT_GR_RAW_LOC_V,
                       DVT_GR_RAW_LOC_V_CNT_MASK,
                       DVT_GR_RAW_LOC_V_CNT_SHIFT,
                       DVT_GR_RAW_LOC_V_CNT_SIGNED);

  _LOC_CNT=readPara(DVT_DVT_GR_RAW_LOC_V,
                    DVT_GR_RAW_LOC_V_OFFSET_MASK,
                    DVT_GR_RAW_LOC_V_OFFSET_SHIFT,
                    DVT_GR_RAW_LOC_V_OFFSET_SIGNED);

  _AE_MANU_EXP=readPara(DVT_DVT_GR_AE_MANU,
                        DVT_GR_AE_MANU_EXP_MASK,
                        DVT_GR_AE_MANU_EXP_SHIFT,
                        DVT_GR_AE_MANU_EXP_SIGNED);

  _AE_MANU_GAIN=readPara(DVT_DVT_GR_AE_MANU,
                         DVT_GR_AE_MANU_GAIN_MASK,
                         DVT_GR_AE_MANU_GAIN_SHIFT,
                         DVT_GR_AE_MANU_GAIN_SIGNED);

  _RAW_STRIDE=readPara(DVT_DVT_GR_RAW_STRIDE,
                       DVT_GR_RAW_STRIDE_GENERAL_MASK,
                       DVT_GR_RAW_STRIDE_GENERAL_SHIFT,
                       DVT_GR_RAW_STRIDE_GENERAL_SIGNED);

  _RB_CTRL_WR_BLOCKING=readPara(DVT_DVT_GR_RB_CTRL,
                                DVT_GR_RB_CTRL_WR_BLOCKING_MASK,
                                DVT_GR_RB_CTRL_WR_BLOCKING_SHIFT,
                                DVT_GR_RB_CTRL_WR_BLOCKING_SIGNED);

  _RB_CTRL_WR_INIT_IRQ=readPara(DVT_DVT_GR_RB_CTRL,
                                DVT_GR_RB_CTRL_WR_INIT_IRQ_MASK,
                                DVT_GR_RB_CTRL_WR_INIT_IRQ_SHIFT,
                                DVT_GR_RB_CTRL_WR_INIT_IRQ_SIGNED);

  _RB_ADDR=readPara(DVT_DVT_GR_RB_ADDR,
                    DVT_GR_RB_ADDR_BASE_MASK,
                    DVT_GR_RB_ADDR_BASE_SHIFT,
                    DVT_GR_RB_ADDR_BASE_SIGNED);

  _RB_STRIDE=readPara(DVT_DVT_GR_RB_STRIDE,
                      DVT_GR_RB_STRIDE_FRAME_MASK,
                      DVT_GR_RB_STRIDE_FRAME_SHIFT,
                      DVT_GR_RB_STRIDE_FRAME_SIGNED);

  _RB_LOC=readPara(DVT_DVT_GR_RB_LOC,
                   DVT_GR_RB_LOC_WR_MASK,
                   DVT_GR_RB_LOC_WR_SHIFT,
                   DVT_GR_RB_LOC_WR_SIGNED);

  _RB_SLOT=readPara(DVT_DVT_GR_RB_SLOT,
                    DVT_GR_RB_SLOT_TABLE_MASK,
                    DVT_GR_RB_SLOT_TABLE_SHIFT,
                    DVT_GR_RB_SLOT_TABLE_SIGNED);
}


void Driver::printPara(){
  cout<<setiosflags(ios::left)<<setw(32)<<"_VERSION: "<<"0x"<<hex<<_VERSION <<endl;
  cout<<setiosflags(ios::left)<<setw(32)<<"_COMPANY_DIGI: "<<"0x"<<hex<<_COMPANY_DIGI <<endl;
  cout<<setiosflags(ios::left)<<setw(32)<<"_COMPANY_VISI: "<<"0x"<<hex<<_COMPANY_VISI <<endl;
  cout<<setiosflags(ios::left)<<setw(32)<<"_COMPANY_ON: "<<"0x"<<hex<<_COMPANY_ON <<endl;
  cout<<setiosflags(ios::left)<<setw(32)<<"_COMPANY_HZCN: "<<"0x"<<hex<<_COMPANY_HZCN <<endl;
  cout<<setiosflags(ios::left)<<setw(32)<<"_IRQ_PORT_HIGH: "<<"0x"<<hex<<_IRQ_PORT_HIGH <<endl;
  cout<<setiosflags(ios::left)<<setw(32)<<"_IRQ_CMD_OP: "<<"0x"<<hex<<_IRQ_CMD_OP <<endl;
  cout<<setiosflags(ios::left)<<setw(32)<<"_IRQ_CMD_SIDE_INFO: "<<"0x"<<hex<<_IRQ_CMD_SIDE_INFO <<endl;
  cout<<setiosflags(ios::left)<<setw(32)<<"_IRQ_DATA_SIZE: "<<"0x"<<hex<<_IRQ_DATA_SIZE <<endl;
  cout<<setiosflags(ios::left)<<setw(32)<<"_IRQ_D0: "<<"0x"<<hex<<_IRQ_D0 <<endl;
  cout<<setiosflags(ios::left)<<setw(32)<<"_IRQ_D1: "<<"0x"<<hex<<_IRQ_D1 <<endl;
  cout<<setiosflags(ios::left)<<setw(32)<<"_IRQ_D2: "<<"0x"<<hex<<_IRQ_D2 <<endl;
  cout<<setiosflags(ios::left)<<setw(32)<<"_IRQ_D3: "<<"0x"<<hex<<_IRQ_D3 <<endl;
  cout<<setiosflags(ios::left)<<setw(32)<<"_MOS_CTRL_IIC_SL: "<<"0x"<<hex<<_MOS_CTRL_IIC_SL <<endl;
  cout<<setiosflags(ios::left)<<setw(32)<<"_MOS_CTRL_VS_HS_OEN: "<<"0x"<<hex<<_MOS_CTRL_VS_HS_OEN <<endl;
  cout<<setiosflags(ios::left)<<setw(32)<<"_MOS_CTRL_SLAVE_MODE: "<<"0x"<<hex<<_MOS_CTRL_SLAVE_MODE <<endl;
  cout<<setiosflags(ios::left)<<setw(32)<<"_MOS_FRAME_HS_INCK_CNT: "<<"0x"<<hex<<_MOS_FRAME_HS_INCK_CNT <<endl;
  cout<<setiosflags(ios::left)<<setw(32)<<"_MOS_FRAME_VS_LINE_CNT: "<<"0x"<<hex<<_MOS_FRAME_VS_LINE_CNT <<endl;
  cout<<setiosflags(ios::left)<<setw(32)<<"_RAW_LOC_H_OFFSET: "<<"0x"<<hex<<_RAW_LOC_H_OFFSET <<endl;
  cout<<setiosflags(ios::left)<<setw(32)<<"_RAW_LOC_H_SET_CNT: "<<"0x"<<hex<<_RAW_LOC_H_SET_CNT <<endl;
  cout<<setiosflags(ios::left)<<setw(32)<<"_LOC_OFFSET: "<<"0x"<<hex<<_LOC_OFFSET <<endl;
  cout<<setiosflags(ios::left)<<setw(32)<<"_LOC_CNT: "<<"0x"<<hex<<_LOC_CNT <<endl;
  cout<<setiosflags(ios::left)<<setw(32)<<"_AE_MANU_GAIN: "<<"0x"<<hex<<_AE_MANU_GAIN <<endl;
  cout<<setiosflags(ios::left)<<setw(32)<<"_AE_MANU_EXP: "<<"0x"<<hex<<_AE_MANU_EXP <<endl;
  cout<<setiosflags(ios::left)<<setw(32)<<"_RAW_STRIDE: "<<"0x"<<hex<<_RAW_STRIDE <<endl;
  cout<<setiosflags(ios::left)<<setw(32)<<"_RB_CTRL_WR_INIT_IRQ: "<<"0x"<<hex<<_RB_CTRL_WR_INIT_IRQ <<endl;
  cout<<setiosflags(ios::left)<<setw(32)<<"_RB_CTRL_WR_BLOCKING: "<<"0x"<<hex<<_RB_CTRL_WR_BLOCKING <<endl;
  cout<<setiosflags(ios::left)<<setw(32)<<"_RB_ADDR: "<<"0x"<<hex<<_RB_ADDR <<endl;
  cout<<setiosflags(ios::left)<<setw(32)<<"_RB_STRIDE: "<<"0x"<<hex<<_RB_STRIDE <<endl;
  cout<<setiosflags(ios::left)<<setw(32)<<"_RB_LOC: "<<"0x"<<hex<<_RB_LOC <<endl;
  cout<<setiosflags(ios::left)<<setw(32)<<"_RB_SLOT: "<<"0x"<<hex<<_RB_SLOT <<endl;

}
