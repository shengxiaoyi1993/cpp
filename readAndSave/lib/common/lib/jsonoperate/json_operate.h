
#ifndef JSON_OPERTATE_H
#define JSON_OPERTATE_H
#include <stdio.h>
#include "../cjson/cJSON.h"
#include <string>

using namespace std;


/**
 * @brief getJsonObj
 * @param value
 * @param v_requesttype
 * @return return whole jsonobj
 */
cJSON * getJsonObj(const char *value,int* v_requesttype);

int getRemainTimes(const char *value,int & v_remain);

/**
 * @brief getRemainTimesJson
 * @param v_remain
 * @param ppdata
 * @return
 */
int getRemainTimesJson(const int v_remain,char **ppdata);


cJSON* createJsonObj_Network(const string & v_ip,
                             const string & v_gateway,
                             const string & v_mask);



int getResponseJson(const int v_returncode,
                    cJSON* v_obj
                    , char **ppdata);

int getNetWorkSettingResponseJson(
        int v_returncode,
        const string & v_ip,
        const string & v_gateway,
        const string & v_mask,
        char** ppdata
        );


int getNetWorkSettingJson(const string & v_ip,
                          const string & v_gateway,
                          const string & v_mask,
                          char** ppdata
                          );

int loadNetWorkSettingFromJson(const cJSON* v_obj,
                               string & v_ip,
                               string & v_gateway,
                               string & v_mask);

int getNetWorkSettingFromJsonString(const string& v_json,
                                    string & v_ip,
                                    string & v_gateway,
                                    string & v_mask);


int getBroadcastJson(const cJSON* v_dataobj,char**ppdata);


cJSON* createRemainTimesObj(const int v_remain);



int getImagePathFromJson(cJSON* v_obj, char **ppdata);

int getWSParaFromJsonObj(cJSON* v_obj,string &v_addr,int &v_port);

int getDeviceInfo(const char* v_data,string &v_language,string &v_region,string &v_sn );
int getDeviceFromJsonObj(const cJSON* v_jsonobj,string &v_language,string &v_region,string &v_sn );



int  getNetworkSettingRequest(char **ppdata,
                              const string &v_ip,
                              const string &v_mask,
                              const string &v_gateway,
                              const int v_requesttype=2
        );

int getReturnCode(const string & v_response);


/**
 * @brief isMsgEncrypted
 * @param v_obj
 * @return
 */

bool isMsgEncrypted(const cJSON* v_obj,cJSON** v_encryptedobj,
                    const string & v_username,
                    const string & v_password,
                    const string & v_sn);


int getSimpleResquest(const int v_requesttype,string &v_msg);

int getBroadcastParaFromResponse(const string& v_reponse,
                                 string & v_addr_b,
                                 int & v_port_b,
                                 int & v_interval_b
                                 );

int getBroadcastResetRequest(char **ppdata,
                             const string &v_addr_b,
                             const int &v_port_b,
                             const int &v_interval_b,
                             const int v_requesttype=5
        );

int getCutDownRemainRequest(char **ppdata,
                            const string & v_key,
                            const string &v_keytype,
                            const int v_requesttype=6);

int getRemainFromResponse(const string& v_reponse,int & v_remain);

int explainDemoConfig(const string& v_reponse,int & v_mode);


#endif
