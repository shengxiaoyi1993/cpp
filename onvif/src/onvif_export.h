#ifndef ONVIF_EXPORT_H
#define ONVIF_EXPORT_H


#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "onvif/soapH.h"
#include "onvif/wsaapi.h"
#include "onvif/soapStub.h"
#include "onvif/stdsoap2.h"
#include "onvif/wsseapi.h"


#define ONVIF_OUT



/**
 * @brief ONVIF_GetDeviceInformation 获取IP指向的设备的信息
 * @param DeviceXAddr                IP
 * @param pdevinfo_resp              保存设备信息的数据结构,注意释放该结构中的内存
 * @return
 */
ONVIF_OUT int ONVIF_GetDeviceInformation(const char *DeviceXAddr,
                                         struct _tds__GetDeviceInformationResponse *pdevinfo_resp,
                                         const char* username,
                                         const char* password
                                         );

typedef  struct  OnvifSize{
    int height;
    int width;
}OnvifSize;

typedef struct DevUrl{
    struct DevUrl *next;
    char adddr[128];
}DevUrl;
/**
 * @brief ONVIF_DetectDevice  检测设备数量
 * @param DeviceXAddr         每检测到一个设备回调用该回调函数将地址传出
 * @param pp_devurl           保存设备地址的地址，变长数组;注意释放指针中的内存
 * @param psize               地址的数量
 * @param timeout             超时时间，函数会在超时时间内检测设备，时间结束后，停止检索并以pp_devurl返回；
 *                            若timeout 为负值，则会持续检测；
 * @return
 */

ONVIF_OUT int ONVIF_DetectDevice(void (*cb)(char *DeviceXAddr) ,
                                 char ***pp_devurl,
                                 int* psize,
                                 int timeout);


/**
 * @brief ONVIF_getStreamUrlAndSnapUrl  获取某个设备的视频流和对应截图地址
 * @param device_addr
 * @param ppurlstream                   视频流地址列表，注意释放内存
 * @param ppurlsnap                     截图地址列表，注意释放内存
 * @param pvideosize                    保存视频或图片的尺寸线
 * @param psize
 * @param username
 * @param password
 * @return
 *
 *
    //释放内存
    int l=0;
    for(l=0;l<size_stream;l++){
        if(purlstream[l] !=NULL){
            free(purlstream[l]);
            purlstream[l]=NULL;
        }
        if(purlsnap[l] !=NULL){
            free(purlsnap[l]);
            purlsnap[l]=NULL;
        }
    }
    free(pvideosize);
    pvideosize=NULL;
    free(purlstream);
    purlstream=NULL;
    free(purlsnap);
    purlsnap=NULL;
 */

ONVIF_OUT int ONVIF_getStreamUrlAndSnapUrl(const char * device_addr,
                                           char*** ppurlstream,
                                           char*** ppurlsnap,
                                           OnvifSize **pvideosize,
                                           int *psize,
                                           const char* username,
                                           const char* password
                                           );

/**
 * @brief ONVIF_Get_Gateway  获取设备网关
 * @param device_ip
 * @param username
 * @param password
 * @return
 */
int ONVIF_Get_Gateway(char *device_ip,
                      char *pgateway,
                      const char* username,
                      const char* password
                      );


/**
 * @brief ONVIF_GetCapabilities  中间函数
 * @param device_server
 * @param media_ip
 * @param ptz_ip
 * @param username
 * @param password
 * @return
 */

int ONVIF_GetCapabilities(const char *device_server ,
                          char *media_ip ,
                          char *ptz_ip,
                          const char* username,
                          const char* password
                          );

/**
 * @brief ONVIF_Media_GetProfiles  获取视频流地址和对应的截图位置
 * @param Media_ip
 * @param ppurlstream
 * @param ppurlsnap
 * @param psize
 * @param username
 * @param password
 * @return
 */
int ONVIF_Media_GetProfiles(const char *Media_ip,
                            char*** ppurlstream,
                            char*** ppurlsnap,
                            OnvifSize **pvideosize,
                            int *psize,
                            const char* username,
                            const char* password);



/**
 * @brief ONVIF_GetStreamUri  中间函数，获取视频流
 * @param MediaXAddr
 * @param ProfileToken
 * @param url                 输入为二重指针，由函数内部进行分配内存，使用时注意该指针的内存释放
 * @param username
 * @param password
 * @return
 */

int ONVIF_GetStreamUri(const char *MediaXAddr,
                       char *ProfileToken,
                       char** url,
                       const char* username,
                       const char* password
                       );

/**
 * @brief ONVIF_GetSnapshotUri 中间函数，获取截图地址
 * @param MediaXAddr
 * @param ProfileToken
 * @param uri                 输入为数组
 * @param sizeuri
 * @param username
 * @param password
 * @return
 */
int ONVIF_GetSnapshotUri(const char *MediaXAddr,
                         char *ProfileToken,
                         char *uri,
                         unsigned int sizeuri,
                         const char* username,
                         const char* password
                         );

#endif
