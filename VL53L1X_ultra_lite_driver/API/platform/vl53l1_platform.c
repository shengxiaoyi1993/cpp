



/* 
* This file is part of VL53L1 Platform 
* 
* Copyright (c) 2016, STMicroelectronics - All Rights Reserved 
* 
* License terms: BSD 3-clause "New" or "Revised" License. 
* 
* Redistribution and use in source and binary forms, with or without 
* modification, are permitted provided that the following conditions are met: 
* 
* 1. Redistributions of source code must retain the above copyright notice, this 
* list of conditions and the following disclaimer. 
* 
* 2. Redistributions in binary form must reproduce the above copyright notice, 
* this list of conditions and the following disclaimer in the documentation 
* and/or other materials provided with the distribution. 
* 
* 3. Neither the name of the copyright holder nor the names of its contributors 
* may be used to endorse or promote products derived from this software 
* without specific prior written permission. 
* 
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE 
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
* 
*/

#include "vl53l1_platform.h"
#include <string.h>
#include <time.h>
#include <math.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

int g_fd_dev=0;

int initDevFD(int fd){
  g_fd_dev=fd;
  return 0;
}


//int8_t VL53L1_WriteMulti( uint16_t dev, uint16_t index, uint8_t *pdata, uint32_t count) {
//  if (g_fd_dev <= 0) {
//    return -1;
//  }

//  struct i2c_rdwr_ioctl_data msg_rdwr;
//  struct i2c_msg i2cmsg;
//  int i;
//  char *_buf=(uint8_t*)malloc((count+1)*sizeof (uint8_t));

//  _buf[0]=index;
//  for(i=0;i<count;i++)
//  {
//    _buf[1+i]=pdata[i];
////    printf("----_writedata:%x------\n",_buf[1+i]);
//  }

//  msg_rdwr.msgs = &i2cmsg;
//  msg_rdwr.nmsgs = 1;

//  i2cmsg.addr  = dev;
//  i2cmsg.flags = 0;
//  i2cmsg.len   = 1+count;
//  i2cmsg.buf   = _buf;

//  if((i=ioctl(g_fd_dev,I2C_RDWR,&msg_rdwr))<0){
//    printf(__func__);
//    printf(" fail !\n");
//    perror("ioctl()");
//    fprintf(stderr,"ioctl returned %d\n",i);
//    free(_buf);
//    _buf=NULL;
//    return -1;
//  }
//  else{
////    printf(__func__);
////    printf("\nsucceed !\n");
//  }


//	return 0; // to be implemented
//}

//int8_t VL53L1_ReadMulti(uint16_t dev, uint16_t index, uint8_t *pdata, uint32_t count){
//  if (g_fd_dev <= 0) {
//    return -1;
//  }
//  struct i2c_rdwr_ioctl_data msg_rdwr;
//  struct i2c_msg i2cmsg;
//  int i;

//  if(VL53L1_WriteMulti(dev,index,NULL,0)<0)
//  {
//    return -1;
//  }

//  msg_rdwr.msgs = &i2cmsg;
//  msg_rdwr.nmsgs = 1;

//  i2cmsg.addr  = dev;
//  i2cmsg.flags = 1;
//  i2cmsg.len   = count;
//  i2cmsg.buf   = pdata;


//  if((i=ioctl(g_fd_dev,I2C_RDWR,&msg_rdwr))<0){

//    printf(__func__);
//    printf(" fail !\n");

//    perror("ioctl()");
//    fprintf(stderr,"ioctl returned %d\n",i);
//    return -1;
//  }
//  else{
////    printf(__func__);
////    printf("\nsucceed !\n");
//  }


//	return 0; // to be implemented
//}

//int8_t VL53L1_WrByte(uint16_t dev, uint16_t index, uint8_t data) {

//  return VL53L1_WriteMulti(dev,index,&data,1);
//}

//int8_t VL53L1_WrWord(uint16_t dev, uint16_t index, uint16_t data) {
//  return VL53L1_WriteMulti(dev,index,&data,2);
////	return 0; // to be implemented
//}

//int8_t VL53L1_WrDWord(uint16_t dev, uint16_t index, uint32_t data) {
//  return VL53L1_WriteMulti(dev,index,&data,4);

////	return 0; // to be implemented
//}

//int8_t VL53L1_RdByte(uint16_t dev, uint16_t index, uint8_t *val) {
//  return VL53L1_WriteMulti(dev,index,val,1);
//}

//int8_t VL53L1_RdWord(uint16_t dev, uint16_t index, uint16_t *data) {
//  return VL53L1_WriteMulti(dev,index,data,2);

////	return 0; // to be implemented
//}

//int8_t VL53L1_RdDWord(uint16_t dev, uint16_t index, uint32_t *data) {
//  return VL53L1_WriteMulti(dev,index,data,4);

////	return 0; // to be implemented
//}

//int8_t VL53L1_WaitMs(uint16_t dev, int32_t wait_ms){

//	return 0; // to be implemented
//}


#define VL53L1_ERROR_NONE 0
#define VL53L1_ERROR_CONTROL_INTERFACE 1
#define VL53L1_ERROR_INVALID_PARAMS 2


uint8_t _I2CBuffer[256];

int _I2CWrite(uint16_t dev, uint8_t *pdata, uint32_t count) {
  int status=VL53L1_ERROR_NONE;

  //    int i2c_time_out = I2C_TIME_OUT_BASE+ count* I2C_TIME_OUT_BYTE;

  //    status = HAL_I2C_Master_Transmit(&XNUCLEO53L1A1_hi2c, Dev, pdata, count, i2c_time_out);
  //    if (status) {
  //        //VL6180x_ErrLog("I2C error 0x%x %d len", dev->I2cAddr, len);
  //        //XNUCLEO6180XA1_I2C1_Init(&hi2c1);
  //    }

  if (g_fd_dev <= 0) {
    return -1;
  }

  struct i2c_rdwr_ioctl_data msg_rdwr;
  struct i2c_msg i2cmsg;
  int i;

  //      char *_buf=(uint8_t*)malloc((count+1)*sizeof (uint8_t));

  //      _buf[0]=index;
  //      for(i=0;i<count;i++)
  //      {
  //        _buf[1+i]=pdata[i];
  //    //    printf("----_writedata:%x------\n",_buf[1+i]);
  //      }

  msg_rdwr.msgs = &i2cmsg;
  msg_rdwr.nmsgs = 1;

  i2cmsg.addr  = dev;
  i2cmsg.flags = 0;
  i2cmsg.len   = count;
  i2cmsg.buf   = pdata;

  printf("fd:%d\n",g_fd_dev);
  printf("dev:%d\n",dev);


  if((i=ioctl(g_fd_dev,I2C_RDWR,&msg_rdwr))<0){
    printf(__func__);
    printf(" fail !\n");
    perror("ioctl()");
    fprintf(stderr,"ioctl returned %d\n",i);
    //        free(_buf);
    //        _buf=NULL;
    return -1;
  }
  else{
//    for(i=0;i<count;i++)
//    {
//      //                pdata[1+i]=pdata[i];
//      printf("----_writedata:%x------\n",pdata[i]);
//    }
//    printf("\n");


  }

  return status;
}

int _I2CRead(uint16_t dev, uint8_t *pdata, uint32_t count) {
  printf("{\n");
  int status=VL53L1_ERROR_NONE;

  if (g_fd_dev <= 0) {
    printf("e}\n");

    return -1;
  }
  struct i2c_rdwr_ioctl_data msg_rdwr;
  struct i2c_msg i2cmsg;
  int i;

  //      if(VL53L1_WriteMulti(dev,index,NULL,0)<0)
  //      {
  //        return -1;
  //      }

  msg_rdwr.msgs = &i2cmsg;
  msg_rdwr.nmsgs = 1;

  i2cmsg.addr  = dev;
  i2cmsg.flags = 1;
  i2cmsg.len   = count;
  i2cmsg.buf   = pdata;


  if((i=ioctl(g_fd_dev,I2C_RDWR,&msg_rdwr))<0){

    printf(__func__);
    printf(" fail !\n");

    perror("ioctl()");
    fprintf(stderr,"ioctl returned %d\n",i);
    printf("e}\n");

    return -1;
  }
  else{
//    for(i=0;i<count;i++)
//    {
//      //                pdata[1+i]=pdata[i];
//      printf("----_readdata:%x------\n",pdata[i]);
//    }
//    printf("\n");

    //    printf(__func__);
    //    printf("\nsucceed !\n");
  }


  //    int i2c_time_out = I2C_TIME_OUT_BASE+ count* I2C_TIME_OUT_BYTE;

  //    status = HAL_I2C_Master_Receive(&XNUCLEO53L1A1_hi2c, Dev|1, pdata, count, i2c_time_out);
  //    if (status) {
  //        //VL6180x_ErrLog("I2C error 0x%x %d len", dev->I2cAddr, len);
  //        //XNUCLEO6180XA1_I2C1_Init(&hi2c1);
  //    }
  printf("}\n");

  return status;
}

int8_t VL53L1_WriteMulti(uint16_t Dev, uint16_t index, uint8_t *pdata, uint32_t count) {
  int status_int;
  int8_t Status = VL53L1_ERROR_NONE;
  if (count > sizeof(_I2CBuffer) - 1) {
    return VL53L1_ERROR_INVALID_PARAMS;
  }
  _I2CBuffer[0] = index>>8;
  _I2CBuffer[1] = index&0xFF;
  memcpy(&_I2CBuffer[2], pdata, count);
  //VL53L1_GetI2cBus();
  status_int = _I2CWrite(Dev, _I2CBuffer, count + 2);
  if (status_int != 0) {
    Status = VL53L1_ERROR_CONTROL_INTERFACE;
  }
  //VL53L1_PutI2cBus();
  return Status;
}

// the ranging_sensor_comms.dll will take care of the page selection
int8_t VL53L1_ReadMulti(uint16_t Dev, uint16_t index, uint8_t *pdata, uint32_t count) {
  int8_t Status = VL53L1_ERROR_NONE;
  int32_t status_int;

  _I2CBuffer[0] = index>>8;
  _I2CBuffer[1] = index&0xFF;
  //VL53L1_GetI2cBus();
  status_int = _I2CWrite(Dev, _I2CBuffer, 2);
  if (status_int != 0) {
    Status = VL53L1_ERROR_CONTROL_INTERFACE;
    goto done;
  }
  status_int = _I2CRead(Dev, pdata, count);
  if (status_int != 0) {
    Status = VL53L1_ERROR_CONTROL_INTERFACE;
  }
done:
  //VL53L1_PutI2cBus();
  return Status;
}

int8_t VL53L1_WrByte(uint16_t Dev, uint16_t index, uint8_t data) {
  int8_t Status = VL53L1_ERROR_NONE;
  int32_t status_int;

  _I2CBuffer[0] = index>>8;
  _I2CBuffer[1] = index&0xFF;
  _I2CBuffer[2] = data;

  //VL53L1_GetI2cBus();
  status_int = _I2CWrite(Dev, _I2CBuffer, 3);
  if (status_int != 0) {
    Status = VL53L1_ERROR_CONTROL_INTERFACE;
  }
  //VL53L1_PutI2cBus();
  return Status;
}

int8_t VL53L1_WrWord(uint16_t Dev, uint16_t index, uint16_t data) {
  int8_t Status = VL53L1_ERROR_NONE;
  int32_t status_int;

  _I2CBuffer[0] = index>>8;
  _I2CBuffer[1] = index&0xFF;
  _I2CBuffer[2] = data >> 8;
  _I2CBuffer[3] = data & 0x00FF;

  //VL53L1_GetI2cBus();
  status_int = _I2CWrite(Dev, _I2CBuffer, 4);
  if (status_int != 0) {
    Status = VL53L1_ERROR_CONTROL_INTERFACE;
  }
  //VL53L1_PutI2cBus();
  return Status;
}

int8_t VL53L1_WrDWord(uint16_t Dev, uint16_t index, uint32_t data) {
  int8_t Status = VL53L1_ERROR_NONE;
  int32_t status_int;
  _I2CBuffer[0] = index>>8;
  _I2CBuffer[1] = index&0xFF;
  _I2CBuffer[2] = (data >> 24) & 0xFF;
  _I2CBuffer[3] = (data >> 16) & 0xFF;
  _I2CBuffer[4] = (data >> 8)  & 0xFF;
  _I2CBuffer[5] = (data >> 0 ) & 0xFF;
  //VL53L1_GetI2cBus();
  status_int = _I2CWrite(Dev, _I2CBuffer, 6);
  if (status_int != 0) {
    Status = VL53L1_ERROR_CONTROL_INTERFACE;
  }
  //VL53L1_PutI2cBus();
  return Status;
}

int8_t VL53L1_UpdateByte(uint16_t Dev, uint16_t index, uint8_t AndData, uint8_t OrData) {
  int8_t Status = VL53L1_ERROR_NONE;
  uint8_t data;

  Status = VL53L1_RdByte(Dev, index, &data);
  if (Status) {
    goto done;
  }
  data = (data & AndData) | OrData;
  Status = VL53L1_WrByte(Dev, index, data);
done:
  return Status;
}

int8_t VL53L1_RdByte(uint16_t Dev, uint16_t index, uint8_t *data) {
  int8_t Status = VL53L1_ERROR_NONE;
  int32_t status_int;

  _I2CBuffer[0] = index>>8;
  _I2CBuffer[1] = index&0xFF;
  //VL53L1_GetI2cBus();
  status_int = _I2CWrite(Dev, _I2CBuffer, 2);
  if( status_int ){
    Status = VL53L1_ERROR_CONTROL_INTERFACE;
    goto done;
  }
  status_int = _I2CRead(Dev, data, 1);
  if (status_int != 0) {
    Status = VL53L1_ERROR_CONTROL_INTERFACE;
  }
done:
  //VL53L1_PutI2cBus();
  return Status;
}

int8_t VL53L1_RdWord(uint16_t Dev, uint16_t index, uint16_t *data) {
  int8_t Status = VL53L1_ERROR_NONE;
  int32_t status_int;

  _I2CBuffer[0] = index>>8;
  _I2CBuffer[1] = index&0xFF;
  //VL53L1_GetI2cBus();
  status_int = _I2CWrite(Dev, _I2CBuffer, 2);

  if( status_int ){
    printf("error:%d\n",__LINE__);

    Status = VL53L1_ERROR_CONTROL_INTERFACE;

    goto done;
  }
  status_int = _I2CRead(Dev, _I2CBuffer, 2);
  if (status_int != 0) {
    printf("error:%d\n",__LINE__);
    Status = VL53L1_ERROR_CONTROL_INTERFACE;
    goto done;
  }

  *data = ((uint16_t)_I2CBuffer[0]<<8) + (uint16_t)_I2CBuffer[1];
done:
  //VL53L1_PutI2cBus();
  return Status;
}

int8_t VL53L1_RdDWord(uint16_t Dev, uint16_t index, uint32_t *data) {
  int8_t Status = VL53L1_ERROR_NONE;
  int32_t status_int;

  _I2CBuffer[0] = index>>8;
  _I2CBuffer[1] = index&0xFF;
  //VL53L1_GetI2cBus();
  status_int = _I2CWrite(Dev, _I2CBuffer, 2);
  if (status_int != 0) {
    Status = VL53L1_ERROR_CONTROL_INTERFACE;
    goto done;
  }
  status_int = _I2CRead(Dev, _I2CBuffer, 4);
  if (status_int != 0) {
    Status = VL53L1_ERROR_CONTROL_INTERFACE;
    goto done;
  }

  *data = ((uint32_t)_I2CBuffer[0]<<24) + ((uint32_t)_I2CBuffer[1]<<16) + ((uint32_t)_I2CBuffer[2]<<8) + (uint32_t)_I2CBuffer[3];

done:
  //VL53L1_PutI2cBus();
  return Status;
}

