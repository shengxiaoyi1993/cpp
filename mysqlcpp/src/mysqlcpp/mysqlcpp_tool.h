#ifndef MYSQLCPP_TOOL_H
#define MYSQLCPP_TOOL_H

#include <iostream>
#include <string>
#include <vector>
#include "../../lib_copy/cjson/cJSON.h"

using namespace std;

namespace mysqlcpp_tool {

typedef struct Entry{
  string _field;
  string _type;
  string _null;
  string _key;
  string _default;
  string _extra;
  static Entry loadFromJsonString(const string& v_str);
  static Entry loadFromJsonObj(const cJSON *v_obj);
  static string stringFromStruct(const Entry &v_data);
  void print(int v_space);

}Entry;

typedef struct Table{
  string _name;
  vector<Entry> _entries;
  string _extra;

//  Table(const Table &);
  static Table loadFromJsonString(const string& v_str);
  static string stringFromStruct(const Table &v_data);
  static Table loadFromJsonObj(const cJSON *v_obj);
  void print(int v_space);

} Table;


typedef struct DBConfig{
  string _db;
  vector<Table> _tables;
  static DBConfig loadFromJsonString(const string& v_str);
  static string stringFromStruct(const DBConfig &v_data);
  void print(int v_space);
} DBConfig;


/**
 * @brief createDataBaseAccordingToConfig 根据数据库配置文件创建数据库
 * @param v_configpath 配置文件路径
 * @return    若返回0则创建成功
 */
int createDataBaseAccordingToConfig(const string& v_configpath, const string &v_host, const string &v_user, const string &v_password);

/**
 * @brief generateStatisticalTableOfDataBase 根据数据配置文件查询数据库统计数据
 *
 * @param v_configpath    配置文件路径
 * @param v_stat          统计文件保存路径
 * @return
 */
int generateStatisticalTableOfDataBase(const string& v_configpath,
                                       const string& v_stat);


}








#endif


