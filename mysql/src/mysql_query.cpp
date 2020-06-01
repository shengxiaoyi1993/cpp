#include <iostream>
#include <string>
#include <mysql/mysql.h>
#include "sha512.h"
#include "basic.h"

using namespace std;



void mysql_insertdata(uint v_num){
    MYSQL conn;
    int res;
    MYSQL_RES *result = NULL;
    MYSQL_FIELD *field = NULL;
    mysql_init(&conn);

    uint inputnum=v_num;

    //222555yq为数据库的进入密码，yg_sql为数据库名
    if(mysql_real_connect(&conn,"localhost","root","123456","test_db",0,NULL,CLIENT_FOUND_ROWS))
    {
        cout << "connect success!" << endl;


        //         res = mysql_query(&conn,"create database tb_search");

        //         if(res == 0){
        //             cout<<"succeed to create database"<<endl;
        //         }
        //         else{
        //             cout<<"failed to create database"<<endl;
        //         }

        //         res = mysql_query(&conn,"SHOW DATABASES");
        ////         res = mysql_query(&conn,"USE tb_search");

        //         if(res == 0){
        //             cout<<"succeed to create database"<<endl;
        //         }
        //          result = mysql_store_result(&conn);


        res = mysql_query(&conn,"CREATE TABLE tb_search("
                                "id INT(11) UNSIGNED PRIMARY KEY,"
                                " condi VARCHAR(128),"
                                "description VARCHAR(10))");
        if(res == 0){
            cout<<"succeed to create TABLE"<<endl;
        }
        else{
            cout<<"failed to create TABLE"<<endl;
        }

        for(uint i=0;i<inputnum;i++){

            string codition = getSha512ForUint(i);
            string insert_query="INSERT INTO tb_search VALUES("+integerToString(i)
                    +",'"+codition+"','hhh'"+")";
            mysql_query(&conn,insert_query.c_str());

            MYSQL_RES *res_query;
            MYSQL_ROW row;
            res_query = mysql_store_result(&conn);

            if (NULL == res_query)
            {
                cout << "mysql_store_result failure！" << endl;
            }

            // 重复读取行，并输出第一个字段的值，直到row为NULL

            while (row = mysql_fetch_row(res_query))
            {
                cout << row[0 ] << endl;
            }

            // 释放结果集
            mysql_free_result(res_query);
        }


        mysql_close(&conn);
    }
    else{
        cout<<"Failed to connect!"<<endl;
    }
}


void mysql_search(uint v_repeat,uint v_quentity){


    MYSQL conn;
    int res;
    MYSQL_RES *result = NULL;
    MYSQL_FIELD *field = NULL;
    mysql_init(&conn);

    vector<string> list= getNumFrom(10000,v_quentity);
    //    cout<<"list[0]:"<<list[0]<<endl;

    //222555yq为数据库的进入密码，yg_sql为数据库名
    if(mysql_real_connect(&conn,"127.0.0.1","root","123456","test_db",0,NULL,CLIENT_FOUND_ROWS))
    {
        cout << "connect success!" << endl;

        time_t record_time = time(0);
        for(uint i=0;i<v_repeat;i++){
            for(uint j=0;j<v_quentity;j++){
                string insert_query="SELECT * FROM tb_search WHERE condi='"+list[j]+"'";
                cout<<"insert_query:"<<insert_query<<endl;
                int flag_query=  mysql_query(&conn,insert_query.c_str());
                cout<<"flag_query:"<<flag_query<<endl;
                MYSQL_RES *res_query;
                MYSQL_ROW row;
                res_query = mysql_store_result(&conn);

                if (NULL == res_query)
                {
                    cout << "mysql_store_result failure！" << endl;
                    return;
                }

                time_t current_time = time(0);
                cout<<"ONE search:"<<current_time-record_time<<endl;

                // 重复读取行，并输出第一个字段的值，直到row为NULL

                while (row = mysql_fetch_row(res_query))

                {
                    cout << row[0 ] << endl;
                }

                // 释放结果集
                mysql_free_result(res_query);
            }
        }

        time_t current_time = time(0);
        cout<<"total_time:"<<current_time-record_time<<endl;
        mysql_close(&conn);

    }
    else{
        cout << "Fail to connect!" << endl;

    }
}


int main(int argc,char *argv[])
{
    mysql_search(1000,1000);

    return 0;
}
