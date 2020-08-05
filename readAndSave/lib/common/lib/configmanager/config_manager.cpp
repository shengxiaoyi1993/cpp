#include "config_manager.h"
#include <stdlib.h>
#include <fstream>
#include <unistd.h>

#include "..//basic/basic.h"
#include"../jsonoperate/json_operate.h"

#define DEBUG_CONFIGMANAGER

const char *path_deviceconfig="/home/root/device/config/info.config";
const char *path_broadcastconfig="/home/root/device/config/broadcast.config";
const char *path_webserverconfig="/home/root/device/config/webserver.config";
const char *path_controlinfo="/home/root/device/config/controlinfo.config";

const char * path_testimage="/home/root/device/app/image_generator/images/test/test.jpg";
const char *dir_workimage="/home/root/device/app/image_generator/images/work/";

const char *path_wsconnector="/home/root/device/script/restart_wsconnect.sh";

const char *path_devicecontrol="/home/root/device/script/control_device.sh";
const char *path_restart_broadcast="/home/root/device/script/restart_broadcast.sh";
const char *path_restart_webserver="/home/root/device/script/restart_webserver.sh";


//0
DEVICE_ERRCODE getDeviceInfo(char **ppdata){
    int flag = getStringFromFile(path_deviceconfig,ppdata);
    if(flag == 0){
        return DEVICE_ERRCODE_SUCCESS;
    }
    return DEVICE_ERRCODE_OPERATE_FAIL;

}


DEVICE_ERRCODE getDeviceInfo(string &v_language,string &v_region,string &v_sn){

    char* data = nullptr;
    if(getDeviceInfo(&data) == DEVICE_ERRCODE_SUCCESS){
        int flag= getDeviceInfo(data,v_language,v_region,v_sn);
        if(0 == flag){
            return DEVICE_ERRCODE_SUCCESS;
        }
        else{
            return DEVICE_ERRCODE_OPERATE_FAIL;
        }

    }
    else {
        return DEVICE_ERRCODE_OPERATE_FAIL;
    }

}




//1 <!Incomplete>
DEVICE_ERRCODE getNetworkSetting(string & v_ip,
                                 string & v_gateway,
                                 string & v_mask
                                 ){
    v_ip="192.168.2.1";
    v_gateway="192.168.1.1";
    v_mask="255.255.255.0";
    return DEVICE_ERRCODE_SUCCESS;
}




//2 <!Incomplete>
DEVICE_ERRCODE resetNetwork(const string & v_ip,
                            const string & v_gateway,
                            const string & v_mask
                            ){
    (void)v_ip;
    (void)v_gateway;
    (void)v_mask;

    return DEVICE_ERRCODE_SUCCESS;

}

//3
DEVICE_ERRCODE getBroadcastSetting(
        char **ppdata
        ){
    int flag = getStringFromFile(path_broadcastconfig,ppdata);
    if(flag == 0 && (*ppdata!=nullptr)){
        return DEVICE_ERRCODE_SUCCESS;
    }
    return DEVICE_ERRCODE_OPERATE_FAIL;

}

//4
DEVICE_ERRCODE resetBroadcast(const  char *data){
    saveFile((char*)data,path_broadcastconfig);
    return DEVICE_ERRCODE_SUCCESS;
}


//5
DEVICE_ERRCODE getRemainTimes(int & v_remian){
    char *pdata=nullptr;
    int flag= getStringFromFile(path_controlinfo,&pdata);
    if(flag == 0 && (pdata != nullptr)){
        int operateflag= getRemainTimes(pdata,v_remian);
        free(pdata);
        if(operateflag == 0){
            return DEVICE_ERRCODE_SUCCESS;

        }
    }

    return DEVICE_ERRCODE_OPERATE_FAIL;

}

//6
DEVICE_ERRCODE cutDownRemainTimes(){
    int v_remain;
    DEVICE_ERRCODE flag_get=getRemainTimes(v_remain);
    if(flag_get == DEVICE_ERRCODE_SUCCESS){
        if(v_remain>0){
            v_remain--;
        }
        else{
            v_remain=0;
        }
        char* tmpjson=nullptr;
        int flag_json=getRemainTimesJson(v_remain,&tmpjson);
        if(flag_json== 0 ){
            if(tmpjson != nullptr){
                saveFile(tmpjson,path_controlinfo);
                free(tmpjson);
                tmpjson=nullptr;
                return DEVICE_ERRCODE_SUCCESS;
            }
        }
    }
    return DEVICE_ERRCODE_OPERATE_FAIL;

}

//7
DEVICE_ERRCODE getTestImage(char** ppdata,int & v_size){
    int flag_get= getStringFromFile(path_testimage,ppdata,v_size);
    if(flag_get == 0){
        return DEVICE_ERRCODE_SUCCESS;
    }
    return DEVICE_ERRCODE_OPERATE_FAIL;
}

//8
DEVICE_ERRCODE buildWSConnection(const string & v_addr,
                                 const int port,
                                 const string &key){
    string str_cmd=string(path_wsconnector)+" "+v_addr+" "
            +integerToString(port)+" "+key+" &";
#ifdef  DEBUG_CONFIGMANAGER

    ofstream configmanager_log("configmanager_log.txt");
    configmanager_log<<"str_cmd:"<<str_cmd<<endl;
#endif


    pid_t pid = fork();
    switch(pid)
    {
    case -1:
        return DEVICE_ERRCODE_OPERATE_FAIL;
    case 0:
        close_all_fd(getpid());

        execlp("sh",
               "sh",
               path_wsconnector,
               v_addr.c_str(),
               integerToString(port).c_str(),
               key.c_str(),
               nullptr);
        exit(0);
    default:
        return DEVICE_ERRCODE_SUCCESS;

    }

}


//9
DEVICE_ERRCODE getImage(const string & v_path,char** ppdata,int &v_size){
    int flag_get= getStringFromFile(v_path,ppdata,v_size);
    if(flag_get == 0){
        return DEVICE_ERRCODE_SUCCESS;
    }
    return DEVICE_ERRCODE_OPERATE_FAIL;
}


//10
DEVICE_ERRCODE shutDownDevice(){
    string str_cmd=string(path_devicecontrol)+" shutdown";
    pid_t pid = fork();
    switch(pid)
    {
    case -1:
        return DEVICE_ERRCODE_OPERATE_FAIL;
    case 0:
//        execvp("sh",(char* const*)str_cmd.c_str());
//        execlp("sh","sh",str_cmd.c_str(),nullptr);
        close_all_fd(getpid());
        execlp("sh","sh",path_devicecontrol,"shutdown",nullptr);
        exit(0);


//        break;
    default:
        return DEVICE_ERRCODE_SUCCESS;

//        break;
    }
//    system(str_cmd.c_str());
}

//11
DEVICE_ERRCODE rebootDevice(){
    string str_cmd=string(path_devicecontrol)+" reboot";
    pid_t pid = fork();
    switch(pid)
    {
    case -1:
        return DEVICE_ERRCODE_OPERATE_FAIL;
    case 0:
//        execvp("sh",(char* const*)str_cmd.c_str());
        close_all_fd(getpid());
        execlp("sh","sh",path_devicecontrol,"reboot",nullptr);
        exit(0);

    default:
        return DEVICE_ERRCODE_SUCCESS;

    }

}


//12
DEVICE_ERRCODE restartBroadcast(){
    string str_cmd=string(path_restart_broadcast)+" &";
    pid_t pid = fork();
    switch(pid)
    {
    case -1:
        return DEVICE_ERRCODE_OPERATE_FAIL;
    case 0:
        close_all_fd(getpid());

        execlp("sh","sh",path_restart_broadcast,nullptr);
        exit(0);

    default:
        return DEVICE_ERRCODE_SUCCESS;
    }
}


//13
DEVICE_ERRCODE restartWebServer(){
    string str_cmd=string(path_restart_webserver)+" &";
//    pid_t pid = fork();
//    switch(pid)
//    {
//    case -1:
//        return DEVICE_ERRCODE_OPERATE_FAIL;
//    case 0:
//        close_all_fd(getpid());

//        execlp("sh","sh",path_restart_webserver,nullptr);
//        exit(0);

////        break;
//    default:
//        return DEVICE_ERRCODE_SUCCESS;

////        break;
//    }
    system(str_cmd.c_str());
    return DEVICE_ERRCODE_SUCCESS;

}


int getBroadcastInfo(string & v_addr,int & v_port,int& v_interval){
    char* pdata=nullptr;
    int flag = getStringFromFile(path_broadcastconfig,&pdata);
    if((pdata != nullptr)
            && (0 == flag)){
        cJSON* root=cJSON_Parse(pdata);
        int flag = 0;
        if(root != nullptr){
            cJSON* item=cJSON_GetObjectItem(root,"addr");
            if(nullptr != item){
                v_addr=item->valuestring;
            }
            else{
                flag=-1;
            }
            item=cJSON_GetObjectItem(root,"port");
            if(nullptr !=item ){
                v_port=item->valueint;
            }
            else{
                flag=-1;
            }

            item=cJSON_GetObjectItem(root,"interval");
            if(nullptr !=item ){
                v_interval=item->valueint;
            }
            else{
                flag=-1;
            }
            cJSON_free(root);
            root=nullptr;
        }
        free(pdata);
        pdata=nullptr;
        return flag;
    }
    return -1;

}



int getBroadcastMsg(char **ppdata){
    char* pdata=nullptr;
    int flag = getStringFromFile(path_deviceconfig,&pdata);
    if(nullptr == pdata || flag !=0){
        return -1;
    }

    cJSON* root_device =cJSON_Parse(pdata);
    if(nullptr == root_device){
        free(pdata);
        pdata=nullptr;
        return -1;
    }

    string v_ip;
    string v_gateway;
    string v_mask;

    if(DEVICE_ERRCODE_SUCCESS != getNetworkSetting(v_ip,v_gateway,v_mask)){
        cJSON_free(root_device);
        root_device=nullptr;
        free(pdata);
        pdata=nullptr;
        return -1;
    }

    cJSON* obj_network=createJsonObj_Network(v_ip,v_gateway,v_mask);
    if(nullptr != obj_network ){
        cJSON_AddItemToObject(root_device,"network",obj_network);
    }

    *ppdata=cJSON_Print(root_device);
    cJSON_free(root_device);
    root_device=nullptr;
    free(pdata);
    pdata=nullptr;
    if(nullptr != *ppdata){
        return 0;
    }
    else{
        return -1;
    }

}


DEVICE_ERRCODE getAuthPara(string & v_user,string & v_password){
    v_user="root";
    v_password="password";
    return DEVICE_ERRCODE_SUCCESS;

}

string getPublicKey(const string & v_user,
                    const string & v_password,
                    const string& vsn){
    return picosha2::hash256_hex_string(v_user+v_password+vsn);

}

