#ifndef MYSQL_H
#define MYSQL_H

#include <iostream>
#include <string>
#include <vector>
#include <mysql/mysql.h>


using namespace std;

namespace mysql_uvss{

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
MYSQL_RES* mysql_QueryOneEntry(const string & v_table );


}

#endif // MYSQL_H
