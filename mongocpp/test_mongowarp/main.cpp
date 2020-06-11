#include "bs_cxx_driver_export.h"
#include <iostream>
#include "../../mysql/src/sha512.h"
#include "../../mysql/src/basic.h"
#include "../lib/cjsonobject/CJsonObject.hpp"
#include <sstream>
#include <sys/time.h>



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


int mongo_insertdata(uint v_quentity,string v_tablename){
    mongo::Init();

    for(uint i=0;i<v_quentity;i++){
        string tmp=getSha512ForUint(i);
        string query_insert="{\"id\":"+integerToString(i)+",\"condi\":\""
                +tmp+"\",\"description\":\"hhh\""
                     "}";

        char* pid_insert= Add((char*)query_insert.c_str(),(char*)v_tablename.c_str());
        cout<<"pid_insert:"<<pid_insert<<endl;
    }

    mongo::Cleanup();
    return 0;

}

long mongo_batchinsertdata(uint v_low,uint v_high,string v_tablename){
    mongo::Init();

    vector<string> list=getRangeNumList(v_low,v_high);

    struct timeval tv_record;
    struct timezone tz_record;

    struct timeval tv_current;
    struct timezone tz_current;
    gettimeofday(&tv_record,&tz_record);


    for(uint i=0;i<list.size();i++){
        string query_insert="{\"id\":"+integerToString(i)+",\"condi\":\""
                +list[i]+"\",\"description\":\"hhh\""
                         "}";
        char* pid_insert= Add((char*)query_insert.c_str(),(char*)v_tablename.c_str());
        //        cout<<"pid_insert:"<<pid_insert<<endl;
    }

    gettimeofday(&tv_current,&tz_current);


    mongo::Cleanup();

    return (tv_current.tv_sec-tv_record.tv_sec)*1000000
            +tv_current.tv_usec-tv_record.tv_usec;
}

long mongo_batchdeletedata(uint v_low,uint v_high,string v_tablename){
    mongo::Init();

    vector<string> list=getRangeNumList(v_low,v_high);

    struct timeval tv_record;
    struct timezone tz_record;

    struct timeval tv_current;
    struct timezone tz_current;
    gettimeofday(&tv_record,&tz_record);


    for(uint i=0;i<list.size();i++){
        //        string query_insert="{\"id\":"+integerToString(i)+",\"condi\":\""
        //                +list[i]+"\",\"description\":\"hhh\""
        //                         "}";
        //        char* pid_insert= Add((char*)query_insert.c_str(),(char*)v_tablename.c_str());


        string query_tmp="{\"condi\":\""+list[i]+
                "\"}";

        char* result=FindOne((char*)query_tmp.c_str(),(char*)v_tablename.c_str());
        if(result!= nullptr){
            neb::CJsonObject obj;
            obj.Parse(string(result));
            string v_id;
            obj.Get("_id",v_id);

            DeleteById((char*)v_id.c_str(),(char*)v_tablename.c_str());
        }
    }

    gettimeofday(&tv_current,&tz_current);


    mongo::Cleanup();

    return (tv_current.tv_sec-tv_record.tv_sec)*1000000
            +tv_current.tv_usec-tv_record.tv_usec;
}


long mongo_searchdata(uint v_repeat,uint v_quentity,uint v_total,string v_tablename){

    mongo::Init();
    //    char ptable[]="tb_search_450k";
    vector<string> list= getNumFrom(v_total,v_quentity);

    struct timeval tv_record;
    struct timezone tz_record;

    struct timeval tv_current;
    struct timezone tz_current;

    gettimeofday(&tv_record,&tz_record);

    for(uint i=0;i<v_repeat;i++){
        for(uint j=0;j<v_quentity;j++){

            string query_tmp="{\"condi\":\""+list[j]+
                    "\"}";

            char* result=FindMany((char*)query_tmp.c_str(),0,0,(char*)v_tablename.c_str());
            //                        cout<<"result:"<<result<<endl;
            //            time_t current_time = time(0);
            //            cout<<"ONE search:"<<current_time-record_time<<endl;
        }
    }

    gettimeofday(&tv_current,&tz_current);

    mongo::Cleanup();

    return (tv_current.tv_sec-tv_record.tv_sec)*1000000
            +tv_current.tv_usec-tv_record.tv_usec;

}

int main(int argc, char *argv[])
{
    //    api_test();
    //    return 0;

    stringstream logcout("mongotest.log");

    vector<uint> list_total;
    vector<string> list_table;


    {

        list_total.push_back(10000);
        list_table.push_back("tb_10k");

        list_total.push_back(100000);
        list_table.push_back("tb_100k");

        list_total.push_back(500000);
        list_table.push_back("tb_500k");

        list_total.push_back(1000000);
        list_table.push_back("tb_1m");

        list_total.push_back(5000000);
        list_table.push_back("tb_5m");

        //    list_total.push_back(10000000);
        //    list_table.push_back("tb_10m");

        //    list_total.push_back(50000000);
        //    list_table.push_back("tb_50m");

        //    list_total.push_back(100000000);
        //    list_table.push_back("tb_100m");

    }


    {
        //    //   insert
        //    for(uint ntab=0;ntab<list_table.size();ntab++){
        //        int flag_insert=mongo_insertdata(list_total[ntab],list_table[ntab]);
        //        if(flag_insert == 0){
        //            cout<<list_table[ntab]<<" create succeed"<<endl;
        //        }
        //        else{
        //            cout<<list_table[ntab]<<" create failed"<<endl;
        //        }
        //    }
    }


    {

        //    //search
        //    uint times = 1;
        //    uint quentity=1000;
        //    cout<<"| total |"<<" times |"<<" quentity |"<<" cost |"<<endl;
        //    logcout<<"| total |"<<" times |"<<" quentity |"<<" cost |"<<endl;
        //    for(uint ntab=0;ntab<list_table.size();ntab++){
        //        long time= mongo_searchdata(times,quentity,list_total[ntab],list_table[ntab]);
        //        cout<<"| "<<list_total[ntab]<<" | "<<times<<" | "<<quentity<<" | "<<time<<" | "<<endl;
        //        logcout<<"| "<<list_total[ntab]<<" | "<<times<<" | "<<quentity<<" | "<<time<<" | "<<endl;
        //        time= mongo_searchdata(times,quentity,list_total[ntab],list_table[ntab]);
        //        cout<<"| "<<list_total[ntab]<<" | "<<times<<" | "<<quentity<<" | "<<time<<" | "<<endl;
        //        logcout<<"| "<<list_total[ntab]<<" | "<<times<<" | "<<quentity<<" | "<<time<<" | "<<endl;
        //        time= mongo_searchdata(times,quentity,list_total[ntab],list_table[ntab]);
        //        cout<<"| "<<list_total[ntab]<<" | "<<times<<" | "<<quentity<<" | "<<time<<" | "<<endl;
        //        logcout<<"| "<<list_total[ntab]<<" | "<<times<<" | "<<quentity<<" | "<<time<<" | "<<endl;
        //        cout<<endl;
        //    }
    }


    {
        //insert test
        uint v_low = 10000001;
        uint v_high = 10010000;
//        cout.width(20);
        cout<<"| v_low |";
        cout<<" v_high |";
        cout<<" table |";
        cout<<"cost |"<<endl;
        for(uint ntab=0;ntab<list_table.size();ntab++){
            long time= mongo_batchinsertdata(v_low,v_high,list_table[ntab]);
//            long time= mongo_batchdeletedata(v_low,v_high,list_table[ntab]);
            cout<<"| "<<v_low<<" |";
            cout<<v_high<<" |";
            cout<<list_table[ntab]<<" |";
            cout<<time<<" |"<<endl;
        }
    }


    return 0;
}
