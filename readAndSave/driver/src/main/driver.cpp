#include "driver.h"
#include <iomanip>
#include <stdio.h>
#include <sys/time.h>
#include "../../../lib/common/lib/channel_imagebuffer/channel_imagebuffer.h"

#ifdef SWITCH_LOG
#include "../../../lib_copy/syslogger/syslogger.h"
#endif

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

#ifdef SWITCH_LOG
  pdriver->_syslog.WriteLog(LEVEL_DEBUG,__FILE__,__LINE__,gettid(),
                            "=================Recv Info from displaydemo!===================");
#endif

  //  v_data._mode =0;
  cout<<"==================before==================="<<endl;
  pdriver->loadParaFromDev();
  pdriver->printPara();

  //1:rgb
  if(v_data._mode == 1){
#ifdef SWITCH_LOG
    pdriver->_syslog.WriteLog(LEVEL_DEBUG,__FILE__,__LINE__,gettid(),
                              "info of rgb image");
#endif

    unsigned int value = pdriver->_mmap_regs.rreg32(DVT_DVT_GR_CB_SLOT);
    cout<<"before loc:"<<hex<<v_data._loc<<dec<<endl;
    cout<<"before value:"<<hex<<value<<dec<<endl;
    cout<<"before 1 << v_data._loc:"<<hex<<1 << v_data._loc<<dec<<endl;
    cout<<"before !(1 << v_data._loc):"<<hex<<!(1 << v_data._loc)<<dec<<endl;

    value = value & (~(1 << v_data._loc));
    cout<<"after value:"<<hex<<value<<dec<<endl;
    pdriver->_mmap_regs.wreg32(DVT_DVT_GR_CB_SLOT, value);
    //    pdriver->_mmap_regs.wreg32(DVT_DVT_GR_CB_SLOT, 0);
  }
  else if(v_data._mode == 0){

#ifdef SWITCH_LOG
    pdriver->_syslog.WriteLog(LEVEL_DEBUG,__FILE__,__LINE__,gettid(),
                              "info of raw image");
#endif

    unsigned int value = pdriver->_mmap_regs.rreg32(DVT_DVT_GR_RB_SLOT);
    value = value & !(1 << v_data._loc);
    pdriver->_mmap_regs.wreg32(DVT_DVT_GR_RB_SLOT, value);
    //    pdriver->_mmap_regs.wreg32(DVT_DVT_GR_RB_SLOT, 0);
  }

  pdriver->_dvt_uio.unmask_interrupt();

  cout<<"==================after==================="<<endl;
  pdriver->loadParaFromDev();
  pdriver->printPara();


  cout<<"[end ]"<<__func__<<endl;


#ifdef SWITCH_LOG
  pdriver->_syslog.WriteLog(LEVEL_DEBUG,__FILE__,__LINE__,gettid(),
                            "=================End Recv Info from displaydemo!===================");
  fflush(stdout);
#endif
}

Driver::Driver(const string & v_fdev,unsigned int v_rawmode,unsigned v_rgbmode):
  _mode_raw(v_rawmode),
  _mode_rgb(v_rgbmode),
  _devfile(v_fdev),
  _dvt_uio(_devfile.c_str()),
  _mmap_regs(_dvt_uio,OP_WR,MAP_REG_SIZE),
  _mmap_pb(_dvt_uio,OP_RD,MAP_PB_SIZE),
  _ch(NULL)
{
#ifdef DEBUG_DRIVER
  initTime();
#endif

#ifdef SWITCH_LOG
  _syslog.InitLogger("Driver.log",LEVEL_DEBUG);
#endif

  _ch=new ImageBufferChannel(MsgChannel_Mode::producer,
                             ImageBufferChannel_TYPE_Display,
                             getMsg,this);
  if(_ch == nullptr){
    cerr<<"_ch is NULL"<<endl;
  }

  loadParaFromDev();
  printPara();
  //  //设置设备参数
  //  //mask取或,
  _mmap_regs.wreg32_f(DVT_DVT_GR_RB_CTRL,DVT_GR_RB_CTRL_WR_BLOCKING_MASK,DVT_GR_RB_CTRL_WR_BLOCKING_SHIFT,0);
  _mmap_regs.wreg32_f(DVT_DVT_GR_RB_CTRL,DVT_GR_RB_CTRL_WR_INIT_IRQ_MASK,DVT_GR_RB_CTRL_WR_INIT_IRQ_SHIFT,1);
  _mmap_regs.wreg32_f(DVT_DVT_GR_CB_CTRL,DVT_GR_CB_CTRL_WR_BLOCKING_MASK,DVT_GR_CB_CTRL_WR_BLOCKING_SHIFT,1);
  _mmap_regs.wreg32_f(DVT_DVT_GR_CB_CTRL,DVT_GR_CB_CTRL_WR_INIT_IRQ_MASK,DVT_GR_CB_CTRL_WR_INIT_IRQ_SHIFT,1);
  //由于rgb图片的实现依赖于raw数据，raw数据的阻塞会导致rgb图片重复显示




  _dvt_uio.unmask_interrupt();
  //  getchar();
  loadParaFromDev();
  printPara();

  pthread_t pid;
  int flag=pthread_create(&pid,nullptr,run,this);
  if(flag != 0){
    return;
  }

#ifdef SWITCH_LOG
  _syslog.WriteLog(LEVEL_DEBUG,__FILE__,__LINE__,gettid(),
                   "=================End to init!===================");
#endif
}

void *run(void* v_pdata){



  Driver* pdriver=(Driver* )v_pdata;
#ifdef SWITCH_LOG
  pdriver->_syslog.WriteLog(LEVEL_DEBUG,__FILE__,__LINE__,gettid(),
                            "=================Start thread to listen irq==================!");
#endif

  int wait_irq_result;
  uint32_t irq_count;
  uint32_t dvt_op, dvt_slot_reg, dvt_slot_loc;
  unsigned int value;

  while(1) {
    pdriver->_dvt_uio.unmask_interrupt();

    wait_irq_result = pdriver->_dvt_uio.wait_interrupt(1000);

    printf("wait_irq_result:%d\n",wait_irq_result );
    if (wait_irq_result == 0) {
#ifdef SWITCH_LOG
      pdriver->_syslog.WriteLog(LEVEL_DEBUG,__FILE__,__LINE__,gettid(),
                                "Wait IRQ Timeout!");
#endif

      printf(" Wait IRQ Timeout\n");
    } else if (wait_irq_result < 0) {
      printf(" Wait IRQ Error\n");
#ifdef SWITCH_LOG
      pdriver->_syslog.WriteLog(LEVEL_DEBUG,__FILE__,__LINE__,gettid(),
                                "Wait IRQ Error!");
#endif
    } else {
#ifdef DEBUG_DRIVER
      outputTimeCost();
#endif
#ifdef SWITCH_LOG
      pdriver->_syslog.WriteLog(LEVEL_DEBUG,__FILE__,__LINE__,gettid(),
                                "========Obtain IRQ (%d)==========",pdriver->_dvt_uio.get_irq_cnt());
#endif

      printf("%s: Wait IRQ get Irq_Count = %d\n", "", pdriver->_dvt_uio.get_irq_cnt());

      pdriver->_mmap_regs.wreg32(DVT_DVT_GR_IRQ_PORT, 0x00000000);
      value = pdriver->_mmap_regs.rreg32(DVT_DVT_GR_IRQ_CMD);
      printf("%s: Read DVT_DVT_GR_IRQ_CMD = 0x%8x\n", "", value);
      dvt_op = value & DVT_GR_IRQ_CMD_OP_MASK;
      dvt_slot_reg = (value & DVT_GR_IRQ_CMD_SIDE_INFO_MASK) >> 16;
      dvt_slot_loc = (value & 0x00000300) >> 8;

      printf("%s: dvt_op = 0x%2x, dvt_slot_reg = 0x%4x, dvt_slot_loc = 0x%2x, \n"
             , "", dvt_op, dvt_slot_reg, dvt_slot_loc);
#ifdef SWITCH_LOG
      pdriver->_syslog.WriteLog(LEVEL_DEBUG,__FILE__,__LINE__,gettid(),
                                "IRQ op:%u slot_reg:%u slot_loc:%u",dvt_op,dvt_slot_reg,dvt_slot_loc);
#endif
      unsigned int tmpaddr;
      int imagemode;

      if(dvt_op == 0x40){
        continue;
        imagemode=0;
        tmpaddr=pdriver->readPara(DVT_DVT_GR_IRQ_D1,
                                  DVT_GR_IRQ_D1_SRC_ADDR_L_MASK,
                                  DVT_GR_IRQ_D1_SRC_ADDR_L_SHIFT,
                                  DVT_GR_IRQ_D1_SRC_ADDR_L_SIGNED);
      }
      else if(dvt_op == 0x41){
        imagemode=1;
        tmpaddr=pdriver->readPara(DVT_DVT_GR_CB_ADDR,
                                  DVT_GR_CB_ADDR_BASE_MASK,
                                  DVT_GR_CB_ADDR_BASE_SHIFT,
                                  DVT_GR_CB_ADDR_BASE_SIGNED);
        tmpaddr =tmpaddr+ (pdriver->_RGB_STRIDE<<12)*dvt_slot_loc;

      }
      else{
        continue;
      }

      //将数据添加到队列中
      ImageBufferInArm tmp(tmpaddr<<8,4096,4096,imagemode,
                           dvt_slot_loc,pdriver->_dvt_uio.get_irq_cnt(),0);
      int flag= pdriver->_ch->addNewImageBufferInArm(
            tmp);

      if(flag==0){
#ifdef SWITCH_LOG
        pdriver->_syslog.WriteLog(LEVEL_DEBUG,__FILE__,__LINE__,gettid(),
                                  "Succeed to send to displaydemo:%s",ImageBufferInArm::getString(tmp).c_str());
#endif

      }
      else{
#ifdef SWITCH_LOG
        pdriver->_syslog.WriteLog(LEVEL_DEBUG,__FILE__,__LINE__,gettid(),
                                  "Fail to send to displaydemo:%s",ImageBufferInArm::getString(tmp).c_str());
#endif
      }

#ifdef SWITCH_LOG
      pdriver->_syslog.WriteLog(LEVEL_DEBUG,__FILE__,__LINE__,gettid(),
                                "=========End to treat IRQ=========");
#endif
    }
  }

#ifdef SWITCH_LOG
  pdriver->_syslog.WriteLog(LEVEL_DEBUG,__FILE__,__LINE__,gettid(),
                            "=================End thread to listen irq==================!");
#endif

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

  _RGB_STRIDE=readPara(DVT_DVT_GR_RGB_STRIDE,
                       DVT_GR_RGB_STRIDE_GENERAL_MASK,
                       DVT_GR_RGB_STRIDE_GENERAL_SHIFT,
                       DVT_GR_RGB_STRIDE_GENERAL_SIGNED);
  _CB_CTRL_WR_BLOCKING=readPara(DVT_DVT_GR_CB_CTRL,
                                DVT_GR_CB_CTRL_WR_BLOCKING_MASK,
                                DVT_GR_CB_CTRL_WR_BLOCKING_SHIFT,
                                DVT_GR_CB_CTRL_WR_BLOCKING_SIGNED);
  _CB_CTRL_WR_INIT_IRQ=readPara(DVT_DVT_GR_CB_CTRL,
                                DVT_GR_CB_CTRL_WR_INIT_IRQ_MASK,
                                DVT_GR_CB_CTRL_WR_INIT_IRQ_SHIFT,
                                DVT_GR_CB_CTRL_WR_INIT_IRQ_SIGNED);
  _CB_ADDR=readPara(DVT_DVT_GR_CB_ADDR,
                    DVT_GR_CB_ADDR_BASE_MASK,
                    DVT_GR_CB_ADDR_BASE_SHIFT,
                    DVT_GR_CB_ADDR_BASE_SIGNED);
  _CB_STRIDE=readPara(DVT_DVT_GR_CB_STRIDE,
                      DVT_GR_CB_STRIDE_FRAME_MASK,
                      DVT_GR_CB_STRIDE_FRAME_SHIFT,
                      DVT_GR_CB_STRIDE_FRAME_SIGNED);
  _CB_LOC=readPara(DVT_DVT_GR_CB_LOC,
                   DVT_GR_CB_LOC_WR_MASK,
                   DVT_GR_CB_LOC_WR_SHIFT,
                   DVT_GR_CB_LOC_WR_SIGNED);
  _CB_SLOT=readPara(DVT_DVT_GR_CB_SLOT,
                    DVT_GR_CB_SLOT_TABLE_MASK,
                    DVT_GR_CB_SLOT_TABLE_SHIFT,
                    DVT_GR_CB_SLOT_TABLE_SIGNED);

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
  //add rgb
  cout<<setiosflags(ios::left)<<setw(32)<<"_RGB_STRIDE: "<<"0x"<<hex<<_RGB_STRIDE <<endl;
  cout<<setiosflags(ios::left)<<setw(32)<<"_CB_CTRL_WR_BLOCKING: "<<"0x"<<hex<<_CB_CTRL_WR_BLOCKING <<endl;
  cout<<setiosflags(ios::left)<<setw(32)<<"_CB_CTRL_WR_INIT_IRQ: "<<"0x"<<hex<<_CB_CTRL_WR_INIT_IRQ <<endl;
  cout<<setiosflags(ios::left)<<setw(32)<<"_CB_ADDR: "<<"0x"<<hex<<_CB_ADDR <<endl;
  cout<<setiosflags(ios::left)<<setw(32)<<"_CB_STRIDE: "<<"0x"<<hex<<_CB_STRIDE <<endl;
  cout<<setiosflags(ios::left)<<setw(32)<<"_CB_LOC: "<<"0x"<<hex<<_CB_LOC <<endl;
  cout<<setiosflags(ios::left)<<setw(32)<<"_CB_SLOT: "<<"0x"<<hex<<_CB_SLOT <<endl;

}
