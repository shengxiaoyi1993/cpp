#ifndef MYSQL_INSTANCE_H
#define MYSQL_INSTANCE_H


#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <sstream>


/// 本项目在已知数据库配置文件地条件下运行
/// 本项目用于利用某些配置文件将数据进行实例化，某些数据结构是对具体的数据库或基本表进行构造


using namespace std;

template<class T>
inline string stringfromT(const T& v_val){
  stringstream textdev;
  textdev<<v_val;
  string ret;
  textdev>>ret;
  return ret;
}


namespace mysqlcpp_instance
{
//typedef map<int,string>  DictionaryConfig;


typedef  struct DictionaryEntry{
  string _key;
  unsigned int    _id;
  DictionaryEntry(const string&v_key,const unsigned int &v_id):
    _key(v_key),_id(v_id)
  {
  }
  DictionaryEntry():
    _key(""),_id(0)
  {
  }

  string toEntryString(){
    string ret;
    ret+="(";
    ret+=stringfromT(_id+1);
    ret+=",\""+string(_key)+"\"";
    ret+=")";
    return ret;

  }

  DictionaryEntry& operator=(const DictionaryEntry& cls)
  {
      // 避免自赋值
      if (this != &cls)
      {
        _key=cls._key;
        _id=cls._id;
      }
      return *this;
  }

  friend ostream & operator<<( ostream & os,const DictionaryEntry & c);

}DictionaryEntry;

inline ostream & operator<<( ostream & os,const DictionaryEntry & c)
{
  os << c._id << ":" << c._key ; //以"a+bi"的形式输出
  return os;
}

///从本地文件中载入数据
/// 将这些数据插入到数据字典中
vector<DictionaryEntry>
loadDictConfigFromFile(const string & v_file);

/// 用配置文件的数据将数据字典基本表初始化
void initDictionaryWithConfig(const string &v_host,
                              const string &v_user,
                              const string &v_password,
                              const string& v_db,
                              const string& v_tb,
                              const string & v_file);


///该接口用于创建数据及初始化数据字典基本表
void createDataBaseWithConfigAndInit(const string& v_configpath,
                                     const string& v_dictpath,
                                     const string &v_host,
                                     const string &v_user,
                                     const string &v_password);

};

#endif // MYSQL_INSTANCE_H
