#include "bs_cxx_driver_export.h"
#include <iostream>
#include "../../mysql/src/sha512.h"
#include "../../mysql/src/basic.h"
#include <sstream>


using namespace std;




void api_test(){

    mongo::Init();
    //    char * newid=NewObjectId();
    //    cout<<"newid:"<<newid<<endl;
    //    char * newid1=NewObjectId();
    //    cout<<"newid1:"<<newid1<<endl;
    //    char * newid2=NewObjectId();
    //    cout<<"newid2:"<<newid2<<endl;

    char ptable[]="sxy";
    char* pdata_intable=FindAll(ptable);
    cout<<"pdata_intable:"<<pdata_intable<<endl;
    free(pdata_intable);
    pdata_intable=nullptr;


    char pdoc0[]="{\"name\":\"sxy\"}";
    char* pid_insert= Add(pdoc0,ptable);
    cout<<"pid_insert:"<<pid_insert<<endl;

    pdata_intable=FindAll(ptable);
    cout<<"pdata_intable:"<<pdata_intable<<endl;
    free(pdata_intable);
    pdata_intable=nullptr;

    //    cout<<">>find by id:"<<endl;
    //    char * pid_find=FindOneById(pid_insert ,  ptable);
    //    cout<<"pid_find:"<<pid_find<<endl;

    //    cout<<">>find by conition:"<<endl;
    //    char con[]="{\"name\":\"sxy\"}";
    //    char * pid_findbycon=FindOne(con ,  ptable);
    //    cout<<"pid_findbycon:"<<pid_findbycon<<endl;

    //    cout<<">>findmany by conition:"<<endl;
    //    char* pmany=FindMany(con,1,20,ptable);
    //    cout<<"pmany:"<<pmany<<endl;

    //    cout<<">>DeleteById:"<<endl;
    //    bool flag_detlete=DeleteById(pid_insert,ptable);
    //    cout<<"flag_detlete:"<<flag_detlete<<endl;

    //    cout<<">>FindAll:"<<endl;
    //    pdata_intable=FindAll(ptable);
    //    cout<<"pdata_intable:"<<pdata_intable<<endl;
    //    free(pdata_intable);
    //    pdata_intable=nullptr;

    //    char doc_new[]="{\"name\":\"lli\"}";
    //    bool flag_update=UpdateById(pid_insert,doc_new,ptable);
    //    cout<<"flag_update:"<<flag_update<<endl;

    //    cout<<">>FindAll:"<<endl;
    //    pdata_intable=FindAll(ptable);
    //    cout<<"pdata_intable:"<<pdata_intable<<endl;
    //    free(pdata_intable);
    //    pdata_intable=nullptr;

    char con[]="{\"name\":\"sxy\"}";
    cout<<">>Count:"<<endl;
    int cout_coll=Count(con,ptable);
    cout<<"cout_coll:"<<cout_coll<<endl;


    mongo::Cleanup();
}


void mongo_insertdata(uint v_quentity){
    mongo::Init();
    char ptable[]="tb_search_450k";

    for(uint i=0;i<v_quentity;i++){
        string tmp=getSha512ForUint(i);
        string query_insert="{\"id\":"+integerToString(i)+",\"condi\":\""
                +tmp+"\",\"description\":\"hhh\""
                     "}";

        char* pid_insert= Add((char*)query_insert.c_str(),ptable);
        //        cout<<"pid_insert:"<<query_insert<<endl;

    }

    //    char pdoc0[]="{\"name\":\"sxy\"}";
    //    char* pid_insert= Add(pdoc0,ptable);
    //    cout<<"pid_insert:"<<pid_insert<<endl;

    mongo::Cleanup();

}



void mongo_searchdata(uint v_repeat,uint v_quentity){

    mongo::Init();
    char ptable[]="tb_search_450k";
    vector<string> list= getNumFrom(10000,v_quentity);
    time_t record_time = time(0);


    for(uint i=0;i<v_repeat;i++){
        for(uint j=0;j<v_quentity;j++){
//            stringstream  logcout("/home/sxy/Github/cpp/mongocpp/build-test_mongowarp-Desktop_Qt_5_9_7_GCC_64bit-Debug/mongo_search.log");

            string query_tmp="{\"condi\":\""+list[j]+
                    "\"}";

//            logcout<<"query_tmp:"<<query_tmp<<endl;
            cout<<"query_tmp:"<<query_tmp<<endl;


            char* result=FindMany((char*)query_tmp.c_str(),0,0,ptable);
            cout<<"result:"<<result<<endl;
            time_t current_time = time(0);
            cout<<"ONE search:"<<current_time-record_time<<endl;
        }
    }


    mongo::Cleanup();

}

int main(int argc, char *argv[])
{
    //    api_test();
//        mongo_insertdata(4361168);
    mongo_searchdata(1000,1000);
    return 0;
}
