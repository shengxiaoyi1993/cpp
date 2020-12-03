#include<iostream>
#include <iterator>
#include <mysql-cppconn/mysql/jdbc.h>
#include "mysqlcpp/mysqlcpp_warpper.h"
#include "mysqlcpp/mysqlcpp_tool.h"
#include "mysqlcpp/mysqlcpp_instance.h"
#include "../lib_copy/log/syslogger.h"

#define DBHOST "tcp://127.0.0.1:3306"
//#define DBHOST "192.168.1.100:3306"

#define USER "root"
#define PASSWORD "123456"
#define DATABASE "admin"

#define NUMOFFSET 100
#define COLNAME 200

using namespace std;
using namespace sql;

//连接至数据库管理系统
//查询连接状态
void test_ConnectToDBMS();

//查询所有的数据库
//创建数据库
//删除数据库
void test_DataBase();

//查询数据库中包含的表
//查询各个表的属性
//创建基本表
//删除基本表
void test_Table();

//增
//删
//改
//查
void test_DataEntryOperation();

//查询各个表的索引
//创建索引
//删除索引
//输出索引中的所有内容
//获取某基本表中的所有索引
void test_Index();


//测试根据配置文件创建数据库
void test_tools_createDB();

void test_instance_initData();



int main(int argc, const char *argv[]) {

  //  test_ConnectToDBMS();
    test_DataBase();
  //  test_Table();
  //  test_DataEntryOperation();
  //  test_Index();
//    test_tools_createDB();
//  test_instance_initData();

} // main()


//连接至数据库管理系统
//查询连接状态
void test_ConnectToDBMS(){


  cout<<"=====================主体部分 start====================="<<endl;
  cout<<"1. 数据库初始化"<<endl;
  MySqlCppWarpper sql(DBHOST,USER,PASSWORD);

  cout<<"2. 查询数据库的连接状态"<<endl;
  cout<<"连接状态：:"<<sql.isValid()<<endl;

  cout<<"3. 关闭与DBMS的连接"<<endl;
  //  MySqlCppWarpper 析构时即关闭与DBMS的连接

  cout<<"=====================主体部分 end====================="<<endl;


}

//查询所有的数据库
//创建数据库
//删除数据库
void test_DataBase(){
  cout<<"=====================初始化测试环境 start====================="<<endl;
  cout<<"1. 数据库初始化"<<endl;
  MySqlCppWarpper sql(DBHOST,USER,PASSWORD);

  cout<<"2. 查询数据库的连接状态"<<endl;
  cout<<"连接状态：:"<<sql.isValid()<<endl;
  cout<<endl;

  cout<<"=====================主体部分 start====================="<<endl;
  cout<<"1. 查询所有的数据库"<<endl;
  vector<string> dbs=sql.getDataBases();

  cout<<"DBS: ";
  copy(dbs.begin(),dbs.end(),ostream_iterator<string>(cout," | "));
  cout<<endl;


  cout<<"2. 创建数据库"<<endl;
  sql.createDataBase("db_0910");
  vector<string> dbs_create=sql.getDataBases();
  cout<<"after create DBS: ";
  copy(dbs_create.begin(),dbs_create.end(),ostream_iterator<string>(cout," | "));
  cout<<endl;

  cout<<"3. 删除数据库"<<endl;
  sql.deleteDataBase("db_0910");
  vector<string> dbs_delete=sql.getDataBases();
  cout<<"after delete DBS: ";
  copy(dbs_delete.begin(),dbs_delete.end(),ostream_iterator<string>(cout," | "));
  cout<<endl;

  cout<<"=====================主体部分 end====================="<<endl;

  cout<<"=====================还原数据库 end====================="<<endl;

  //  MySqlCppWarpper 析构时即关闭与DBMS的连接

}


//查询数据库中包含的表
//查询各个表的属性
//创建基本表
//删除基本表
void test_Table(){
  string name_db_test="db_0910";
  string name_tb_test="tb_1548";


  cout<<"=====================初始化测试环境 start====================="<<endl;
  cout<<"1. 数据库初始化"<<endl;
  MySqlCppWarpper sql(DBHOST,USER,PASSWORD);

  cout<<"2. 查询数据库的连接状态"<<endl;
  cout<<"连接状态：:"<<sql.isValid()<<endl;
  cout<<endl;

  cout<<"=====================初始化数据库 start====================="<<endl;
  cout<<"1. 查询所有的数据库"<<endl;
  vector<string> dbs=sql.getDataBases();

  cout<<"DBS: ";
  copy(dbs.begin(),dbs.end(),ostream_iterator<string>(cout," | "));
  cout<<endl;


  cout<<"2. 创建数据库"<<endl;
  sql.createDataBase(name_db_test);
  vector<string> dbs_create=sql.getDataBases();
  cout<<"after create DBS: ";
  copy(dbs_create.begin(),dbs_create.end(),ostream_iterator<string>(cout," | "));
  cout<<endl;

  cout<<"=====================主体部分 start====================="<<endl;

  cout<<"1. 查询数据库中包含的表"<<endl;
  vector<string> tables=sql.getTables(name_db_test);
  cout<<"Init TBS: ";
  copy(tables.begin(),tables.end(),ostream_iterator<string>(cout," | "));
  cout<<endl;

  cout<<"2. 查询各个表的属性"<<endl;
  for (auto item_table:tables) {
    vector<string> props_table=sql.getTableProperty(name_db_test,item_table);
    cout<<"props( "<<item_table<<"):";
    copy(props_table.begin(),props_table.end(),ostream_iterator<string>(cout," | "));
    cout<<endl;

    vector<vector<string>> para_table=sql.getTablePara(name_db_test,item_table);
    for(uint i=0;i<para_table.size();i++){
      cout<<i<<":";
      for(uint j=0;j<para_table[i].size();j++){
        cout<<para_table[i][j]<<" ";
      }
      cout<<endl;
    }
  }

  cout<<"3. 创建基本表"<<endl;
  sql.createTable(name_db_test,name_tb_test,"(ID INT(11),name VARCHAR(25))");
  vector<string> tables_aftercreate=sql.getTables(name_db_test);
  cout<<"after create TBS: ";
  copy(tables_aftercreate.begin(),tables_aftercreate.end(),ostream_iterator<string>(cout," | "));
  cout<<endl;
  vector<string> props_table_create=sql.getTableProperty(name_db_test,name_tb_test);
  cout<<"props( "<<name_tb_test<<"):";
  copy(props_table_create.begin(),props_table_create.end(),ostream_iterator<string>(cout," | "));
  cout<<endl;
  cout<<"\nTable params: \n";
  vector<vector<string>> para_table=sql.getTablePara(name_db_test,name_tb_test);
  for(uint i=0;i<para_table.size();i++){
    cout<<" "<<i<<":";
    for(uint j=0;j<para_table[i].size();j++){
      cout<<para_table[i][j]<<" ";
    }
    cout<<endl;
  }


  cout<<"4. 删除基本表"<<endl;
  sql.deleteTable(name_db_test,name_tb_test);
  vector<string> tables_afterdel=sql.getTables(name_db_test);
  cout<<"after del TBS: ";
  copy(tables_afterdel.begin(),tables_afterdel.end(),ostream_iterator<string>(cout," | "));
  cout<<endl;



  cout<<"=====================主体部分 end====================="<<endl;

  cout<<"3. 删除数据库"<<endl;
  sql.deleteDataBase(name_db_test);
  vector<string> dbs_delete=sql.getDataBases();
  cout<<"after delete DBS: ";
  copy(dbs_delete.begin(),dbs_delete.end(),ostream_iterator<string>(cout," | "));
  cout<<endl;

  cout<<"=====================还原数据库 end====================="<<endl;

  cout<<"=====================还原数据库 end====================="<<endl;

  //  MySqlCppWarpper 析构时即关闭与DBMS的连接

}


//增
//删
//改
//查
void test_DataEntryOperation(){
  string name_db_test="db_0910";
  string name_tb_test="tb_1548";
  string format_tb="(ID INT(11),name VARCHAR(25))";


  cout<<"=====================初始化测试环境 start====================="<<endl;
  cout<<"1. 数据库初始化"<<endl;
  MySqlCppWarpper sql(DBHOST,USER,PASSWORD);

  cout<<"2. 查询数据库的连接状态"<<endl;
  cout<<"连接状态：:"<<sql.isValid()<<endl;
  cout<<endl;

  cout<<"=====================初始化数据库 start====================="<<endl;
  cout<<"1. 查询所有的数据库"<<endl;
  vector<string> dbs=sql.getDataBases();

  cout<<"DBS: ";
  copy(dbs.begin(),dbs.end(),ostream_iterator<string>(cout," | "));
  cout<<endl;


  cout<<"2. 创建数据库"<<endl;
  sql.createDataBase(name_db_test);
  vector<string> dbs_create=sql.getDataBases();
  cout<<"after create DBS: ";
  copy(dbs_create.begin(),dbs_create.end(),ostream_iterator<string>(cout," | "));
  cout<<endl;

  cout<<"=====================初始化基本表 end====================="<<endl;


  cout<<"1. 查询数据库中包含的表"<<endl;
  vector<string> tables=sql.getTables(name_db_test);
  cout<<"Init TBS: ";
  copy(tables.begin(),tables.end(),ostream_iterator<string>(cout," | "));
  cout<<endl;

  cout<<"2. 查询各个表的属性"<<endl;
  for (auto item_table:tables) {
    vector<string> props_table=sql.getTableProperty(name_db_test,item_table);
    cout<<"props( "<<item_table<<"):";
    copy(props_table.begin(),props_table.end(),ostream_iterator<string>(cout," | "));
    cout<<endl;

    vector<vector<string>> para_table=sql.getTablePara(name_db_test,item_table);
    for(uint i=0;i<para_table.size();i++){
      cout<<i<<":";
      for(uint j=0;j<para_table[i].size();j++){
        cout<<para_table[i][j]<<" ";
      }
      cout<<endl;
    }
  }

  cout<<"3. 创建基本表"<<endl;
  sql.createTable(name_db_test,name_tb_test,format_tb);
  vector<string> tables_aftercreate=sql.getTables(name_db_test);
  cout<<"after create TBS: ";
  copy(tables_aftercreate.begin(),tables_aftercreate.end(),ostream_iterator<string>(cout," | "));
  cout<<endl;
  vector<string> props_table_create=sql.getTableProperty(name_db_test,name_tb_test);
  cout<<"props( "<<name_tb_test<<"):";
  copy(props_table_create.begin(),props_table_create.end(),ostream_iterator<string>(cout," | "));
  cout<<endl;
  cout<<"\nTable params: \n";
  vector<vector<string>> para_table=sql.getTablePara(name_db_test,name_tb_test);
  for(uint i=0;i<para_table.size();i++){
    cout<<" "<<i<<":";
    for(uint j=0;j<para_table[i].size();j++){
      cout<<para_table[i][j]<<" ";
    }
    cout<<endl;
  }
  cout<<"=====================主体部分 start====================="<<endl;

  vector<string> props={"ID","name"};
  cout<<"1. 查"<<endl;
  vector<vector<string>> values=sql.searchDataEntries(name_db_test,name_tb_test,props,"");
  for (uint i=0;i<values.size();i++) {
    cout<<i<<":";
    copy(values[i].begin(),values[i].end(),ostream_iterator<string>(cout," "));
    cout<<endl;
  }

  cout<<"2. 增"<<endl;
  sql.insertDataEntry(name_db_test,name_tb_test,"(999,\"sxy\")");
  cout<<"数据："<<endl;
  vector<vector<string>> values_insert=sql.searchDataEntries(name_db_test,name_tb_test,props,"");
  for (uint i=0;i<values_insert.size();i++) {
    cout<<i<<":";
    copy(values_insert[i].begin(),values_insert[i].end(),ostream_iterator<string>(cout," "));
    cout<<endl;
  }

  cout<<"3. 改"<<endl;
  sql.updateDataEntry(name_db_test,name_tb_test,"name='yxs'","name='sxy'");
  cout<<"数据："<<endl;
  vector<vector<string>> values_update=sql.searchDataEntries(name_db_test,name_tb_test,props,"");
  for (uint i=0;i<values_update.size();i++) {
    cout<<i<<":";
    copy(values_update[i].begin(),values_update[i].end(),ostream_iterator<string>(cout," "));
    cout<<endl;
  }

  cout<<"4. 删"<<endl;
  sql.deleteDataEntry(name_db_test,name_tb_test,"ID=999");
  cout<<"数据："<<endl;
  vector<vector<string>> values_del=sql.searchDataEntries(name_db_test,name_tb_test,props,"");
  for (uint i=0;i<values_del.size();i++) {
    cout<<i<<":";
    copy(values_del[i].begin(),values_del[i].end(),ostream_iterator<string>(cout," "));
    cout<<endl;
  }


  cout<<"=====================主体部分 end====================="<<endl;

  cout<<"=====================还原基本表 end====================="<<endl;

  cout<<"4. 删除基本表"<<endl;
  sql.deleteTable(name_db_test,name_tb_test);
  vector<string> tables_afterdel=sql.getTables(name_db_test);
  cout<<"after del TBS: ";
  copy(tables_afterdel.begin(),tables_afterdel.end(),ostream_iterator<string>(cout," | "));
  cout<<endl;


  cout<<"3. 删除数据库"<<endl;
  sql.deleteDataBase(name_db_test);
  vector<string> dbs_delete=sql.getDataBases();
  cout<<"after delete DBS: ";
  copy(dbs_delete.begin(),dbs_delete.end(),ostream_iterator<string>(cout," | "));
  cout<<endl;

  cout<<"=====================还原数据库 end====================="<<endl;

  cout<<"=====================还原数据库 end====================="<<endl;

  //  MySqlCppWarpper 析构时即关闭与DBMS的连接

}

//查询各个表的索引
//创建索引
//删除索引
//输出索引中的所有内容
//获取某基本表中的所有索引
void test_Index(){
  string name_db_test="db_0910";
  string name_tb_test="tb_1548";
  string format_tb="(ID INT(11),name VARCHAR(25))";


  cout<<"=====================初始化测试环境 start====================="<<endl;
  cout<<"1. 数据库初始化"<<endl;
  MySqlCppWarpper sql(DBHOST,USER,PASSWORD);

  cout<<"2. 查询数据库的连接状态"<<endl;
  cout<<"连接状态：:"<<sql.isValid()<<endl;
  cout<<endl;

  cout<<"=====================初始化数据库 start====================="<<endl;
  cout<<"1. 查询所有的数据库"<<endl;
  vector<string> dbs=sql.getDataBases();

  cout<<"DBS: ";
  copy(dbs.begin(),dbs.end(),ostream_iterator<string>(cout," | "));
  cout<<endl;


  cout<<"2. 创建数据库"<<endl;
  sql.createDataBase(name_db_test);
  vector<string> dbs_create=sql.getDataBases();
  cout<<"after create DBS: ";
  copy(dbs_create.begin(),dbs_create.end(),ostream_iterator<string>(cout," | "));
  cout<<endl;

  cout<<"=====================初始化基本表 end====================="<<endl;


  cout<<"1. 查询数据库中包含的表"<<endl;
  vector<string> tables=sql.getTables(name_db_test);
  cout<<"Init TBS: ";
  copy(tables.begin(),tables.end(),ostream_iterator<string>(cout," | "));
  cout<<endl;

  cout<<"2. 查询各个表的属性"<<endl;
  for (auto item_table:tables) {
    vector<string> props_table=sql.getTableProperty(name_db_test,item_table);
    cout<<"props( "<<item_table<<"):";
    copy(props_table.begin(),props_table.end(),ostream_iterator<string>(cout," | "));
    cout<<endl;

    vector<vector<string>> para_table=sql.getTablePara(name_db_test,item_table);
    for(uint i=0;i<para_table.size();i++){
      cout<<i<<":";
      for(uint j=0;j<para_table[i].size();j++){
        cout<<para_table[i][j]<<" ";
      }
      cout<<endl;
    }
  }

  cout<<"3. 创建基本表"<<endl;
  sql.createTable(name_db_test,name_tb_test,format_tb);
  vector<string> tables_aftercreate=sql.getTables(name_db_test);
  cout<<"after create TBS: ";
  copy(tables_aftercreate.begin(),tables_aftercreate.end(),ostream_iterator<string>(cout," | "));
  cout<<endl;
  vector<string> props_table_create=sql.getTableProperty(name_db_test,name_tb_test);
  cout<<"props( "<<name_tb_test<<"):";
  copy(props_table_create.begin(),props_table_create.end(),ostream_iterator<string>(cout," | "));
  cout<<endl;
  cout<<"\nTable params: \n";
  vector<vector<string>> para_table=sql.getTablePara(name_db_test,name_tb_test);
  for(uint i=0;i<para_table.size();i++){
    cout<<" "<<i<<":";
    for(uint j=0;j<para_table[i].size();j++){
      cout<<para_table[i][j]<<" ";
    }
    cout<<endl;
  }

  cout<<"=====================数据初始化 start====================="<<endl;


  vector<string> props={"ID","name"};
  cout<<"1. 查"<<endl;
  vector<vector<string>> values=sql.searchDataEntries(name_db_test,name_tb_test,props,"");
  for (uint i=0;i<values.size();i++) {
    cout<<i<<":";
    copy(values[i].begin(),values[i].end(),ostream_iterator<string>(cout," "));
    cout<<endl;
  }

  cout<<"2. 增"<<endl;
  sql.insertDataEntry(name_db_test,name_tb_test,"(999,\"sxy\")");
  cout<<"数据："<<endl;
  vector<vector<string>> values_insert=sql.searchDataEntries(name_db_test,name_tb_test,props,"");
  for (uint i=0;i<values_insert.size();i++) {
    cout<<i<<":";
    copy(values_insert[i].begin(),values_insert[i].end(),ostream_iterator<string>(cout," "));
    cout<<endl;
  }

  cout<<"=====================主体部分 start====================="<<endl;

  vector<string> props_index={"Key_name","Column_name"};
  string name_index_create="index_1701";
  bool bhave=false;


  //查询各个表的索引
  cout<<"1. 查询各个表的索引"<<endl;
  cout<<"索引列表:"<<endl;

  vector<vector<string>> indexes=sql.searchIndexInTable(name_db_test,name_tb_test,props_index);
  for (uint i=0;i<indexes.size();i++) {
    cout<<i<<":";
    copy(indexes[i].begin(),indexes[i].end(),ostream_iterator<string>(cout," "));
    if(find(indexes[i].begin(),indexes[i].end(),name_index_create)!=indexes[i].end() ){
      bhave=true;
    }
    cout<<endl;
  }

  cout<<"2. 创建索引"<<endl;

  if(!bhave){
    sql.createIndex(name_db_test,name_tb_test,name_index_create,"(ID,name)");
    cout<<"索引列表:"<<endl;
    vector<vector<string>> indexes_create=sql.searchIndexInTable(name_db_test,name_tb_test,props_index);
    for (uint i=0;i<indexes_create.size();i++) {
      cout<<i<<":";
      copy(indexes_create[i].begin(),indexes_create[i].end(),ostream_iterator<string>(cout," "));
      cout<<endl;
    }
  }


  cout<<"3. 输出索引中的所有内容"<<endl;
  vector<string> props_index_content={"ID"};
  cout<<"索引内容:"<<endl;
  vector<vector<string>> contents=sql.getContentInIndex(name_db_test,name_tb_test,name_index_create,props_index_content);
  for (uint i=0;i<contents.size();i++) {
    cout<<i<<":";
    for (uint j=0;j<contents[i].size();j++) {
      copy(contents[i].begin(),contents[i].end(),ostream_iterator<string>(cout," "));
    }
    cout<<endl;
  }


  cout<<"4. 删除索引"<<endl;
  sql.deleteIndex(name_db_test,name_tb_test,name_index_create);
  cout<<"索引列表:"<<endl;

  vector<vector<string>> indexes_del=sql.searchIndexInTable(name_db_test,name_tb_test,props_index);
  for (uint i=0;i<indexes_del.size();i++) {
    cout<<i<<":";
    for (uint j=0;j<indexes_del[i].size();j++) {
      copy(indexes_del[i].begin(),indexes_del[i].end(),ostream_iterator<string>(cout," "));
    }
    cout<<endl;
  }





  cout<<"=====================主体部分 end====================="<<endl;




  cout<<"3. 改"<<endl;
  sql.updateDataEntry(name_db_test,name_tb_test,"name='yxs'","name='sxy'");
  cout<<"数据："<<endl;
  vector<vector<string>> values_update=sql.searchDataEntries(name_db_test,name_tb_test,props,"");
  for (uint i=0;i<values_update.size();i++) {
    cout<<i<<":";
    copy(values_update[i].begin(),values_update[i].end(),ostream_iterator<string>(cout," "));
    cout<<endl;
  }

  cout<<"4. 删"<<endl;
  sql.deleteDataEntry(name_db_test,name_tb_test,"ID=999");
  cout<<"数据："<<endl;
  vector<vector<string>> values_del=sql.searchDataEntries(name_db_test,name_tb_test,props,"");
  for (uint i=0;i<values_del.size();i++) {
    cout<<i<<":";
    copy(values_del[i].begin(),values_del[i].end(),ostream_iterator<string>(cout," "));
    cout<<endl;
  }


  cout<<"=====================数据初始化 end====================="<<endl;


  cout<<"=====================还原基本表 end====================="<<endl;

  cout<<"4. 删除基本表"<<endl;
  sql.deleteTable(name_db_test,name_tb_test);
  vector<string> tables_afterdel=sql.getTables(name_db_test);
  cout<<"after del TBS: ";
  copy(tables_afterdel.begin(),tables_afterdel.end(),ostream_iterator<string>(cout," | "));
  cout<<endl;


  cout<<"3. 删除数据库"<<endl;
  sql.deleteDataBase(name_db_test);
  vector<string> dbs_delete=sql.getDataBases();
  cout<<"after delete DBS: ";
  copy(dbs_delete.begin(),dbs_delete.end(),ostream_iterator<string>(cout," | "));
  cout<<endl;

  cout<<"=====================还原数据库 end====================="<<endl;

  cout<<"=====================还原数据库 end====================="<<endl;

  //  MySqlCppWarpper 析构时即关闭与DBMS的连接
}


void test_tools_createDB(){

  try {



    cout<<"=====================1. 检测数据库初始状态 ====================="<<endl;
    MySqlCppWarpper mysqlwarpper(DBHOST,USER,PASSWORD);
    vector<string> dbs_before=mysqlwarpper.getDataBases();
    copy(dbs_before.begin(),dbs_before.end(),ostream_iterator<string>(cout," | "));
    cout<<endl;

    cout<<"=====================2. 根据配置文件创建数据库 ====================="<<endl;
    //根据配置文件创建数据库
    string spath_config="../../resources/db.config";
    int vflag=mysqlcpp_tool::createDataBaseAccordingToConfig(spath_config,DBHOST,USER,PASSWORD);


    cout<<"=====================检测创建结果 ====================="<<endl;
    vector<string> dbs_aftercreate=mysqlwarpper.getDataBases();
    cout<<"DBS: ";
    copy(dbs_aftercreate.begin(),dbs_aftercreate.end(),ostream_iterator<string>(cout," | "));
    cout<<endl;
    for(auto item:dbs_aftercreate){
      if(item != "DB_UVSS"){
        continue;
      }
      vector<string> ttbs=mysqlwarpper.getTables(item);
      cout<<"  DB_UVSS: ";
      copy(ttbs.begin(),ttbs.end(),ostream_iterator<string>(cout," | "));
      cout<<endl;
      for(auto item_tb:ttbs){
        vector<string> tpropertys=mysqlwarpper.getTableProperty("DB_UVSS",item_tb);
        cout<<"    "<<item_tb<<
              " Props: ";
        copy(tpropertys.begin(),tpropertys.end(),ostream_iterator<string>(cout," | "));
        cout<<endl;
      }
    }


//      cout<<"=====================3. 删除数据库 ====================="<<endl;
//      mysqlwarpper.deleteDataBase("DB_UVSS");

    cout<<"=====================检测创建结果 ====================="<<endl;
    vector<string> dbs_afterdel=mysqlwarpper.getDataBases();
    copy(dbs_afterdel.begin(),dbs_afterdel.end(),ostream_iterator<string>(cout," | "));
    cout<<endl;

  } catch (string v_msg) {
    cout<<"Throw Error:"<<v_msg<<endl;
  }

}




void test_instance_initData(){
  cout<<"=====================0. 导入文本中的config数据 ====================="<<endl;

  //导入config数据
  string spath_dict="../../resources/DICTIONARY.config";
  vector<mysqlcpp_instance::DictionaryEntry> rlist=mysqlcpp_instance::loadDictConfigFromFile(spath_dict);
//  copy(rlist.begin(),rlist.end(),ostream_iterator<mysqlcpp_instance::DictionaryEntry>(cout," \n"));


  cout<<"=====================1. 检测数据库初始状态 ====================="<<endl;
  MySqlCppWarpper mysqlwarpper(DBHOST,USER,PASSWORD);
  vector<string> dbs_before=mysqlwarpper.getDataBases();
  copy(dbs_before.begin(),dbs_before.end(),ostream_iterator<string>(cout," | "));
  cout<<endl;

  string v_db="DB_UVSS";
  string v_tb="T_DATA_DICTIONARY";

  //insert
  for(auto item:rlist){
    cout<<"insert:"<<item.toEntryString()<<endl;
    mysqlwarpper.insertDataEntry(v_db,v_tb,item.toEntryString());
  }

  //search
  cout<<"afterinsert:"<<endl;
  vector<string> v_props{"ENUM_ID","ENUM_TYPE"};
  vector<vector<string>> ret_search=mysqlwarpper.searchDataEntries(v_db,v_tb,v_props,"");
  for(auto item:ret_search){
    copy(item.begin(),item.end(),ostream_iterator<string>(cout," | "));
    cout<<endl;
  }
  //delete
  mysqlwarpper.deleteDataEntry(v_db,v_tb,"");

  vector<vector<string>> ret_afterdel=mysqlwarpper.searchDataEntries(v_db,v_tb,v_props,"");
  cout<<"afterdel:"<<endl;
  for(auto item:ret_afterdel){
    copy(item.begin(),item.end(),ostream_iterator<string>(cout," | "));
  }

}




