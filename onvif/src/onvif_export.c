#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "onvif_export.h"
#include "onvif/soapH.h"
#include "onvif/wsaapi.h"
#include "onvif/soapStub.h"
#include "onvif/wsdd.nsmap"
#include "onvif/stdsoap2.h"
#include "onvif/wsseapi.h"


#define SOAP_ASSERT     assert
#define SOAP_DBGLOG     printf
#define SOAP_DBGERR     printf

#define SOAP_TO         "urn:schemas-xmlsoap-org:ws:2005:04:discovery"
#define SOAP_ACTION     "http://schemas.xmlsoap.org/ws/2005/04/discovery/Probe"

#define SOAP_MCAST_ADDR "soap.udp://239.255.255.250:3702"// onvif multicast address

#define SOAP_ITEM       ""// scope of device
#define SOAP_TYPES      "dn:NetworkVideoTransmitter"// type of device

#define SOAP_SOCK_TIMEOUT    (1)// socket timeout
#define ONVIF_TOKEN_SIZE     65 // 唯一标识该视频编码器的令牌字符串

#define SOAP_CHECK_ERROR(result, soap, str) \
    do { \
    if (SOAP_OK != (result) || SOAP_OK != (soap)->error) { \
    soap_perror((soap), (str)); \
    if (SOAP_OK == (result)) { \
    (result) = (soap)->error; \
    } \
    goto EXIT;\
    } \
    } while (0)

/*configuration of video encode */
struct tagVideoEncoderConfiguration
{
    char token[ONVIF_TOKEN_SIZE];// video token
    int Width;// resolution ratio
    int Height;
};

/* configuration of device */
struct tagProfile {
    char token[ONVIF_TOKEN_SIZE];// device token

    struct tagVideoEncoderConfiguration venc;// video encoding configuration information
};


//enum tt__CapabilityCategory my_category;

void soap_perror(struct soap *soap, const char *str)
{
    if (NULL == str) {
        SOAP_DBGERR("[soap] error: %d, %s, %s\n", soap->error, *soap_faultcode(soap), *soap_faultstring(soap));
    } else {
        SOAP_DBGERR("[soap] %s error: %d, %s, %s\n", str, soap->error, *soap_faultcode(soap), *soap_faultstring(soap));
    }
    return;
}

void* ONVIF_soap_malloc(struct soap *soap, unsigned int n)
{
    void *p = NULL;

    if (n > 0) {
        p = soap_malloc(soap, n);
        SOAP_ASSERT(NULL != p);
        memset(p, 0x00 ,n);
    }
    return p;
}


struct soap *ONVIF_soap_new(int timeout)
{
    struct soap *soap = NULL;// onvif soap

    SOAP_ASSERT(NULL != (soap = soap_new()));

    soap_set_namespaces(soap, namespaces);// set soap namespaces
    soap->recv_timeout    = timeout;// timeout
    soap->send_timeout    = timeout;
    soap->connect_timeout = timeout;

#if defined(__linux__) || defined(__linux) // 参考https://www.genivia.com/dev.html#client-c的修改：
    soap->socket_flags = MSG_NOSIGNAL;                                          // To prevent connection reset errors
#endif

    soap_set_mode(soap, SOAP_C_UTFSTRING);// set encoding of character

    return soap;
}

void ONVIF_soap_delete(struct soap *soap)
{
    soap_destroy(soap); // remove deserialized class instances (C++ only)
    soap_end(soap); // Clean up deserialized data (except class instances) and temporary data
    soap_done(soap);// Reset, close communications, and remove callbacks
    soap_free(soap);// Reset and deallocate the context created with soap_new or soap_copy
}

void ONVIF_init_header(struct soap *soap)
{
    struct SOAP_ENV__Header *header = NULL;

    SOAP_ASSERT(NULL != soap);

    header = (struct SOAP_ENV__Header *)ONVIF_soap_malloc(soap, sizeof(struct SOAP_ENV__Header));//in heap
    soap_default_SOAP_ENV__Header(soap, header);
    header->wsa__MessageID = (char*)soap_wsa_rand_uuid(soap);//get uuid
    header->wsa__To        = (char*)ONVIF_soap_malloc(soap, strlen(SOAP_TO) + 1);
    header->wsa__Action    = (char*)ONVIF_soap_malloc(soap, strlen(SOAP_ACTION) + 1);
    strcpy(header->wsa__To, SOAP_TO);
    strcpy(header->wsa__Action, SOAP_ACTION);
    soap->header = header;

    return;
}


void ONVIF_init_ProbeType(struct soap *soap, struct wsdd__ProbeType *probe)
{
    struct wsdd__ScopesType *scope = NULL;// 用于描述查找哪类的Web服务

    SOAP_ASSERT(NULL != soap);
    SOAP_ASSERT(NULL != probe);

    scope = (struct wsdd__ScopesType *)ONVIF_soap_malloc(soap, sizeof(struct wsdd__ScopesType));
    soap_default_wsdd__ScopesType(soap, scope);// 设置寻找设备的范围
    scope->__item = (char*)ONVIF_soap_malloc(soap, strlen(SOAP_ITEM) + 1);
    strcpy(scope->__item, SOAP_ITEM);

    memset(probe, 0x00, sizeof(struct wsdd__ProbeType));
    soap_default_wsdd__ProbeType(soap, probe);
    probe->Scopes = scope;
    probe->Types  = (char*)ONVIF_soap_malloc(soap, strlen(SOAP_TYPES) + 1);// 设置寻找设备的类型
    strcpy(probe->Types, SOAP_TYPES);

    return;
}

static int ONVIF_SetAuthInfo(struct soap *soap, const char *username, const char *password)
{
    int result = 0;

    SOAP_ASSERT(NULL != username);
    SOAP_ASSERT(NULL != password);

    result = soap_wsse_add_UsernameTokenDigest(soap, NULL, username, password);
    SOAP_CHECK_ERROR(result, soap, "add_UsernameTokenDigest");

EXIT:

    return result;
}

/************************************************************************
**函数：ONVIF_GetSnapshotUri
**功能：获取设备图像抓拍地址(HTTP)
**参数：
** [in] MediaXAddr - 媒体服务地址
** [in] ProfileToken - the media profile token
** [out] uri - 返回的地址
** [in] sizeuri - 地址缓存大小 **返回： 0表明成功，非0表明失败
**备注： 1). 并非所有的ProfileToken都支持图像抓拍地址。
** 举例：XXX品牌的IPC有如下三个配置profile0/profile1/TestMediaProfile，其中TestMediaProfile返回的图像抓拍地址就是空指针。
************************************************************************/
int ONVIF_GetSnapshotUri(const char *MediaXAddr,
                         char *ProfileToken,
                         char *uri,
                         unsigned int sizeuri,
                         const char* username,
                         const char* password
                         )
{
    int result = 0;
    struct soap *soap = NULL;
    struct _trt__GetSnapshotUri         req;
    struct _trt__GetSnapshotUriResponse rep;

    SOAP_ASSERT(NULL != MediaXAddr);
    SOAP_ASSERT(NULL != uri);
    memset(uri, 0x00, sizeuri);

    SOAP_ASSERT(NULL != (soap = ONVIF_soap_new(SOAP_SOCK_TIMEOUT)));

    ONVIF_SetAuthInfo(soap, username, password);

    memset(&req, 0x00, sizeof(req));
    memset(&rep, 0x00, sizeof(rep));
    req.ProfileToken = ProfileToken;
    result = soap_call___trt__GetSnapshotUri(soap, MediaXAddr, NULL, &req, &rep);
    SOAP_CHECK_ERROR(result, soap, "GetSnapshotUri");


    result = -1;
    if (NULL != rep.MediaUri) {
        if (NULL != rep.MediaUri->Uri) {
            if (sizeuri > strlen(rep.MediaUri->Uri)) {
                strcpy(uri, rep.MediaUri->Uri);
                result = 0;
            } else {
                SOAP_DBGERR("Not enough cache!\n");
            }
        }
    }

EXIT:

    if (NULL != soap) {
        ONVIF_soap_delete(soap);
    }

    return result;
}

int ONVIF_DetectDevice(void (*cb)(char *DeviceXAddr) ,
                       char ***pp_devurl,
                       int* psize,
                       int timeout)
{

    int i;
    int result = 0;
    unsigned int count = 0;// count of device
    struct soap *soap = NULL;// soap
    struct wsdd__ProbeType      req;// request
    struct __wsdd__ProbeMatches resp;// respone
    struct wsdd__ProbeMatchType *probeMatch;

    time_t  time_start;
    time_t  time_curr;

    time(&time_start);


    SOAP_ASSERT(NULL != (soap = ONVIF_soap_new(SOAP_SOCK_TIMEOUT)));

    ONVIF_init_header(soap);// init header

    ONVIF_init_ProbeType(soap, &req);//set scope and type
    result = soap_send___wsdd__Probe(soap, SOAP_MCAST_ADDR, NULL, &req);// send request

    //用单向链表保存搜索到的ip，搜索结束后统一返回双重指针
    DevUrl * purlhead=NULL;
    DevUrl * purlend=purlhead;

    *psize=0;

    while (SOAP_OK == result)// receive respone
    {
        memset(&resp, 0x00, sizeof(resp));
        int result_recv = soap_recv___wsdd__ProbeMatches(soap, &resp);

        if (SOAP_OK == result_recv) {
            if (soap->error) {
                soap_perror(soap, "ProbeMatches");
            }
            else
            {
                for(i = 0; i < resp.wsdd__ProbeMatches->__sizeProbeMatch; i++)//display information
                {

                    //                    printf("__sizeProbeMatch        : %d\n", resp.wsdd__ProbeMatches->__sizeProbeMatch);
                    //                    printf("wsa__EndpointReference  : %p\n", resp.wsdd__ProbeMatches->ProbeMatch->wsa__EndpointReference);
                    //                    printf("Target EP Address       : %s\n", resp.wsdd__ProbeMatches->ProbeMatch->wsa__EndpointReference.Address);
                    //                    printf("Target Type             : %s\n", resp.wsdd__ProbeMatches->ProbeMatch->Types);
                    //                    printf("Target Service Address  : %s\n", resp.wsdd__ProbeMatches->ProbeMatch->XAddrs);
                    //                    printf("Target Metadata Version : %d\n", resp.wsdd__ProbeMatches->ProbeMatch->MetadataVersion);
                    //                    if(resp.wsdd__ProbeMatches->ProbeMatch->Scopes)
                    //                    {
                    //                        printf("Target Scopes Address   : %s\n\n", resp.wsdd__ProbeMatches->ProbeMatch->Scopes->__item);
                    //                    }

                    DevUrl *devurl_tmp =(DevUrl*)malloc(sizeof (DevUrl));
                    if(devurl_tmp == NULL){
                        return -1;
                    }
                    devurl_tmp->next=NULL;
                    memset(devurl_tmp->adddr,0,128*sizeof (char));
                    memcpy(devurl_tmp->adddr , resp.wsdd__ProbeMatches->ProbeMatch->XAddrs , strlen(resp.wsdd__ProbeMatches->ProbeMatch->XAddrs));
                    *psize=*psize+1;
                    if(purlend == NULL){
                        purlhead=devurl_tmp;
                        purlend=purlhead;
                    }
                    else{
                        purlend->next=devurl_tmp;
                        purlend=purlend->next;
                    }

                }
                if (NULL != resp.wsdd__ProbeMatches)
                {
                    count += resp.wsdd__ProbeMatches->__sizeProbeMatch;
                    for(i = 0; i < resp.wsdd__ProbeMatches->__sizeProbeMatch; i++)
                    {
                        probeMatch = resp.wsdd__ProbeMatches->ProbeMatch + i;
                        if (NULL != cb)
                        {
                            cb(probeMatch->XAddrs);    // run callback function
                        }
                    }
                }
            }
        }
        else if(result_recv == -1){
            time( &time_curr);
            if(time_curr-time_start>timeout
                    && timeout!=-1){
                break;
            }

        }
        else
        {
            break;
        }
    }


    if(*psize!=0){
        (*pp_devurl)=(char **)malloc(sizeof (char*)*(*psize));
        int seq=0;
        DevUrl *tmpnode=NULL;
        while(purlhead!=NULL){
            (*pp_devurl)[seq]=(char*)malloc(sizeof (char)*strlen(purlhead->adddr));

            if((*pp_devurl)[seq] == NULL){
                printf("fail to malloc ");
                return -1;
            }
            memset((*pp_devurl)[seq],0,sizeof (char)*strlen(purlhead->adddr));
            memcpy((*pp_devurl)[seq],purlhead->adddr,sizeof (char)*strlen(purlhead->adddr));

            tmpnode =purlhead->next;
            free(purlhead);
            purlhead=NULL;
            purlhead=tmpnode;
            seq++;
        }
    }

    if (NULL != soap)
    {
        ONVIF_soap_delete(soap);
    }
    return 0;
}



int ONVIF_GetDeviceInformation(const char *DeviceXAddr,
                               struct _tds__GetDeviceInformationResponse *pdevinfo_resp,
                               const char* username,
                               const char* password
                               )
{
    int result = 0;
    struct soap *soap = NULL;
    struct _tds__GetDeviceInformation           devinfo_req;
    struct _tds__GetDeviceInformationResponse   devinfo_resp;

    SOAP_ASSERT(NULL != DeviceXAddr);
    SOAP_ASSERT(NULL != (soap = ONVIF_soap_new(SOAP_SOCK_TIMEOUT)));

    ONVIF_SetAuthInfo(soap, username, password);

    memset(&devinfo_req, 0x00, sizeof(devinfo_req));
    memset(pdevinfo_resp, 0x00, sizeof(struct _tds__GetDeviceInformationResponse));
    result = soap_call___tds__GetDeviceInformation(soap, DeviceXAddr, NULL, &devinfo_req, &devinfo_resp);
    SOAP_CHECK_ERROR(result, soap, "GetDeviceInformation");
    pdevinfo_resp->Model=(char*)malloc(strlen (devinfo_resp.Model)+1);
    if(pdevinfo_resp->Model == NULL){
        return -1;
    }
    memcpy(pdevinfo_resp->Model,devinfo_resp.Model,strlen (devinfo_resp.Model)+1);
    pdevinfo_resp->HardwareId=(char*)malloc(strlen (devinfo_resp.HardwareId)+1);
    if(pdevinfo_resp->HardwareId == NULL){
        return -1;
    }
    memcpy(pdevinfo_resp->HardwareId,devinfo_resp.HardwareId,strlen (devinfo_resp.HardwareId)+1);
    pdevinfo_resp->Manufacturer=(char*)malloc(strlen (devinfo_resp.Manufacturer)+1);
    if(pdevinfo_resp->Manufacturer == NULL){
        return -1;
    }
    memcpy(pdevinfo_resp->Manufacturer,devinfo_resp.Manufacturer,strlen (devinfo_resp.Manufacturer)+1);
    pdevinfo_resp->SerialNumber=(char*)malloc(strlen (devinfo_resp.SerialNumber)+1);
    if(pdevinfo_resp->SerialNumber == NULL){
        return -1;
    }
    memcpy(pdevinfo_resp->SerialNumber,devinfo_resp.SerialNumber,strlen (devinfo_resp.SerialNumber)+1);

    pdevinfo_resp->FirmwareVersion=(char*)malloc(strlen (devinfo_resp.FirmwareVersion)+1);
    if(pdevinfo_resp->FirmwareVersion == NULL){
        return -1;
    }
    memcpy(pdevinfo_resp->FirmwareVersion,devinfo_resp.FirmwareVersion,strlen (devinfo_resp.FirmwareVersion)+1);

EXIT:

    if (NULL != soap) {
        ONVIF_soap_delete(soap);
    }
    return result;
}

int ONVIF_GetCapabilities(const char *device_server ,
                          char *media_ip ,
                          char *ptz_ip,
                          const char* username,
                          const char* password
                          )
{
    int result = 0;
    struct soap *soap = NULL;
    struct _tds__GetCapabilities            req;
    struct _tds__GetCapabilitiesResponse    resp;

    SOAP_ASSERT(NULL != device_server);
    SOAP_ASSERT(NULL != (soap = ONVIF_soap_new(SOAP_SOCK_TIMEOUT)));
    memset(&req, 0x00, sizeof(req));

    memset(&resp, 0x00, sizeof(resp));
    req.__sizeCategory = 1;
    req.Category = (enum tt__CapabilityCategory*)soap_malloc (soap, sizeof(int));
    *(req.Category) = (enum tt__CapabilityCategory)5/*(tt__CapabilityCategory__Media)*/;

    ONVIF_SetAuthInfo(soap, username, password);

    result = soap_call___tds__GetCapabilities(soap, device_server, NULL, &req, &resp);

    if(SOAP_OK != result ){
        return -1;
    }

    printf("\n\n");
    //printf("result is :%d\n", result);
    SOAP_CHECK_ERROR(result, soap, "GetCapabilities");
    if(strlen(resp.Capabilities->Media->XAddr) > 128)
    {
        return -1;
    }
    else
    {
        memcpy(media_ip , resp.Capabilities->Media->XAddr , strlen(resp.Capabilities->Media->XAddr));
    }
    /*get PTZ address*/
    req.__sizeCategory = 1;
    req.Category = (enum tt__CapabilityCategory*)soap_malloc (soap, sizeof(int));
    *(req.Category) = (enum tt__CapabilityCategory)6/*(tt__CapabilityCategory__Media)*/;
    result = soap_call___tds__GetCapabilities(soap, device_server, NULL, &req, &resp);
    if(SOAP_OK != result ){
        return -1;
    }

    printf("\n\n");
    SOAP_CHECK_ERROR(result, soap, "GetCapabilities");
#if 1
    if(resp.Capabilities == NULL){
        printf("resp.Capabilities is NULL\n");
        return -1;
    }

    if(resp.Capabilities->PTZ == NULL)
    {
        printf("unsurpport PTZ\n");
        return -1;
    }
    if(strlen(resp.Capabilities->PTZ->XAddr) > 128)
    {
        return -1;
    }

    else
    {

        memcpy(ptz_ip , resp.Capabilities->PTZ->XAddr , strlen(resp.Capabilities->PTZ->XAddr));

    }
#endif
EXIT:

    if (NULL != soap) {
        ONVIF_soap_delete(soap);
    }

    return result;
}


int ONVIF_GetStreamUri(const char *MediaXAddr,
                       char *ProfileToken,
                       char** url,
                       const char* username,
                       const char* password)
{

    int result = 0;
    //    char uri[128] = {0};
    struct soap *soap = NULL;
    struct tt__StreamSetup              ttStreamSetup;
    struct tt__Transport                ttTransport;
    struct _trt__GetStreamUri           req;
    struct _trt__GetStreamUriResponse   resp;

    SOAP_ASSERT(NULL != MediaXAddr);

    SOAP_ASSERT(NULL != (soap = ONVIF_soap_new(SOAP_SOCK_TIMEOUT)));

    memset(&req, 0x00, sizeof(req));
    memset(&resp, 0x00, sizeof(resp));
    memset(&ttStreamSetup, 0x00, sizeof(ttStreamSetup));
    memset(&ttTransport, 0x00, sizeof(ttTransport));
    ttStreamSetup.Stream                = tt__StreamType__RTP_Unicast;
    ttStreamSetup.Transport             = &ttTransport;
    ttStreamSetup.Transport->Protocol   = tt__TransportProtocol__RTSP;
    ttStreamSetup.Transport->Tunnel     = NULL;
    req.StreamSetup                     = &ttStreamSetup;
    req.ProfileToken                    = ProfileToken;

    ONVIF_SetAuthInfo(soap, username, password);
    result = soap_call___trt__GetStreamUri(soap, MediaXAddr, NULL, &req, &resp);
    if(result != SOAP_OK){
        return result;
    }

    SOAP_CHECK_ERROR(result, soap, "GetServices");
    *url =(char*)malloc(sizeof (char)*(strlen( resp.MediaUri->Uri)+1));

    if(*url == NULL){
        printf("fail to malloc");
        return -1;
    }
    memset(*url,'\0',sizeof (char)*(strlen( resp.MediaUri->Uri)+1));
    memcpy(*url,resp.MediaUri->Uri,sizeof (char)*(strlen(resp.MediaUri->Uri)+1));

EXIT:

    if (NULL != soap) {
        ONVIF_soap_delete(soap);
    }
    return result;
}
/*get media profile*/
int ONVIF_Media_GetProfiles(const char *Media_ip,
                            char*** ppurlstream,
                            char*** ppurlsnap,
                            OnvifSize **pvideosize,
                            int *psize,
                            const char* username,
                            const char* password)
{



    *psize=0;

    int i = 0;
    int result = 0;
    int stmno = 0;
    struct soap *soap = NULL;
    struct tagProfile *profiles = NULL;
    struct _trt__GetProfiles            req;
    struct _trt__GetProfilesResponse    resp;

    SOAP_ASSERT(NULL != Media_ip);
    SOAP_ASSERT(NULL != (soap = ONVIF_soap_new(SOAP_SOCK_TIMEOUT)));

    ONVIF_SetAuthInfo(soap, username, password);

    memset(&req, 0x00, sizeof(req));
    memset(&resp, 0x00, sizeof(resp));
    //    printf("before :soap_call___trt__GetProfiles");
    result = soap_call___trt__GetProfiles(soap, Media_ip, NULL, &req, &resp);
    //    printf(">>>result is :%d\n" , result);
    SOAP_CHECK_ERROR(result, soap, "GetProfiles");
    //printf information of profiles
    //    printf("\n\n");
    //    printf("__sizeprofiles is  :%d\n" , resp.__sizeProfiles);
    //    printf("name is            :%s\n" , resp.Profiles->Name);
    //    printf("token is           :%s\n" , resp.Profiles->VideoSourceConfiguration->token);
    //    printf("sourcetoken is     :%s\n" , resp.Profiles->VideoSourceConfiguration->SourceToken);
    //    printf("usecoutn is        :%d\n" , resp.Profiles->VideoEncoderConfiguration->UseCount);
    //    printf("__size is          :%d\n" , resp.Profiles->VideoEncoderConfiguration->__size);
    //    printf("__any is           :%d\n" , resp.Profiles->VideoEncoderConfiguration->__any );
    //    printf("profile token is   :%s\n" , resp.Profiles->token);
    //    printf("\n\n");
    if (resp.__sizeProfiles > 0)
    {
        profiles = (struct tagProfile *)malloc(resp.__sizeProfiles * sizeof(struct tagProfile));//malloc cache
        SOAP_ASSERT(NULL != profiles);
        memset(profiles, 0x00, resp.__sizeProfiles * sizeof(struct tagProfile));
    }
    /*resolve respone*/
    *psize=resp.__sizeProfiles;

    if(*psize > 0){
        *ppurlstream=(char **)malloc(sizeof (char*)**psize);
        if(*ppurlstream == NULL){
            return -1;
        }

        *ppurlsnap=(char **)malloc(sizeof (char*)**psize);

        if(*ppurlsnap == NULL){
            return -1;
        }

        *pvideosize =(OnvifSize*)malloc(sizeof (OnvifSize)*(*psize));
        if(*pvideosize == NULL){
            return -1;
        }

    }

    for(i = 0; i < resp.__sizeProfiles; i++) {
        struct tt__Profile *RespProfile = &resp.Profiles[i];
        struct tagProfile *StoreProfile = &profiles[i];

        if (NULL != RespProfile->token)// store Token
        {
            strncpy(StoreProfile->token, RespProfile->token, sizeof(StoreProfile->token) - 1);
        }

        if (NULL != RespProfile->VideoEncoderConfiguration) //video encode configuration
        {
            if (NULL != RespProfile->VideoEncoderConfiguration->token) // store video Token
            {
                strncpy(StoreProfile->venc.token, RespProfile->VideoEncoderConfiguration->token, sizeof(StoreProfile->venc.token) - 1);
            }
            if (NULL != RespProfile->VideoEncoderConfiguration->Resolution) // video resolutio
            {
                StoreProfile->venc.Width  = RespProfile->VideoEncoderConfiguration->Resolution->Width;
                StoreProfile->venc.Height = RespProfile->VideoEncoderConfiguration->Resolution->Height;
            }
        }


        char *streamurl_tmp=NULL;
        int flag_getstream=ONVIF_GetStreamUri(Media_ip ,
                                              profiles[i].token,
                                              &streamurl_tmp,
                                              username,
                                              password);

        if(flag_getstream == SOAP_OK){
            (*ppurlstream)[i]=(char*)malloc(sizeof (char)*(strlen(streamurl_tmp)+1));
            if((*ppurlstream)[i] == NULL){
                printf("fail to malloc (*ppurlstream)[i] %d \n",i);
                return -1;
            }
            memset((*ppurlstream)[i],'\0',sizeof (char)*(strlen(streamurl_tmp)+1));
            memcpy((*ppurlstream)[i],streamurl_tmp,sizeof (char)*(strlen(streamurl_tmp)+1));
            if(streamurl_tmp != NULL){
                free(streamurl_tmp);
                streamurl_tmp=NULL;
            }
        }



        char snapurl[128];
        memset(snapurl,0,128);
        int size_snap=128;
        int res_getsnapurl=ONVIF_GetSnapshotUri(Media_ip ,
                                                profiles[i].token,
                                                snapurl,
                                                size_snap,
                                                username,
                                                password
                                                );

        if(res_getsnapurl == SOAP_OK){
            (*ppurlsnap)[i]=(char*)malloc(sizeof (char)*(strlen(snapurl)+1));
            memset((*ppurlsnap)[i],'\0',sizeof (char)*(strlen(snapurl)+1));
            memcpy((*ppurlsnap)[i],snapurl,sizeof (char)*(strlen(snapurl)+1));
        }


        (*pvideosize)[i].height=StoreProfile->venc.Height;
        (*pvideosize)[i].width=StoreProfile->venc.Width;


    }

    return resp.__sizeProfiles;
EXIT:

    if (NULL != soap) {
        ONVIF_soap_delete(soap);
    }

    return resp.__sizeProfiles;
}



int ONVIF_Get_Gateway(char *device_ip,
                      char *pgateway,
                      const char* username,
                      const char* password
                      )
{
    int result = -1;
    struct soap *soap = NULL;// point of soap
    struct _tds__GetNetworkDefaultGateway      req;//requst
    struct _tds__GetNetworkDefaultGatewayResponse resp;// respone

    SOAP_ASSERT(NULL != (soap = ONVIF_soap_new(SOAP_SOCK_TIMEOUT)));

    ONVIF_SetAuthInfo(soap, username, password);
    result = soap_call___tds__GetNetworkDefaultGateway(soap , device_ip , NULL , &req , &resp);

    if(SOAP_OK != result){
        printf("Fail to get NetworkGateway");
        return result;
    }

#if 1

    if(*(resp.NetworkGateway->IPv4Address) == NULL)
    {
        printf("can't get gateway address \n");
        return -1;
    }
    else
    {
        memcpy(pgateway,*(resp.NetworkGateway->IPv4Address),strlen(*(resp.NetworkGateway->IPv4Address))+1);
    }
#endif
    ONVIF_soap_delete(soap);
    return result;
}




int ONVIF_getStreamUrlAndSnapUrl(const char * device_addr,
                                 char*** ppurlstream,
                                 char*** ppurlsnap,
                                 OnvifSize **pvideosize,
                                 int *psize,
                                 const char* username,
                                 const char* password
                                 ){
    char media_ip[128];
    char ptz_ip[128];

    ONVIF_GetCapabilities(device_addr,
                          media_ip ,
                          ptz_ip,
                          username,
                          password
                          );

    int result = ONVIF_Media_GetProfiles(media_ip,
                                         ppurlstream,
                                         ppurlsnap,
                                         pvideosize,
                                         psize,
                                         username,
                                         password);
    return result;

}
