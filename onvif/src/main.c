#include <stdio.h>
#include "onvif_export.h"
const char* username="admin";
const char* password="admin";


void getUrl(char * addr){


    printf("\n\n\ndevice ip obtain: %s\n\n",addr);


    //---------------------
    //get gateway
    char gateway[128];
    memset(gateway,'0',128);
    ONVIF_Get_Gateway(addr,
                      gateway,
                      username,
                      password
                      );
    printf("gateway:%s\n",gateway);



    //------------------------------------------
    //get device info
    struct _tds__GetDeviceInformationResponse devinfo;
    int flag=ONVIF_GetDeviceInformation(addr,&devinfo,username,password);
    if(flag==SOAP_OK){
        printf("\nSucceed to ONVIF_GetDeviceInformation !\n");
        printf("Model:%s\n",devinfo.Model);
        printf("HardwareId:%s\n",devinfo.HardwareId);
        printf("Manufacturer:%s\n",devinfo.Manufacturer);
        printf("SerialNumber:%s\n",devinfo.SerialNumber);
        printf("FirmwareVersion:%s\n",devinfo.FirmwareVersion);
    }
    else{
        printf("Fail to ONVIF_GetDeviceInformation !\n");
    }

    //释放内存过程
    free(devinfo.Model);
    devinfo.Model=NULL;
    free(devinfo.HardwareId);
    devinfo.HardwareId=NULL;
    free(devinfo.Manufacturer);
    devinfo.Manufacturer=NULL;
    free(devinfo.SerialNumber);
    devinfo.SerialNumber=NULL;
    free(devinfo.FirmwareVersion);
    devinfo.FirmwareVersion=NULL;





    //---------------------------------------------------------

    //get stream url and snap url
    char **purlstream=NULL;
    char **purlsnap=NULL;
    int size_stream=0;
    OnvifSize *pvideosize=NULL;

    printf("\nget stream_url and snap_url \n");
    int result = ONVIF_getStreamUrlAndSnapUrl(addr,
                                              &purlstream,
                                              &purlsnap,
                                              &pvideosize,
                                              &size_stream,
                                              username,
                                              password);

    printf("size_stream:%d\n",size_stream);
    int k=0;
    for(k=0;k<size_stream;k++){
        if(purlstream[k] !=NULL){
            printf("stream %d: %s\n",k,purlstream[k]);
        }
        if(purlsnap[k] !=NULL){
            printf("snap   %d: %s\n",k,purlsnap[k]);
        }
        if(purlsnap[k] !=NULL){
            printf("size   %d: %d*%d\n",k,pvideosize[k].width,pvideosize[k].height);
        }
    }

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



}




int main(){



    char **purl=NULL;
    int size=0;
    int timeout=10;
    ONVIF_DetectDevice(getUrl,&purl,&size,timeout);

    printf("size:%d\n",size);
    int i=0;
    for(;i<size;i++){
        printf("%s\n",purl[i]);
    }

    if(size ==0){
        printf("no device find!\nquit !\n");
        return 0;
    }

    //释放指针内存
    int j=0;
    for(;i<size;i++){
        free(purl[i]);
        purl[i]=NULL;
    }
    free(purl);
    purl=NULL;



}
