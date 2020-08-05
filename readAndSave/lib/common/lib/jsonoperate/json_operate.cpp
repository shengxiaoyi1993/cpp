
#include"json_operate.h"
#include <stdio.h>
#include <string.h>
#include <string>
#include <fstream>
#include "../cjson/cJSON.h"
#include "../encrypt/response_data.h"
#include "../encrypt/sha256.h"


#define DEBUG_JSONOPERATE


using namespace std;


cJSON * getJsonObj(const char *value,int* v_requesttype){
    cJSON* root=cJSON_Parse(value);
    if(root != NULL){
        cJSON* item=cJSON_GetObjectItem(root,"request_type");
        if(item != NULL){
            *v_requesttype=item->valueint;
        }
        else{
            cJSON_free(root);
            root=NULL;
            return NULL;
        }
    }
    return root;
}


//{
//  "remain":1024
//}
int getRemainTimes(const char *value,int & v_remain){
    cJSON* root=cJSON_Parse(value);
    if(root != nullptr){
        cJSON* item=cJSON_GetObjectItem(root,"remain");
        if(item != nullptr){
            v_remain=item->valueint;
            cJSON_free(root);
            root=nullptr;
            return 0;
        }
        else{
            cJSON_free(root);
            root=nullptr;
            return -1;
        }
    }
    return -1;
}


int getRemainTimesJson(const int v_remain,char **ppdata){
    cJSON* root=cJSON_CreateObject();
    if(root != nullptr){
        cJSON_AddNumberToObject(root,"remain",v_remain);
        *ppdata=cJSON_Print(root);
        cJSON_free(root);
        root=nullptr;
        if(strlen(*ppdata)>0){
            return 0;
        }

    }
    return -1;
}



cJSON* createJsonObj_Network(const string & v_ip,
                             const string & v_gateway,
                             const string & v_mask){

    cJSON* root=cJSON_CreateObject();
    if(root != nullptr){
        cJSON_AddStringToObject(root,"ip",v_ip.c_str());
        cJSON_AddStringToObject(root,"gateway",v_gateway.c_str());
        cJSON_AddStringToObject(root,"mask",v_mask.c_str());
    }
    return root;

}



int getNetWorkSettingJson(const string & v_ip,
                          const string & v_gateway,
                          const string & v_mask,
                          char** ppdata
                          ){
    cJSON* root=createJsonObj_Network(v_ip,v_gateway,v_mask);

    if(root != nullptr){
        *ppdata=cJSON_Print(root);
        cJSON_free(root);
        root=nullptr;
        if(*ppdata != nullptr){
            if(strlen(*ppdata)>0){
                return 0;
            }
            else{
                free(*ppdata);
                *ppdata = nullptr;
            }
        }

    }
    return -1;

}

int getNetWorkSettingResponseJson(
        int v_returncode,
        const string & v_ip,
        const string & v_gateway,
        const string & v_mask,
        char** ppdata
        ){
    cJSON* networkobj=createJsonObj_Network(v_ip,v_gateway,v_mask);
    return getResponseJson(v_returncode,networkobj,ppdata);
}


int getResponseJson(const int v_returncode,
                    cJSON* v_obj,
                    char** ppdata
                    ){
    cJSON* root=cJSON_CreateObject();
    if(root != nullptr){
        cJSON_AddNumberToObject(root,"returncode",v_returncode);

        if(v_obj != nullptr){
            cJSON_AddItemToObject(root,"data",v_obj);
        }
        * ppdata=cJSON_Print(root);
        cJSON_free(root);
        root=nullptr;
        if(*ppdata != nullptr){
            if(strlen(*ppdata)>0){
                return 0;
            }
            else{
                free(*ppdata);
                *ppdata = nullptr;
            }
        }

    }
    else{
        return -1;
    }



}

int loadNetWorkSettingFromJson(const cJSON* v_obj,
                               string & v_ip,
                               string & v_gateway,
                               string & v_mask){
    if(v_obj != nullptr){
        cJSON* item=cJSON_GetObjectItem(v_obj,"ip");
        if(item != nullptr){
            v_ip=item->valuestring;
        }
        item=cJSON_GetObjectItem(v_obj,"gateway");
        if(item != nullptr){
            v_gateway=item->valuestring;
        }
        item=cJSON_GetObjectItem(v_obj,"mask");
        if(item != nullptr){
            v_mask=item->valuestring;
        }

        return 0;
    }
    else{
        return -1;
    }
}

int getNetWorkSettingFromJsonString(const string& v_json,
                                    string & v_ip,
                                    string & v_gateway,
                                    string & v_mask){
    cJSON* root=cJSON_Parse(v_json.c_str());
    if(nullptr != root){
        int flag=loadNetWorkSettingFromJson(root,v_ip,v_gateway,v_mask);
        cJSON_free(root);
        root=nullptr;
        return flag;
    }
    return -1;
}


int getBroadcastJson(const cJSON* v_dataobj, char **ppdata){

    if(v_dataobj != nullptr){
        cJSON* root=cJSON_CreateObject();
        cJSON* item=cJSON_GetObjectItem(v_dataobj,"port");
        if(item != nullptr){
            cJSON_AddNumberToObject(root,"port",item->valueint);
        }
        item=cJSON_GetObjectItem(v_dataobj,"addr");
        if(item != nullptr){
            cJSON_AddStringToObject(root,"addr",item->valuestring);
        }
        item=cJSON_GetObjectItem(v_dataobj,"interval");
        if(item != nullptr){
            cJSON_AddNumberToObject(root,"interval",item->valueint);
        }

        *ppdata=cJSON_Print(root);
        if(*ppdata != nullptr){
            return 0;
        }
    }
    return -1;
}



cJSON *createRemainTimesObj(const int v_remain){
    cJSON* root=cJSON_CreateObject();
    if(root != nullptr){
        cJSON_AddNumberToObject(root,"remain",v_remain);
    }
    return root;

}


int getImagePathFromJson(cJSON* v_obj,char** ppdata){
    if(v_obj != nullptr){
        cJSON* item=cJSON_GetObjectItem(v_obj,"path");
        if(item != nullptr){
            *ppdata=(char*)malloc(sizeof (char)*(strlen(item->valuestring)+1));
            if(*ppdata != nullptr){
                memcpy(*ppdata,item->valuestring,sizeof (char)*(strlen(item->valuestring)+1));
                return 0;

            }

        }
    }
    return -1;
}


int getWSParaFromJsonObj(cJSON* v_obj,string &v_addr,int &v_port){
    if(v_obj != nullptr){
        cJSON* item=cJSON_GetObjectItem(v_obj,"addr");
        if(item != nullptr){
            v_addr=item->valuestring;
        }
        else{
            return -1;
        }

        item=cJSON_GetObjectItem(v_obj,"port");
        if(item != nullptr){
            v_port=item->valueint;
        }
        else{
            return -1;
        }
        return 0;
    }
    return -1;
}






bool isMsgEncrypted(const cJSON* v_obj,cJSON** v_encryptedobj,
                    const string & v_username,
                    const string & v_password,
                    const string & v_sn){
    if(nullptr != v_obj){
        char* str_sec=v_obj->valuestring;
        if(nullptr != str_sec){
#ifdef DEBUG_JSONOPERATE
            ofstream jsonoperate_log("jsonoperate_log.txt");
#endif
            string string_sec=str_sec;
            string v_key=picosha2::hash256_hex_string(v_username+v_password+v_sn);
            string v_keytype="public";

#ifdef DEBUG_JSONOPERATE
            jsonoperate_log<<"v_key:"<<v_key<<endl;;
            jsonoperate_log<<"v_keytype:"<<v_keytype<<endl;;

            jsonoperate_log<<"string_sec:"<<string_sec<<endl;;
#endif

            ResponseData  data(v_key,v_keytype,"");
            data._secret_data=string_sec;
            data.DecodeSecretData(v_key);
#ifdef DEBUG_JSONOPERATE
            jsonoperate_log<<"data._data:"<<data._data<<endl;;
#endif

            *v_encryptedobj=cJSON_Parse(data._data.c_str());
            if(nullptr != *v_encryptedobj){
                cJSON *encryptobj=cJSON_GetObjectItem(*v_encryptedobj,"encrypted");
                if(nullptr != encryptobj){
                    int flag =encryptobj->valueint;
                    if(1 == flag){
                        return true;
                    }
                }
            }

        }
    }
    return false;
}



int getDeviceFromJsonObj(const cJSON* v_jsonobj,
                         string &v_language,
                         string &v_region,
                         string &v_sn ){
    if(nullptr != v_jsonobj){
        cJSON* item=cJSON_GetObjectItem(v_jsonobj,"language");
        if(nullptr != item){
            v_language=item->valuestring;
        }
        item=cJSON_GetObjectItem(v_jsonobj,"region");
        if(nullptr != item){
            v_region=item->valuestring;
        }
        item=cJSON_GetObjectItem(v_jsonobj,"sn");
        if(nullptr != item){
            v_sn=item->valuestring;
        }

        return 0;

    }
}



int getDeviceInfo(const char* v_data,string &v_language,string &v_region,string &v_sn ){
    if(nullptr != v_data){
        cJSON *root= cJSON_Parse(v_data);
        if(nullptr != root){
            int flag = getDeviceFromJsonObj(root,v_language,v_region,v_sn);
            free(root);
            root=nullptr;
            return flag;
        }

    }
    return -1;
}


int  getNetworkSettingRequest(char**ppdata,
                              const string &v_ip,
                              const string &v_mask,
                              const string &v_gateway,
                              const int v_requesttype){

    cJSON *root =cJSON_CreateObject();
    if(nullptr != root){
        cJSON_AddNumberToObject( root,"request_type",v_requesttype);
        cJSON* dataitem=cJSON_CreateObject();
        if(nullptr != dataitem){
            cJSON_AddStringToObject(dataitem,"ip",(char*)v_ip.c_str());
            cJSON_AddStringToObject(dataitem,"mask",(char*)v_mask.c_str());
            cJSON_AddStringToObject(dataitem,"gateway",(char*)v_gateway.c_str());
            cJSON_AddItemToObject(root,"data",dataitem);
            *ppdata=cJSON_Print(root);
            cJSON_free(root);
            root=nullptr;
            if(*ppdata!=nullptr){
                return 0;
            }
        }
        else{
            cJSON_free(root );
            root =nullptr;
        }
    }

    return -1;

}


int getReturnCode(const string & v_response){
    cJSON* root=cJSON_Parse(v_response.c_str());
    int returncode;
    if(nullptr != root){
        cJSON* item=cJSON_GetObjectItem(root,"returncode");

        if(nullptr != item){
            returncode=item->valueint;
        }
        else{
            returncode=-1;
        }
        cJSON_free(root);
        root=nullptr;
        return returncode;
    }
    return -1;
}

int getSimpleResquest(const int v_requesttype,string &v_msg){
    cJSON* root=cJSON_CreateObject();
    int flag=-1;
    if(root != nullptr){
        cJSON_AddNumberToObject(root,"request_type",v_requesttype);
        char* data=cJSON_Print(root);
        if(data != nullptr){
            v_msg=data;
            flag=0;
            free(data);
            data=nullptr;
        }
        cJSON_free(root);
        root=nullptr;
    }
    return flag;
}


int getBroadcastParaFromResponse(const string& v_response,
                                 string & v_addr_b,
                                 int & v_port_b,
                                 int & v_interval_b
                                 ){
    int returncode=0;
    cJSON* root=cJSON_Parse(v_response.c_str());

    if(nullptr != root){
        cJSON* dataitem=cJSON_GetObjectItem(root,"data");
        if(nullptr != dataitem){
            cJSON* item=cJSON_GetObjectItem(dataitem,"addr");
            if(nullptr != item){
                v_addr_b=item->valuestring;
            }
            else{
                returncode=-1;
            }

            item=cJSON_GetObjectItem(dataitem,"port");
            if(nullptr != item){
                v_port_b=item->valueint;
            }
            else{
                returncode=-1;
            }

            item=cJSON_GetObjectItem(dataitem,"interval");
            if(nullptr != item){
                v_interval_b=item->valueint;
            }
            else{
                returncode=-1;
            }
        }
        else  {
            returncode=-1;
        }

        cJSON_free(root);
        root=nullptr;
    }
    return returncode;

}


int getBroadcastResetRequest(char **ppdata,
                             const string &v_addr_b,
                             const int &v_port_b,
                             const int &v_interval_b,
                             const int v_requesttype
                             ){
    cJSON *root =cJSON_CreateObject();
    if(nullptr != root){
        cJSON_AddNumberToObject( root,"request_type",v_requesttype);
        cJSON* dataitem=cJSON_CreateObject();
        if(nullptr != dataitem){
            cJSON_AddStringToObject(dataitem,"addr",(char*)v_addr_b.c_str());
            cJSON_AddNumberToObject(dataitem,"port",v_port_b);
            cJSON_AddNumberToObject(dataitem,"interval",v_interval_b);
            cJSON_AddItemToObject(root,"data",dataitem);
            *ppdata=cJSON_Print(root);
            cJSON_free(root);
            root=nullptr;
            if(*ppdata!=nullptr){
                return 0;
            }
        }
        else{
            cJSON_free(root );
            root =nullptr;
        }
    }

    return -1;
}


int getCutDownRemainRequest(char **ppdata,
                            const string & v_key,
                            const string &v_keytype,
                            const int v_requesttype){
    string secretstring;
    cJSON *encrypteditem =cJSON_CreateObject();
    int returncode=-1;
    if(nullptr != encrypteditem){
        cJSON_AddBoolToObject(encrypteditem,"encrypted",true);
        char* tmpjson=encrypteditem->valuestring;
        if(nullptr != tmpjson){
            ResponseData  data(v_key,v_keytype,tmpjson);
            secretstring=data._secret_data;
            free(tmpjson);
            tmpjson=nullptr;
            returncode = 0;
        }
        else{
            returncode  = -1;
        }
        cJSON_free(encrypteditem);
        encrypteditem=nullptr;
    }

    if(0 !=returncode ){
        return returncode;
    }


    //dataitem
    cJSON *root =cJSON_CreateObject();
    if(nullptr != root){
        cJSON_AddNumberToObject(root,"request_type",v_requesttype);
        cJSON_AddStringToObject(root,"data",secretstring.c_str());

        *ppdata=cJSON_Print(root);
        if(nullptr == *ppdata){
            returncode  = -1;
        }
        cJSON_free(root);
        root=nullptr;
    }
    else{
        returncode  = -1;
    }

    return returncode;
}


int getRemainFromResponse(const string& v_reponse,int & v_remain){
    cJSON* root=cJSON_Parse(v_reponse.c_str());
    int returncode=-1;
    if(nullptr != root){
        cJSON* item=cJSON_GetObjectItem(root,"data");
        if(nullptr != item){
            cJSON* subitem=cJSON_GetObjectItem(item,"remain");
            if(nullptr != subitem){
                v_remain=item->valueint;
                returncode=0;
            }
        }
        cJSON_free(root);
        root=nullptr;
    }
    return returncode;
}

int explainDemoConfig(const string& v_reponse,int & v_mode){
    cJSON* root=cJSON_Parse(v_reponse.c_str());
    int returncode=-1;
    if(nullptr != root){
        cJSON* item=cJSON_GetObjectItem(root,"mode");
        if(nullptr != item){
            v_mode=item->valueint;
            returncode = 0;
        }
        cJSON_free(root);
        root=nullptr;
    }
    return -1;
}



