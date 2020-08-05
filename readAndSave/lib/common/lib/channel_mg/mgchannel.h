#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include "../msgchannnel/msgchannel.h"
#include "../cjson/cJSON.h"

//#define DEBUG_MGCHANNEL




using namespace std;

typedef struct MGMessage{
    char path[100];
    bool iswait;
    //the device timecode of device,use to judge the timeout
    uint timecode;
    //identify the group
    uint groupid;
    //the sequence of image in group
    uint seq;
    //三种状态：first(0),mid(1),end(2)
    uint flag;

    MGMessage(){
        timecode=0;
        memset(path,0,sizeof (char)* 100);
        iswait=true;
    }

    MGMessage(uint v_timecode,const char* v_path,bool v_iswait){
        timecode=v_timecode;
        size_t len_path=strlen(v_path)+1;

        size_t len=len_path<100?len_path:100;
        memcpy(path,v_path,len);
        iswait=v_iswait;
        groupid=1;
        seq=4;

    }


    MGMessage(uint v_timecode,const char* v_path,bool v_iswait,uint v_groupid,
              uint v_seq,uint v_flag){
        timecode=v_timecode;
        size_t len_path=strlen(v_path)+1;

        size_t len=len_path<100?len_path:100;
        memcpy(path,v_path,len);
        iswait=v_iswait;
        groupid=v_groupid;
        seq=v_seq;
        flag=v_flag;

    }

    static MGMessage fromJsonObj(cJSON* root){
        MGMessage v_mgmsg;
        if(nullptr != root){
            bool allright=true;
            cJSON* item=cJSON_GetObjectItem(root,"timecode");
            if(item == nullptr){
                allright=false;
            }
            else{
                v_mgmsg.timecode=static_cast<uint>(item->valuedouble);
            }

            item=cJSON_GetObjectItem(root,"path");
            if(item == nullptr){
                allright=false;
            }
            else{
                memcpy(v_mgmsg.path,item->valuestring,strlen(item->valuestring)+1);
            }


            item=cJSON_GetObjectItem(root,"iswait");
            if(item == nullptr){
                allright=false;
            }
            else{
                v_mgmsg.iswait=item->valueint;
            }
            //"timecode":112233,"path":"hh","iswait":true,"groupid":0,"seq":4230368,"flag":0

            item=cJSON_GetObjectItem(root,"groupid");
            if(item == nullptr){
                allright=false;
            }
            else{
                v_mgmsg.groupid=static_cast<uint>(item->valuedouble);
            }

            item=cJSON_GetObjectItem(root,"seq");
            if(item == nullptr){
                allright=false;
            }
            else{
                v_mgmsg.seq=static_cast<uint>(item->valuedouble);
            }

            item=cJSON_GetObjectItem(root,"flag");
            if(item == nullptr){
                allright=false;
            }
            else{
                v_mgmsg.flag=static_cast<uint>(item->valuedouble);
            }
        }
        return v_mgmsg;
    }

    static MGMessage fromJson(const char* json){
        MGMessage v_mgmsg;
        cJSON* root=cJSON_Parse(json);
        if(nullptr != root){
            v_mgmsg = fromJsonObj(root);
            cJSON_free(root);
            root=nullptr;
        }

        return v_mgmsg;

    }



    static int MGMsgFromMsg(const Msg & v_msg,MGMessage &v_mgmsg){
        cJSON* root=cJSON_Parse(v_msg.msg_text);
        if(nullptr != root){
            bool allright=true;
            cJSON* item=cJSON_GetObjectItem(root,"timecode");
            if(item == nullptr){
                allright=false;
            }
            else{
                v_mgmsg.timecode=static_cast<uint>(item->valuedouble);
            }

            item=cJSON_GetObjectItem(root,"path");
            if(item == nullptr){
                allright=false;
            }
            else{
                memcpy(v_mgmsg.path,item->valuestring,strlen(item->valuestring)+1);
            }


            item=cJSON_GetObjectItem(root,"iswait");
            if(item == nullptr){
                allright=false;
            }
            else{
                v_mgmsg.iswait=item->valueint;
            }
            //"timecode":112233,"path":"hh","iswait":true,"groupid":0,"seq":4230368,"flag":0

            item=cJSON_GetObjectItem(root,"groupid");
            if(item == nullptr){
                allright=false;
            }
            else{
                v_mgmsg.groupid=static_cast<uint>(item->valuedouble);
            }

            item=cJSON_GetObjectItem(root,"seq");
            if(item == nullptr){
                allright=false;
            }
            else{
                v_mgmsg.seq=static_cast<uint>(item->valuedouble);
            }

            item=cJSON_GetObjectItem(root,"flag");
            if(item == nullptr){
                allright=false;
            }
            else{
                v_mgmsg.flag=static_cast<uint>(item->valuedouble);
            }


            cJSON_free(root);
            root=nullptr;
            if(true == allright){
                return 0;
            }
            else{
                return -1;
            }


        }
        return -1;

    }


    static int MsgFromMGMsg(const MGMessage &v_mgmsg,Msg &v_msg){
        cJSON* root=cJSON_CreateObject();
        if(nullptr != root){
            
            cJSON_AddNumberToObject(root,"timecode",v_mgmsg.timecode);
            cJSON_AddStringToObject(root,"path",v_mgmsg.path);
            cJSON_AddBoolToObject(root,"iswait",v_mgmsg.iswait);
            cJSON_AddNumberToObject(root,"groupid",v_mgmsg.groupid);
            cJSON_AddNumberToObject(root,"seq",v_mgmsg.seq);
            cJSON_AddNumberToObject(root,"flag",v_mgmsg.flag);

        }
        else{
            return -1;
        }

        char *json=cJSON_PrintUnformatted(root);
        cJSON_free(root);
        root=nullptr;

        if(nullptr !=json ){
            size_t len_json=strlen(json)+1;
            size_t len=MSG_BUFFER_LEN<len_json?MSG_BUFFER_LEN:len_json;
            memcpy(v_msg.msg_text,json,len);
            free(json);
            json=nullptr;
            return 0;
        }
        else{
            return  -1;
        }

    }

    static char* jsonString(const MGMessage &v_mgmsg){
        cJSON* root=cJSON_CreateObject();
        if(nullptr != root){

            cJSON_AddNumberToObject(root,"timecode",v_mgmsg.timecode);
            cJSON_AddStringToObject(root,"path",v_mgmsg.path);
            cJSON_AddBoolToObject(root,"iswait",v_mgmsg.iswait);
            cJSON_AddNumberToObject(root,"groupid",v_mgmsg.groupid);
            cJSON_AddNumberToObject(root,"seq",v_mgmsg.seq);
            cJSON_AddNumberToObject(root,"flag",v_mgmsg.flag);

        }
        else{
            return nullptr;
        }
        char *json=cJSON_PrintUnformatted(root);
        cJSON_free(root);
        root=nullptr;
        return json;
    }

    void print(){
        //        cout<<"path:"<<path<<endl;
        //        cout<<"iswait:"<<iswait<<endl;
        //        cout<<"timecode:"<<timecode<<endl;
        //        cout<<"groupid:"<<groupid<<endl;
        //        cout<<"seq:"<<seq<<endl;
        //        cout<<"flag:"<<flag<<endl;
        cout<<"groupid:"<<groupid
           <<" seq:"<<seq
          <<" path:"<<path
         <<" timecode:"<<timecode
        <<" iswait:"<<iswait
        <<endl;
    }

}MGMessage;

enum MGCHANNEL_TYPE{
    MGCHANNEL_TYPE_GENERATOR=0x1000,
    MGCHANNEL_TYPE_CONNECTOR,
    MGCHANNEL_TYPE_CGI
};


//imagegenerator 生成新数据后，添加到图片管理器
//customer  get data from callback

typedef void (*FUNC_MGCHANNEL_RECV)(MGMessage);

class MGChannel
{

public:
    MGChannel(MsgChannel_Mode v_mode,MGCHANNEL_TYPE v_type,void (*func_cb)(MGMessage ));
    ~MGChannel();

    /**
     * @brief addNewMGMessage SEND DATA
     * @param v_mgmsg
     * @return
     */
    int addNewMGMessage(MGMessage v_mgmsg);


private:
    MsgChannel_Mode __mode;
    MsgChannel *__msgchannel;

    static void getMsg(Msg v_msg, long v_type);
    /**
     * @brief __type 说明通道用途，有三种，msgid不同
     */
    MGCHANNEL_TYPE __type;
    static FUNC_MGCHANNEL_RECV g_mgfunc_callback_cgi;
    static FUNC_MGCHANNEL_RECV g_mgfunc_callback_connector;
    static FUNC_MGCHANNEL_RECV g_mgfunc_callback_generator;

    //    FUNC_MSGCHANNEL_RECV getmsg;
    //    static void *setReceiver(void* ppara);

#ifdef DEBUG_MGCHANNEL
    ofstream LogOut;
#endif



};

