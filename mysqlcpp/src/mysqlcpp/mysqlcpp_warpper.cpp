#include "mysqlcpp_warpper.h"
#include <iterator>


MySqlCppWarpper::MySqlCppWarpper(const string&v_host,
                                 const string& v_user,
                                 const string& v_password){
  try {
    driver = get_driver_instance();
    con = driver -> connect(v_host, v_user, v_password);
    con->setAutoCommit(true);

  }  catch (SQLException &e) {
    cout << "ERROR: SQLException in " << __FILE__;
    cout << " (" << __func__<< ") on line " << __LINE__ << endl;
    cout << "ERROR: " << e.what();
    cout << " (MySQL error code: " << e.getErrorCode();
    cout << ", SQLState: " << e.getSQLState() << ")" << endl;
    if (e.getErrorCode() == 1047) {
      cout << "\nYour server does not seem to support Prepared Statements at all. ";
    }

  } catch (std::runtime_error &e) {
    cout << "ERROR: runtime_error in " << __FILE__<<__LINE__;
    cout << "ERROR: " << e.what() << endl;
  }
}



vector<string> MySqlCppWarpper::getDataBases() const{
  vector<string> v_list;
  PreparedStatement *prep_stmt=con -> prepareStatement ("SHOW DATABASES");
  prep_stmt->executeUpdate();
  ResultSet *rs=prep_stmt->getResultSet();
  return   explainResult(rs,"Database");

}


void MySqlCppWarpper::setSchema(const string& v_db){
  con->setSchema(v_db);
  _database=v_db;
}

void MySqlCppWarpper::createDataBase(const string& v_db){
  PreparedStatement *prep_stmt=con -> prepareStatement ("CREATE DATABASE IF NOT EXISTS "+v_db
                                                        );
  prep_stmt->executeUpdate();
}

void MySqlCppWarpper::deleteDataBase(const string& v_db){
  PreparedStatement *prep_stmt=con -> prepareStatement ("DROP DATABASE IF  EXISTS "+v_db
                                                        );
  prep_stmt->executeUpdate();
}

void MySqlCppWarpper::createTable(const string& v_db,const string& v_tb,const string& v_format){
  string query="CREATE TABLE IF NOT EXISTS "+v_db+"."+v_tb+" "+v_format;
  PreparedStatement* prep_stmt = con -> prepareStatement (query);
  prep_stmt -> executeUpdate();
}

void MySqlCppWarpper::deleteTable(const string& v_db,const string& v_tb){
  string query="DROP TABLE IF EXISTS "+v_db+"."+v_tb;
  PreparedStatement* prep_stmt = con -> prepareStatement (query);
  prep_stmt -> executeUpdate();
}

vector<string> MySqlCppWarpper::getTables(const string &v_db) const{
  vector<string> v_list;

  PreparedStatement *prep_stmt=con -> prepareStatement ("select TABLE_NAME  from information_schema.TABLES  where TABLE_SCHEMA = '"
                                                        +v_db+
                                                        "'");
  prep_stmt->executeUpdate();
  ResultSet *rs=prep_stmt->getResultSet();
  return   explainResult(rs,"TABLE_NAME");
}

vector<string> MySqlCppWarpper::getTableProperty(const string& v_db,const string& v_tb)const{

  PreparedStatement *prep_stmt=con -> prepareStatement ("DESC "
                                                        +v_db+"."+v_tb
                                                        );
  prep_stmt->executeUpdate();
  ResultSet *rs=prep_stmt->getResultSet();
  vector<string> Fields=explainResult(rs,"Field");
  return Fields;


}

void MySqlCppWarpper::insertDataEntry(const string& v_db,const string& v_tb,const string& v_value){
  PreparedStatement* prep_stmt = con -> prepareStatement ("INSERT INTO "
                                                          +v_db+"."+v_tb+
                                                          " VALUES "+v_value);
  prep_stmt->executeUpdate();

}

//删
//删除某个数据库数据表中的满足某一条件的所有条目
void MySqlCppWarpper::deleteDataEntry(const string& v_db,const string& v_tb,const string& v_condi){
  PreparedStatement* prep_stmt = con -> prepareStatement ("DELETE FROM "
                                                          +v_db+"."+v_tb+
                                                          " WHERE "+v_condi);
  prep_stmt->executeUpdate();

}

//改
void MySqlCppWarpper::updateDataEntry(const string& v_db,const string& v_tb,const string& v_target,const string& v_condi ){
  PreparedStatement* prep_stmt = con -> prepareStatement ("UPDATE "
                                                          +v_db+"."+v_tb+
                                                          " SET "
                                                          +v_target+
                                                          " WHERE "+v_condi
                                                          );
  prep_stmt -> executeUpdate();
}

//查
vector<vector<string>> MySqlCppWarpper::searchDataEntries(const string& v_db,const string& v_tb,const vector<string>& v_prop,const string& v_condi){

  string query;
  for (uint i=0;i<v_prop.size();i++) {
    if(i==0){
      query+=v_prop[i];
    }
    else{
      query=query+","+v_prop[i];
    }
  }

  if(v_condi != ""){
    query="SELECT "
        +query+
        " FROM  "
        +v_db+"."+v_tb
        +"WHERE "+v_condi;
  }
  else{
    query="SELECT "
        +query+
        " FROM  "
        +v_db+"."+v_tb;
  }

  PreparedStatement* prep_stmt = con -> prepareStatement (query);
  prep_stmt -> executeUpdate();
  ResultSet* res =prep_stmt->getResultSet();

  return explainResult(res,v_prop);

}



vector<vector<string>> MySqlCppWarpper::getTablePara(const string& v_db,const string& v_tb)const {
  //  vector<vector<string>> ;

  PreparedStatement *prep_stmt=con -> prepareStatement ("DESC "
                                                        +v_db+"."+v_tb
                                                        );
  prep_stmt->executeUpdate();
  ResultSet *rs=prep_stmt->getResultSet();
  vector<string> name=explainResult(rs,"Field");



  vector<string> table_desc={"Field","Type","Null","Key","Default","Extra"};
  vector<vector<string>> ret(table_desc.size(),vector<string>(name.size() ,""));
  for(uint i=0;i<table_desc.size();i++){
    PreparedStatement *prep_stmt_tmp=con -> prepareStatement ("DESC "
                                                              +v_db+"."+v_tb
                                                              );
    prep_stmt_tmp->executeUpdate();
    ResultSet *rs_tmp=prep_stmt_tmp->getResultSet();

    vector<string>  params=explainResult(rs_tmp,table_desc[i]);
//    cout<<"table_desc[i]:"<<table_desc[i]<<endl;

//    cout<<endl;
//    copy(params.begin(),params.end(),ostream_iterator<string>(cout," | "));
//    cout<<endl;

    for (uint j=0;j<params.size();j++) {
      ret[i][j]=params[j];
    }
  }
  return ret;
}

//v_props:`(ID INT(11),name VARCHAR(25))`
void MySqlCppWarpper::createIndex(const string& v_db,const string& v_tb,const string& v_index,const string& v_props){
  PreparedStatement* prep_stmt = con -> prepareStatement ("alter table "
                                                          +v_db+"."+v_tb+
                                                          " add index "
                                                          +v_index+v_props
                                                          );
  prep_stmt -> executeUpdate();
}

//删除索引
void MySqlCppWarpper::deleteIndex(const string& v_db,const string& v_tb,const string& v_index){
  PreparedStatement* prep_stmt = con -> prepareStatement ("alter table "
                                                          +v_db+"."+v_tb+
                                                          " DROP INDEX "+v_index
                                                          );
  prep_stmt -> executeUpdate();
}

//输出索引中的所有内容
vector<vector<string>> MySqlCppWarpper::getContentInIndex(const string& v_db,
                                                          const string& v_tb,
                                                          const string& v_index,
                                                          const vector<string>& v_prop){
  con->setSchema(v_db);
  PreparedStatement* prep_stmt = con -> prepareStatement ("SELECT * FROM `"
                                                          +v_tb+
                                                          "`  FORCE INDEX(`"
                                                          +v_index+
                                                          "`)"
                                                          );

  prep_stmt -> executeUpdate();
  ResultSet* res =prep_stmt->getResultSet();
  return  explainResult(res,v_prop);
}

//获取某基本表中的所有索引
vector<vector<string>> MySqlCppWarpper::searchIndexInTable(const string& v_db,const string& v_tb,const vector<string>& v_prop){
  PreparedStatement* prep_stmt = con -> prepareStatement ("SHOW INDEX FROM "
                                                          +v_db+"."+v_tb
                                                          );

  prep_stmt->executeUpdate();
  ResultSet *rs=prep_stmt->getResultSet();
  return  explainResult(rs,v_prop);
}




bool MySqlCppWarpper::isValid() const{
  return con->isValid();
}



MySqlCppWarpper::~MySqlCppWarpper(){
  con->close();
}




vector<string> MySqlCppWarpper::explainResult( ResultSet* v_res,const string& v_name) const{
  size_t rows= v_res -> rowsCount();
//  cout<<"rows:"<<rows<<endl;
  vector<string> v_list(rows);

  uint count=0;
  while (v_res->next()) {
    v_list[count]=v_res -> getString(v_name) ;
    count++;
  } // while
  return  v_list;
}


vector<vector<string>> MySqlCppWarpper::explainResult( ResultSet* v_res,const vector<string>& v_names) const{
  size_t rows= v_res -> rowsCount();
  vector<vector<string>> ret_lists(rows,vector<string>( v_names.size(),""));

  uint count=0;
  while (v_res->next()) {
    for (uint i=0;i<v_names.size();i++) {
      ret_lists[count][i]=v_res -> getString(v_names[i]) ;
//      cout<<ret_lists[count][i]<<endl;
    }
    count++;
  } // while

  return ret_lists;

}

