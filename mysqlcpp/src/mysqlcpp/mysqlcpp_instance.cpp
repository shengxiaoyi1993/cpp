
/*
 * 本项目用于创建具体的数据库并初始化一些基本表，这些都是基于一定结构的本地配置文件
 * 若配置文件中数据的基本表属性发生变化需要修改本文中相应的接口实现方式
 *
 *
 *
 *
*/



#include "mysqlcpp_instance.h"
#include <iostream>
#include <fstream>
#include "../../lib_copy/cjson/cJSON.h"
#include "mysqlcpp_tool.h"
#include "mysqlcpp_warpper.h"






using namespace std;

namespace mysqlcpp_instance
{


///实现过程
/// 载入字符串
/// 字符串转化成json解构体
/// 根据特定地形式进行转化
vector<DictionaryEntry>
 loadDictConfigFromFile(const string & v_file){
  vector<DictionaryEntry>   rlist;
  //load all data from file
  fstream vfile(v_file,ios_base::in);
  std::string vdata((std::istreambuf_iterator<char>(vfile)),
                    std::istreambuf_iterator<char>());
  cJSON* root=cJSON_Parse(vdata.c_str());
  if(root != nullptr){
    cJSON* array=cJSON_GetObjectItem(root,"dict");
    if(array != nullptr||cJSON_IsArray(array)){
      int size_array=cJSON_GetArraySize(array);
      rlist.resize(size_array);
      for(int i=0;i<size_array;i++){
        cJSON* item=cJSON_GetArrayItem(array,i);
        if(item != nullptr){
          cJSON* subitem_key=cJSON_GetObjectItem(item,"key");
          cJSON* subitem_value=cJSON_GetObjectItem(item,"value");

          if(subitem_key!=nullptr&&subitem_value!=nullptr){
            rlist[i]._id=subitem_value->valueint;
            rlist[i]._key=subitem_key->valuestring;
          }
        }
      }
    }
    else{
      throw string(__func__)+"Error: cannot find dict!";
    }

  }
  else{
    throw string(__func__)+"Error: string cannot convert to json!";
  }
  return rlist;

}


///1.获取数据连接实例
/// 删除原有数据字典的内容
/// 将导入字典的配置文件
/// 将字典数据逐条保存到字典基本表中
void initDictionaryWithConfig(const string &v_host,
                              const string &v_user,
                              const string &v_password,
                              const string& v_db,
                              const string& v_tb,
                              const string & v_file){
  vector<mysqlcpp_instance::DictionaryEntry> rlist=mysqlcpp_instance::loadDictConfigFromFile(v_file);
  MySqlCppWarpper mysqlwarpper(v_host,v_user,v_password);
  mysqlwarpper.deleteDataEntry(v_db,v_tb,"");

  //insert
  for(auto item:rlist){
    cout<<"insert:"<<item.toEntryString()<<endl;
    mysqlwarpper.insertDataEntry(v_db,v_tb,item.toEntryString());
  }

}

/// 删除原数据库
/// 根据配置文件创建数据库
/// 初始化数据字典基本表
void createDataBaseWithConfigAndInit(const string& v_configpath,
                                     const string &v_dictpath,
                                     const string &v_host,
                                     const string &v_user,
                                     const string &v_password){
  MySqlCppWarpper mysqcon(v_host,v_user,v_password);
  mysqcon.deleteDataBase("DB_UVSS");
  int vflag=mysqlcpp_tool::createDataBaseAccordingToConfig(v_configpath,v_host,v_user,v_password);
  initDictionaryWithConfig(v_host,v_user,v_password,"DB_UVSS","T_DATA_DICTIONARY",v_dictpath);

}






};
