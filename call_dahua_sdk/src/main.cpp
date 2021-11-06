#include <iostream>
#include "dahua/include/dhnetsdk.h"
#include <cstring>
#include <cstdio>
#include <unistd.h>

void CALLBACK cbSearchDevicesEx(LLONG lSearchHandle,DEVICE_NET_INFO_EX2 *pDevNetInfo, void* pUserData)
{
 printf("ip:%s\n", pDevNetInfo->stuDevInfo.szIP);
}

int main(int argc, char const *argv[])
{

    std::string strLocalIP = "192.168.1.126";

    NET_IN_STARTSERACH_DEVICE pInBuf = {0};
    NET_OUT_STARTSERACH_DEVICE pOutBuf = {0};
    LLONG seachHandle = 0;

    pInBuf.dwSize = sizeof(NET_IN_STARTSERACH_DEVICE);
    pInBuf.cbSearchDevices = cbSearchDevicesEx;
    pInBuf.pUserData = nullptr;
    strncpy(pInBuf.szLocalIp, strLocalIP.c_str(), sizeof(pInBuf.szLocalIp) - 1);
    pOutBuf.dwSize = sizeof(NET_OUT_STARTSERACH_DEVICE);

    seachHandle = CLIENT_StartSearchDevicesEx(&pInBuf, &pOutBuf);

    std::cout << "hello" << std::endl;

    // pause();
    getchar();
    
    return 0;
}
