#include "mysql.h"
#include <mysql/mysql.h>
#include <sstream>
#include <iomanip>


namespace mysql_uvss{

string g_host="127.0.0.1";
string g_username="root";
string g_password="123456";
string g_database="uvss";
MYSQL g_conn;

std::string integerToString(int num){
  stringstream ss;
  ss.clear();
  ss.str("");
  string tmps;
  ss<<num;
  ss>>tmps;
  return tmps;
}
std::string integerToString(float num){
  stringstream ss;
  ss.clear();
  ss.str("");
  string tmps;
  ss<<setprecision(8);
  ss<<num;
  ss>>tmps;
  return tmps;
}
std::string integerToString(uint num){
  stringstream ss;
  ss.clear();
  ss.str("");
  string tmps;
  ss<<num;
  ss>>tmps;
  return tmps;
}


bool mysql_init(){
  mysql_init(&g_conn);
  if(mysql_real_connect(&g_conn,g_host.c_str(),g_username.c_str(),
                        g_password.c_str(),g_database.c_str(),0,
                        NULL,CLIENT_FOUND_ROWS))
  {
    return true;
  }
  return false;
}

bool mysql_close(){
  mysql_close(&g_conn);

}

int mysql_createtable(string v_tablename){
  string query="CREATE TABLE IF NOT EXISTS "
      +v_tablename+
      "("
      "id INT(11) UNSIGNED NOT NULL PRIMARY KEY AUTO_INCREMENT,"
      "dir CHAR(128),"
      "big CHAR(128),"
      "small CHAR(128),";

  for(int i=0;i<128;i++){
    query+="label"+integerToString(i)+" FLOAT(8),";
  }
  query+="description VARCHAR(10))";
  //    cout<<"query:"<<query<<endl;
  int res = mysql_query(&g_conn,query.c_str());
  return res;
}



int mysql_insertData(const string & v_table,const string &v_dir,
                     const string &v_big,const string &v_small,
                     const float *label,uint v_id ){

  string insert_query="INSERT INTO "
      +v_table+
      " VALUES("+integerToString(v_id)
      +",'"+v_dir+"'"+
      +",'"+v_big+"'"+
      + ",'"+v_small+"'";

  for(uint i=0;i<128;i++){
    insert_query+=","+integerToString(label[i]);
  }
  insert_query+=",'kkkk')";
  //    cout<<"insert_query:"<<insert_query<<endl;

  mysql_query(&g_conn,insert_query.c_str());
  return 0;

}
//UPDATE tb_uvsslabel  set description='津E*M05K74'  WHERE id=1;
int mysql_updateData_Description(const string &v_table, uint v_id,const string& v_desc){
  //  //show variables like 'character_set_%';
  //  string char_set_query="show variables like 'character_set_%';";
  //  mysql_query(&g_conn,"set names 'latin1'");
  //  MYSQL_RES *result_char;
  //  result_char = mysql_store_result(&g_conn);

  string insert_query="UPDATE "
      +v_table+" SET description='"+v_desc+"' WHERE id="+integerToString(v_id)+";";
  mysql_query(&g_conn,"set names 'utf8'");

  cout<<"insert_query:"<<insert_query<<endl;

  return mysql_query(&g_conn,insert_query.c_str());

}




MYSQL_RES* mysql_QueryOneEntry(const string & v_table ){

  string insert_query="SELECT * FROM "+v_table+"";

  //    cout<<"insert_query:"<<insert_query<<endl;
  mysql_query(&g_conn,"set names 'utf8'");
  mysql_query(&g_conn,insert_query.c_str());

  //	printf("%d\n", numFields);

  MYSQL_RES *result;
  result = mysql_store_result(&g_conn);

  if(result == nullptr){
    cout<<"error"<<endl;
    return nullptr;
  }
  else{
    return result;
  }

}

MYSQL_RES* mysql_Query(const string& v_query ){
  mysql_query(&g_conn,"set names 'utf8'");
  mysql_query(&g_conn,v_query.c_str());

  //	printf("%d\n", numFields);

  MYSQL_RES *result;
  result = mysql_store_result(&g_conn);

  if(result == nullptr){
    cout<<"error"<<endl;
    return nullptr;
  }
  else{
    return result;
  }
}




MYSQL_RES* mysql_QueryOneEntry(const string & v_table,const string& v_condi ){
  string insert_query="SELECT * FROM "+v_table+" where description='"+v_condi+"'";
  mysql_query(&g_conn,"set names 'utf8'");

  mysql_query(&g_conn,insert_query.c_str());

  //	printf("%d\n", numFields);

  MYSQL_RES *result;
  result = mysql_store_result(&g_conn);

  if(result == nullptr){
    cout<<"error"<<endl;
    return nullptr;
  }
  else{
    return result;
  }

}





string getSelectQuery(const string& v_target,
                      const string& v_tabel,
                      const vector<string>& v_list_condi){
  string ret="SELECT "+v_target+" FROM "+v_tabel+" ";
  for(uint i=0;i<v_list_condi.size();i++){
    ret+=v_list_condi[i];
  }
  ret+=";";
  return ret;

}

string mkLabelQuery(const string& v_target,
                    const string& v_tabel,
                    float* v_labels
                    ){
  vector<string> list_condi;
  for(uint i=0;i<128;i++){
    string tmpcondi;
    if(i == 0){
      tmpcondi="WHERE label"+stringFromData<uint>(i)+">"+stringFromData<float>(v_labels[i]-0.1)
          +" AND "+"label"+stringFromData<uint>(i)+"<"+stringFromData<float>(v_labels[i]+0.1) ;
    }
    else{
      tmpcondi=" AND label"+stringFromData<uint>(i)+">"+stringFromData<float>(v_labels[i]-0.1)
          +" AND "+"label"+stringFromData<uint>(i)+"<"+stringFromData<float>(v_labels[i]+0.1) ;
    }
    list_condi.push_back(tmpcondi);

  }

  return getSelectQuery(v_target,v_tabel,list_condi);


}









}
