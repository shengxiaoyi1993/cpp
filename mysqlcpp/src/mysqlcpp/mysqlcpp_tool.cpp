

#include "mysqlcpp_tool.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include "mysqlcpp_warpper.h"
#include "../../lib_copy/cjson/cJSON.h"

using namespace std;


namespace mysqlcpp_tool {

string getSpace(int v_num){
  string vret;
  for(int i=0;i<v_num;i++){
    vret+=" ";
  }
  return vret;
}

void DBConfig::print(int v_space){
  cout<<getSpace(v_space)<<"_db:"<<_db<<endl;
  cout<<getSpace(v_space)<<"_tables:"<<_tables.size()<<endl;
  for (uint i=0;i<_tables.size();i++) {
    _tables[i].print(v_space+1);
  }
}

void Table::print(int v_space){
  cout<<getSpace(v_space)<<"_name:"<<_name<<endl;
  cout<<getSpace(v_space)<<"_entries:"<<_entries.size()<<endl;
  for (uint i=0;i<_entries.size();i++) {
    _entries[i].print(v_space+1);
  }
}

void Entry::print(int v_space){
  cout<<getSpace(v_space+1)<<_field<<" "<<_type<<" "
     <<_null<<" "<<_key<<" "
    <<_default<<" "<<_extra<<" "
   <<endl;
}


DBConfig DBConfig::loadFromJsonString(const string& v_str){
  DBConfig v_ret;
  cJSON* proot=cJSON_Parse(v_str.c_str());
  if(proot != nullptr){
    cout<<"str:"<<cJSON_Print(proot);
    cJSON *obj_item=cJSON_GetObjectItem(proot,"db");
    if(obj_item != nullptr){
      v_ret._db=obj_item->valuestring;
    }
    else{
      throw string(__func__)+"Error: db isnull!";
    }//end of db


    obj_item=cJSON_GetObjectItem(proot,"tbs");
    if(obj_item != nullptr){
      if (cJSON_IsArray(obj_item)) {
        int vsize=cJSON_GetArraySize(obj_item);
        v_ret._tables.resize(static_cast<unsigned int>(vsize));
        for(int i=0;i<vsize;i++){
          cJSON *subitem=cJSON_GetArrayItem(obj_item,i);
          if(subitem != nullptr){
            v_ret._tables[static_cast<unsigned int>(i)]=Table::loadFromJsonObj(subitem);
          }
          else{
            throw string(__func__)+"Error: subitem isnull!";
          }

        }
      }
    }
    else{
      throw string(__func__)+"Error: tbs isnull!";
    }//end of tbs

    cJSON_free(proot);
    proot=nullptr;
  }
  else{
    throw string(__func__)+"Error: config not match!";
  }//end of proot

  return v_ret;
}



Table Table::loadFromJsonObj(const cJSON *v_obj){
  Table vret;
  if(v_obj != nullptr){

    cJSON *obj_item=cJSON_GetObjectItem(v_obj,"tb");
    if(obj_item != nullptr){
      vret._name=obj_item->valuestring;
    }
    else{
      throw string(__func__)+"Error: tb is null!";
    }//end of tb

    obj_item=cJSON_GetObjectItem(v_obj,"entries");
    if(obj_item != nullptr){
      if(cJSON_IsArray(obj_item)){
        int vsize=cJSON_GetArraySize(obj_item);
        vret._entries.resize(static_cast<uint>(vsize));
        for(int i=0;i<vsize;i++){
          cJSON *subitem=cJSON_GetArrayItem(obj_item,i);
          if(subitem != nullptr){
            vret._entries[static_cast<unsigned int>(i)]=Entry::loadFromJsonObj(subitem);
          }
          else{
            throw string(__func__)+"Error: subitem is null!";
          }//end of subitem
        }
      }
    }
    else{
      throw string(__func__)+"Error: entries is null!";
    }//end of entries

  }
  else{
    throw string(__func__)+"Error: v_obj is null!";

  }//end of v_obj
  return vret;

}


Entry Entry::loadFromJsonObj(const cJSON *v_obj){
  Entry vret;
  if(v_obj != nullptr){

    cJSON *obj_item=cJSON_GetObjectItem(v_obj,"Field");
    if(obj_item != nullptr){
      vret._field=obj_item->valuestring;
    }
    else{
      throw string(__func__)+"Error: Field is null!";
    }//end of Field

    obj_item=cJSON_GetObjectItem(v_obj,"Type");
    if(obj_item != nullptr){
      vret._type=obj_item->valuestring;
    }
    else{
      throw string(__func__)+"Error: Type is null!";
    }//end of Type

    obj_item=cJSON_GetObjectItem(v_obj,"Null");
    if(obj_item != nullptr){
      vret._null=obj_item->valuestring;
    }
    else{
      throw string(__func__)+"Error: Null is null!";
    }//end of Null

    obj_item=cJSON_GetObjectItem(v_obj,"Key");
    if(obj_item != nullptr){
      vret._key=obj_item->valuestring;
    }
    else{
      throw string(__func__)+"Error: Key is null!";
    }//end of Key

    obj_item=cJSON_GetObjectItem(v_obj,"Default");
    if(obj_item != nullptr){
      vret._default=obj_item->valuestring;
    }
    else{
      throw string(__func__)+"Error: Default is null!";
    }//end of Default

    obj_item=cJSON_GetObjectItem(v_obj,"Extra");
    if(obj_item != nullptr){
      vret._extra=obj_item->valuestring;
    }
    else{
      throw string(__func__)+"Error: Extra is null!";
    }//end of Extra


  }
  else{
    throw string(__func__)+"Error: v_obj is null!";

  }//end of v_obj
  return vret;


}





static string formatEntry(const Entry &v_data){
  string ret;
  ret=v_data._field+" "
      +v_data._type+" "
      +v_data._null+" "
      +v_data._key+" "
//      +v_data._default+" "
      +v_data._extra;
  return ret;

}


//读入文件
//解析JSON字符串到一个数据结构
//连接至DBMS
//建立数据库
//建立各个表
//建立各个表之间的关系，建立表间索引等
//测试数据库

int createDataBaseAccordingToConfig(const string& v_configpath,
                                    const string&v_host,
                                    const string& v_user,
                                    const string& v_password){

  //load all data from file
  fstream vfile(v_configpath,ios_base::in);
  std::string vdata((std::istreambuf_iterator<char>(vfile)),
                    std::istreambuf_iterator<char>());
  DBConfig vconfig =DBConfig::loadFromJsonString(vdata);
//  vconfig.print(0);

  //连接至DBMS
  MySqlCppWarpper sql(v_host,v_user,v_password);

  //创建数据库
  sql.createDataBase(vconfig._db);

  for(uint i=0;i<vconfig._tables.size();i++){
    vconfig._tables[i];
    string formatstring;
    formatstring+="(";
    for (uint j=0;j<vconfig._tables[i]._entries.size();j++) {
      if(j==0){
        formatstring+=formatEntry(vconfig._tables[i]._entries[j]);
      }
      else{
        formatstring+=","+formatEntry(vconfig._tables[i]._entries[j]);
      }
    }
    formatstring+=")";
    cout<<"table "<<i<<" :"<<formatstring<<endl;
//    sql.createTable(vconfig._db,vconfig._tables[i]._name,formatstring);


  }








//  throw string(__func__)+"Error: not complete!";
}

























































}


