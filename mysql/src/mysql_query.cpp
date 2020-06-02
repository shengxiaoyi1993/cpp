#include <iostream>
#include <string>
#include <mysql/mysql.h>
#include "sha512.h"
#include "basic.h"
#include <sys/time.h>


using namespace std;



const string name_db="test_db";
const string pw_db="123456";
const string user_db="root";
const string ip_db="127.0.0.1";




int mysql_createtable(string v_tablename){
    MYSQL conn;
    int res;
    MYSQL_RES *result = NULL;
    MYSQL_FIELD *field = NULL;
    mysql_init(&conn);
    if(mysql_real_connect(&conn,"127.0.0.1","root","123456","test_db",0,NULL,CLIENT_FOUND_ROWS))
    {

        string query="CREATE TABLE IF NOT EXISTS "
                +v_tablename+
                "("
                "id INT(11) UNSIGNED PRIMARY KEY,"
                " condi VARCHAR(128),"
                "description VARCHAR(10))";

        res = mysql_query(&conn,query.c_str());
        if(res == 0){
            cout<<"succeed to create"<<endl;
        }
        else{
            cout<<"failed to create"<<endl;
        }
        return res;

    }
    return -1;

}


int mysql_insertdata(uint v_num,string v_tablename){
    MYSQL conn;
    int res;
    MYSQL_RES *result = NULL;
    MYSQL_FIELD *field = NULL;
    mysql_init(&conn);

    uint inputnum=v_num;

    if(mysql_real_connect(&conn,"127.0.0.1","root","123456","test_db",0,NULL,CLIENT_FOUND_ROWS))
    {
        for(uint i=0;i<inputnum;i++){
            string codition = getSha512ForUint(i);
            string insert_query="INSERT INTO "
                    +v_tablename+
                    " VALUES("+integerToString(i)
                    +",'"+codition+"','hhh'"+")";
            mysql_query(&conn,insert_query.c_str());
        }
        mysql_close(&conn);
        return 0;
    }
    else{
        return -1;
    }
}


int mysql_cleantable(string v_tablename){

    MYSQL conn;
    mysql_init(&conn);

    if(mysql_real_connect(&conn,"127.0.0.1","root","123456","test_db",0,NULL,CLIENT_FOUND_ROWS))
    {
        string clean_query="TRUNCATE "+v_tablename;
        int flag_query=  mysql_query(&conn,clean_query.c_str());
        return flag_query;
    }
    else {
        return -1;
    }

}

int  mysql_search(uint v_repeat,uint v_quentity,uint v_total,string v_tablename){

    struct timeval tv_record;
    struct timezone tz_record;

    struct timeval tv_current;
    struct timezone tz_current;



    MYSQL conn;
    mysql_init(&conn);
    vector<string> list= getNumFrom(v_total,v_quentity);


    if(mysql_real_connect(&conn,"127.0.0.1","root","123456","test_db",0,NULL,CLIENT_FOUND_ROWS))
    {

        gettimeofday(&tv_record,&tz_record);
        for(uint i=0;i<v_repeat;i++){
            for(uint j=0;j<v_quentity;j++){
                string insert_query="SELECT * FROM "
                        +v_tablename+
                        " WHERE condi='"+list[j]+"'";
                int flag_query=  mysql_query(&conn,insert_query.c_str());

                MYSQL_RES *res_query;
                MYSQL_ROW row;
                res_query = mysql_store_result(&conn);

                if (NULL == res_query)
                {
                    continue;
                    //                    cout << "mysql_store_result failure！" << endl;
                }
                else{
                    //                    unsigned int num_fields;
                    //                    unsigned int i;
                    //                    num_fields = mysql_num_fields(res_query);
                    //                    while ((row = mysql_fetch_row(res_query)))
                    //                    {
                    //                        unsigned long *lengths;
                    //                        lengths = mysql_fetch_lengths(res_query);
                    //                        for(i = 0; i < num_fields; i++)
                    //                        {
                    //                            printf("[%.*s] ", (int) lengths[i], row[i] ? row[i] : "NULL");
                    //                        }
                    //                        printf("\n");
                    //                    }

                    // 释放结果集
                    mysql_free_result(res_query);
                }


            }
        }

        //        time_t current_time = time(0);
        //        cout<<"total_time:"<<current_time-record_time<<endl;
        gettimeofday(&tv_current,&tz_current);
        //        cout<<"total time:"<<(tv_current.tv_sec-tv_record.tv_sec)*1000000
        //              +tv_current.tv_usec-tv_record.tv_usec<<endl;


        mysql_close(&conn);
        return (tv_current.tv_sec-tv_record.tv_sec)*1000000
                +tv_current.tv_usec-tv_record.tv_usec;
    }
    else{
        cout << "Fail to connect!" << endl;

    }
    return -1;
}



int main(int argc,char *argv[])
{
    vector<uint> list_total;
    vector<string> list_table;
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




    //   insert
    for(uint ntab=0;ntab<list_table.size();ntab++){
        int createflag = mysql_createtable(list_table[ntab]);
        if(createflag != 0 ){
            continue;
        }
        mysql_cleantable(list_table[ntab]);
        int flag_insert=mysql_insertdata(list_total[ntab],list_table[ntab]);
        if(flag_insert == 0){
            cout<<list_table[ntab]<<" create succeed"<<endl;
        }
        else{
            cout<<list_table[ntab]<<" create failed"<<endl;

        }

    }


//    //search
//    uint times = 1;
//    uint quentity=1000;
//    cout<<"| total |"<<" times |"<<" quentity |"<<" cost |"<<endl;
//    for(uint ntab=0;ntab<list_table.size();ntab++){
//        int time= mysql_search(times,quentity,list_total[ntab],list_table[ntab]);
//        cout<<"| "<<list_total[ntab]<<" | "<<times<<" | "<<quentity<<" | "<<time<<" | "<<endl;
//        time= mysql_search(times,quentity,list_total[ntab],list_table[ntab]);
//        cout<<"| "<<list_total[ntab]<<" | "<<times<<" | "<<quentity<<" | "<<time<<" | "<<endl;
//        time= mysql_search(times,quentity,list_total[ntab],list_table[ntab]);
//        cout<<"| "<<list_total[ntab]<<" | "<<times<<" | "<<quentity<<" | "<<time<<" | "<<endl;
//        cout<<endl;
//    }



    return 0;
}
