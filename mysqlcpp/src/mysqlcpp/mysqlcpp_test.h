#ifndef MYSQLCPP_TEST_H
#define MYSQLCPP_TEST_H

#include<iostream>
#include <mysql-cppconn/mysql/jdbc.h>

using namespace std;
using namespace sql;

//打印所有行的指定列
void retrieve_data_and_print (ResultSet *rs, int type, int colidx, string colname) ;
void retrieve_dbmetadata_and_print (Connection *dbcon);
void retrieve_rsmetadata_and_print (ResultSet *rs);

//登陆至服务器
int test_connectToDatabase();

//创建数据库
//无法用prepareStatement进行变量的填充
int test_createDatabase();



//创建表

int test_createTable();

//测试基本表的操作增删改查
int test_DataOP();


//测试索引
int test_index();


int test_wholeProcess();


#endif;
