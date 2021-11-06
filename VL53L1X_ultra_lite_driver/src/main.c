/*
* Copyright (c) 2021-04-08, DigitalVersion Inc. - All Rights Reserved
*
********************************************************************************
*
* @Author: shengxiaoyi2014@icloud.com (XiaoYi Sheng)
*
********************************************************************************
*
* @Usage:
*
********************************************************************************
*
*/

//#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "../API/platform/vl53l1_types.h"
#include "../API/platform/vl53l1_platform.h"
#include "../API/core/VL53L1X_api.h"
#include "../API/core/VL53L1X_calibration.h"

void printVL53L1X_Version_t(VL53L1X_Version_t v_ver){
  printf("major:%d\n",v_ver.major);
  printf("minor:%d\n",v_ver.minor);
  printf("build:%d\n",v_ver.build);
  printf("revision:%d\n",v_ver.revision);
}

#define NEW_ADDR 0X66

#define OLD_ADDR 0X52


int work_loop(){
  //  uint16_t dev;
  uint16_t	dev=OLD_ADDR>>1;


  int fd;

  if ((fd = open("/dev/i2c-0",O_RDWR))< 0) {
    /* 错误处理 */

    exit(1);

  }
  //     dev=fd;
  initDevFD(fd);

  uint8_t byteData=0;
  uint8_t sensorState=0;
  uint16_t wordData;
//  uint8_t ToFSensor = 1; // 0=Left, 1=Center(default), 2=Right
  uint16_t Distance;
  uint16_t SignalRate;
  uint16_t AmbientRate;
  uint16_t SpadNum;
  uint8_t RangeStatus;
  uint8_t dataReady;
  int status=0;


  /* Those basic I2C read functions can be used to check your own I2C functions */
  status = VL53L1_RdByte(dev, 0x010F, &byteData);
  printf("VL53L1X Model_ID: %X\n", byteData);
  status = VL53L1_RdByte(dev, 0x0110, &byteData);
  printf("VL53L1X Module_Type: %X\n", byteData);
  status = VL53L1_RdWord(dev, 0x010F, &wordData);
  printf("VL53L1X: %X\n", wordData);

  while(sensorState == 0){
    status = VL53L1X_BootState(dev, &sensorState);
    //    HAL_Delay(2);
  }
  printf("Chip booted\n");

  /* This function must to be called to initialize the sensor with the default setting  */
  status = VL53L1X_SensorInit(dev);
  /* Optional functions to be used to change the main ranging parameters according the application requirements to get the best ranging performances */
  status = VL53L1X_SetROI(dev,16,16);  										//�趨ROI������С
  status = VL53L1X_SetROICenter(dev,199);									//ROI��������
  status = VL53L1X_SetDistanceMode(dev, 2); /* 1=short, 2=long */
  status = VL53L1X_SetTimingBudgetInMs(dev, 100); /* in ms possible values [20, 50, 100, 200, 500] */
  status = VL53L1X_SetInterMeasurementInMs(dev, 100); /* in ms, IM must be > = TB */
  //<>测距传感器矫正值，尚未确定
  status = VL53L1X_SetOffset(dev,0);
  //<>测距传感器矫正值，尚未确定
  status = VL53L1X_SetXtalk(dev,0);
  //  status = VL53L1X_SetOffset(dev,20); /* offset compensation in mm */
  //  status = VL53L1X_SetROI(dev, 16, 16); /* minimum ROI 4,4 */
  //	status = VL53L1X_CalibrateOffset(dev, 140, &offset); /* may take few second to perform the offset cal*/
  //	status = VL53L1X_CalibrateXtalk(dev, 1000, &xtalk); /* may take few second to perform the xtalk cal */
  printf("VL53L1X Ultra Lite Driver Example running ...\n");
  status = VL53L1X_StartRanging(dev);   /* This function has to be called to enable the ranging */


  while(1){ /* read and display data */
    while (dataReady == 0){
      status = VL53L1X_CheckForDataReady(dev, &dataReady);
      sleep(1);
      //      HAL_Delay(2);
    }
    dataReady = 0;
    status = VL53L1X_GetRangeStatus(dev, &RangeStatus);
    status = VL53L1X_GetDistance(dev, &Distance);
    status = VL53L1X_GetSignalRate(dev, &SignalRate);
    status = VL53L1X_GetAmbientRate(dev, &AmbientRate);
    status = VL53L1X_GetSpadNb(dev, &SpadNum);
    status = VL53L1X_ClearInterrupt(dev); /* clear interrupt has to be called to enable next interrupt*/
    printf("%u, %u, %u, %u, %u\n", RangeStatus, Distance, SignalRate, AmbientRate,SpadNum);
  }

}



int test_loop(){

  //  std::cout<<"start ..."<<std::endl;

  //  uint16_t dev;
  uint16_t	dev=OLD_ADDR>>1;


  int fd;

  if ((fd = open("/dev/i2c-0",O_RDWR))< 0) {
    /* 错误处理 */

    exit(1);

  }
  //     dev=fd;
  initDevFD(fd);


  VL53L1X_ERROR err_status;
  uint8_t state=1;
  uint8_t TempDM;

  //  // 验证程序
  //  //
  //  printf(">start \r\n");
  //    VL53L1X_SetI2CAddress(dev,NEW_ADDR);
  //    dev=NEW_ADDR>>1;


  err_status = VL53L1_RdByte(dev,PHASECAL_CONFIG__TIMEOUT_MACROP, &TempDM);
  if (err_status != 0) {
    printf("fail to VL53L1_RdByte \n");
  }
  printf("-[init] VL53L1_RdByte:%d\n",TempDM);

  err_status = VL53L1_WrByte(dev, PHASECAL_CONFIG__TIMEOUT_MACROP, 0x0A);
  if (err_status != 0) {
    printf("fail to VL53L1_WrByte \n");
  }
  printf("-[w0] VL53L1_WrByte:%d\n",0x0A);


  err_status = VL53L1_RdByte(dev,PHASECAL_CONFIG__TIMEOUT_MACROP, &TempDM);
  if (err_status != 0) {
    printf("fail to VL53L1_RdByte \n");
  }
  printf("-[r0] VL53L1_RdByte:%d\n",TempDM);


  err_status = VL53L1X_SetTimingBudgetInMs(dev, 100); /* in ms possible values [20, 50, 100, 200, 500] */
  if (err_status != 0) {
    printf("fail to VL53L1X_SetTimingBudgetInMs \n");
  }
  printf("-[tb] VL53L1X_SetTimingBudgetInMs :%d\n",100);

  err_status = VL53L1_RdByte(dev,PHASECAL_CONFIG__TIMEOUT_MACROP, &TempDM);
  if (err_status != 0) {
    printf("fail to VL53L1_RdByte \n");
  }
  printf("-[r1] VL53L1_RdByte:%d\n",TempDM);





  //  printf(">end \r\n");



  //>验证单个寄存器的读写正常

  // 获取传感器信息
  VL53L1X_Version_t version_sensor={0};
  printf("before get\n");
  printVL53L1X_Version_t(version_sensor);
  VL53L1X_GetSWVersion(&version_sensor);
  printf("after get\n");
  printVL53L1X_Version_t(version_sensor);

  // 获取传感器id
  uint16_t sensorid=0;
  VL53L1X_GetSensorId(dev,&sensorid);
  printf("sensor id:%d\n",sensorid);

  err_status = VL53L1X_SetDistanceMode(dev, 2); /* 1=short, 2=long */

  // VL53L1X_GetTimingBudgetInMs
  err_status = VL53L1X_SetTimingBudgetInMs(dev, 100); /* in ms possible values [20, 50, 100, 200, 500] */
  if (err_status != 0) {
    printf("fail to VL53L1X_SetTimingBudgetInMs \n");
  }
  printf("VL53L1X_SetTimingBudgetInMs :%d\n",100);

  err_status = VL53L1_RdByte(dev,PHASECAL_CONFIG__TIMEOUT_MACROP, &TempDM);
  if (err_status != 0) {
    printf("fail to VL53L1_RdByte \n");
  }
  printf("VL53L1_RdByte:%d\n",TempDM);

  uint16_t TB=0;
  err_status = VL53L1X_GetTimingBudgetInMs(dev, &TB);
  if (err_status != 0) {
    printf("fail to VL53L1X_GetTimingBudgetInMs \n");
  }
  printf("VL53L1X_GetTimingBudgetInMs :%d\n",TB);

  ///>验证TimingBudget的读写正常

  err_status = VL53L1X_SetInterMeasurementInMs(dev, 100); /* in ms, IM must be > = TB */

  // jj
  //  uint8_t Polarity;
  //  VL53L1X_SetInterruptPolarity(,Polarity);
  //  StartRanging

  ///<>读写出错出错
  uint16_t dm=2;

  err_status =VL53L1X_GetDistanceMode(dev,&dm);
  if (err_status != 0) {
    printf("fail to VL53L1X_GetDistanceMode \n");
  }
  printf("VL53L1X_GetDistanceMode 1:%d\n",dm);

  err_status = VL53L1_RdByte(dev,PHASECAL_CONFIG__TIMEOUT_MACROP, &TempDM);
  if (err_status != 0) {
    printf("fail to VL53L1_RdByte \n");
  }
  printf("VL53L1_RdByte:%d\n",TempDM);

  err_status = VL53L1X_SetDistanceMode(dev,dm);
  if (err_status != 0) {
    printf("fail to VL53L1X_SetDistanceMode \n");
  }
  printf("VL53L1X_SetDistanceMode 2:%d\n",dm);

  err_status = VL53L1_RdByte(dev,PHASECAL_CONFIG__TIMEOUT_MACROP, &TempDM);
  if (err_status != 0) {
    printf("fail to VL53L1_RdByte \n");
  }
  printf("VL53L1_RdByte:%d\n",TempDM);

  err_status = VL53L1X_GetDistanceMode(dev,&dm);
  if (err_status != 0) {
    printf("fail to VL53L1X_GetDistanceMode \n");
  }
  printf("VL53L1X_GetDistanceMode 3:%d\n",dm);

  err_status = VL53L1_RdByte(dev,PHASECAL_CONFIG__TIMEOUT_MACROP, &TempDM);
  if (err_status != 0) {
    printf("fail to VL53L1_RdByte \n");
  }
  printf("VL53L1_RdByte:%d\n",TempDM);




  while(state == 0){
    printf("VL53L1X_BootState again\n");
    err_status = VL53L1X_BootState(dev, &state);
    if (err_status != 0) {
      printf("fail to VL53L1X_BootState \n");
    }
    sleep(2);
  }

  printf("after VL53L1X_BootState\n");
  //  getchar();


  err_status = VL53L1X_SensorInit(dev);


  printf("after VL53L1X_SensorInit\n");


  //    err_status = VL53L1X_SetInterMeasurementPeriod();

  //    err_status = VL53l1X_SetOffset();

  //  •
  err_status = VL53L1X_StartRanging(dev);
  printf("after VL53L1X_StartRanging\n");

  //  •
  uint8_t isready=0;
  while (isready == 0) {
    printf("VL53L1X_CheckForDataReady again\n");
    err_status = VL53L1X_CheckForDataReady(dev,&isready);
  }

  //  •
  uint16_t distance=0;

  while (1) {
    err_status = VL53L1X_GetDistance(dev,&distance);
    printf("distance:%d\n",distance);
    //  •
    err_status = VL53L1X_ClearInterrupt(dev);
    //    printf("after VL53L1X_ClearInterrupt\n");


  }

  //  •
  err_status = VL53L1X_StopRanging(dev);
  printf("after VL53L1X_StopRanging\n");

  return 0;
}

int check_toop(){

  //  uint16_t dev;
  uint16_t	dev=OLD_ADDR>>1;


  int fd;

  if ((fd = open("/dev/i2c-0",O_RDWR))< 0) {
    /* 错误处理 */

    exit(1);

  }
  //     dev=fd;
  initDevFD(fd);

  while (1) {

    int8_t err_status = VL53L1_WrByte(dev, PHASECAL_CONFIG__TIMEOUT_MACROP, 0x0A);
    if (err_status != 0) {
      printf("fail to VL53L1_WrByte \n");
    }
    printf("-[w0] VL53L1_WrByte:%d\n",0x0A);
    sleep(1);

  }
}



int main(int argc, char *argv[])
{
  work_loop();
  //    test_loop();
  //  check_toop();

}
