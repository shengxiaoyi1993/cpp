#ifndef MYSQLCPP_WARPPER_H
#define MYSQLCPP_WARPPER_H
#include <iostream>
#include <mysql-cppconn/mysql/jdbc.h>
#include <vector>


using namespace std;
using namespace sql;


class MySqlCppWarpper{
public:
  MySqlCppWarpper(const string&v_host,const string& v_user,const string& v_password);
  ~MySqlCppWarpper();
  /**
   * @brief setSchema set database ,otherwise some data option cannot be used
   * @param v_db
   */
  void setSchema(const string& v_db);

  bool isValid() const;

  //获取数据库列表
  vector<string> getDataBases() const;

  //获取某个数据库的列表
  vector<string> getTables(const string& v_db) const;

  //获取某数据库，某表的列名
  //前提是基本表要在数据库中
  vector<vector<string>> getTablePara(const string& v_db,const string& v_tb)const;
  //获取数据库中基本表的属性名
  vector<string> getTableProperty(const string& v_db,const string& v_tb)const;


  //创建数据库
  void createDataBase(const string& v_db);

  //删除数据库
  void deleteDataBase(const string& v_db);


  //创建基本表
  //创建基本表的同时，需要确定表的格式
  //v_format:(ID INT(11),name VARCHAR(25))
  void createTable(const string& v_db,const string& v_tb,const string& v_format);
  //删除基本表
  void deleteTable(const string& v_db,const string& v_tb);



  //增
  //v_value:一个数据条目的值,需要将要插入的基本表的格式相对应，如`(6,"sxy")`
  void insertDataEntry(const string& v_db,const string& v_tb,const string& v_value);

  //删
  //删除某个数据库数据表中的满足某一条件的所有条目
  void deleteDataEntry(const string& v_db,const string& v_tb,const string& v_condi);
  //改
  void updateDataEntry(const string& v_db,const string& v_tb,const string& v_target,const string& v_condi );
  //查
  vector<vector<string>> searchDataEntries(const string& v_db,const string& v_tb,const vector<string>& v_prop,const string& v_condi);

  //指定某张索引表进行检索
  //多张表的联合检索

  //索引操作
  //创建索引
  void createIndex(const string& v_db,const string& v_tb,const string& v_index,const string& v_props);
  //删除索引
  void deleteIndex(const string& v_db,const string& v_tb,const string& v_index);
  //输出索引中的所有内容
  vector<vector<string>> getContentInIndex(const string& v_db,const string& v_tb,const string& v_index,const vector<string>& v_prop);
  //获取某基本表中的所有索引
  vector<vector<string>> searchIndexInTable(const string& v_db,const string& v_tb,const vector<string>& v_prop);


  //  void setAutoCommit(bool v_flag);


private:
  //DBMMS url
  string _host;
  //user to login
  string _user;
  //password
  string _password;
  //database to connect
  string _database;

  bool _isConnectValid;
  bool _isDataBaseVaild;

  sql::Driver *driver;

  sql::Connection *con;

  //如果结果数量小可以使用这个接口，否则使用原数据接口，以节省时间
  vector<string> explainResult( ResultSet* v_res,const string& v_name) const;

  vector<vector<string>> explainResult( ResultSet* v_res,const vector<string>& v_nameS) const;


};




#endif
