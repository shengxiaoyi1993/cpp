#ifndef MYSQL_H
#define MYSQL_H

#include <iostream>
#include <string>
#include <vector>
#include <mysql/mysql.h>
#include <cstring>
#include <sstream>

using namespace std;

template<typename T>
inline string stringFromData(const T &v_val){
  string ret;
  stringstream convert;
  convert<<v_val;
  convert>>ret;
  return ret;
}


namespace mysql_uvss{
struct Condition{
  string _condi;
};

extern string g_host;
extern string g_username;
extern string g_password;
extern string g_database;
extern MYSQL g_conn;

bool mysql_init();
bool mysql_close();

int mysql_createtable(string v_tablename);

int mysql_insertData(const string &v_table, const string &v_dir, const string &v_big, const string &v_small,
                     const float *label, uint v_id );

//获取某一数据库文档中的所有数据项
MYSQL_RES* mysql_QueryOneEntry(const string & v_table );

//获取某一数据库文档中的所有数据项
MYSQL_RES* mysql_QueryOneEntry(const string & v_table,const string& v_condi );

int mysql_updateData_Description(const string &v_table, uint v_id,const string& v_desc );

//
string getSelectQuery(const string& v_target,
                      const string& v_tabel,
                      const vector<string>& v_list_condi);

/**
 * @brief mkLabelQuery 创建检索label值字符串
 * @param v_target
 * @param v_tabel
 * @param v_labels     输入必须为长为128的数组，且包含值
 * @return
 */
string mkLabelQuery(const string& v_target,
                    const string& v_tabel,
                    float* v_labels
                    );

//获取某一数据库文档中的所有数据项
MYSQL_RES* mysql_Query(const string& v_query );






}

#endif // MYSQL_H
