
#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <stdio.h>
#include <iostream>
#include <string>
#include"errorcode.h"
#include"../encrypt/response_data.h"
#include"../encrypt/sha256.h"
#include "../cjson/cJSON.h"



using  namespace std;



DEVICE_ERRCODE getDeviceInfo(char **ppdata);
DEVICE_ERRCODE getDeviceInfo(string &v_language,string &v_region,string &v_sn);


/**
 * @brief getNetworkSetting
 * @param v_ip
 * @param v_gateway
 * @param v_mask
 * @return
 */
//1 <!Incomplete>
DEVICE_ERRCODE getNetworkSetting(string & v_ip,
                      string & v_gateway,
                      string & v_mask
                      );

//2 <!Incomplete>
DEVICE_ERRCODE resetNetwork(const string & v_ip,
                 const string & v_gateway,
                 const string & v_mask
                 );
//3
DEVICE_ERRCODE getBroadcastSetting(
        char **ppdata
        );

//4
DEVICE_ERRCODE resetBroadcast(const  char *data);


//5
DEVICE_ERRCODE getRemainTimes(int & v_remian);

//6
DEVICE_ERRCODE cutDownRemainTimes();

//7
DEVICE_ERRCODE getTestImage(char** ppdata, int &v_size);

//8
DEVICE_ERRCODE buildWSConnection(const string & v_addr,
                      const int port,const string & key);

//9
DEVICE_ERRCODE getImage(const string & v_path, char** ppdata, int &v_size);


//10
DEVICE_ERRCODE shutDownDevice();

//11
DEVICE_ERRCODE rebootDevice();


//12
DEVICE_ERRCODE restartBroadcast();


//13
DEVICE_ERRCODE restartWebServer();


//wait
DEVICE_ERRCODE getAuthPara(string & v_user,string & v_password);
string getPublicKey(const string & v_user,
                    const string & v_password,
                    const string& vsn);

int getBroadcastInfo(string & v_addr,int & v_port,int& v_interval);

int getBroadcastMsg(char **ppdata);








#endif
