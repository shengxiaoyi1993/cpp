#include "mysqlcpp_test.h"
#include<iostream>
#include <mysql-cppconn/mysql/jdbc.h>

using namespace std;
using namespace sql;


#define NUMOFFSET 100
#define COLNAME 200


// const string url="127.0.0.1";
const string url="192.168.1.66";

const string user="root";
const string password="123456";
const string database="mysqlcpp_test";

void retrieve_data_and_print (ResultSet *rs, int type, int colidx, string colname) {

  /* retrieve the row count in the result set */
  cout << "\nRetrieved " << rs -> rowsCount() << " row(s)." << endl;

  cout << "\n" <<colname<< endl;
  cout << "--------" << endl;

  /* fetch the data : retrieve all the rows in the result set */
  while (rs->next()) {
    if (type == NUMOFFSET) {
      cout << rs -> getString(colidx) << endl;
    } else if (type == COLNAME) {
      cout << rs -> getString(colname) << endl;
    } // if-else
  } // while

  cout << endl;

} // retrieve_data_and_print()



void retrieve_dbmetadata_and_print (Connection *dbcon) {

  if (dbcon -> isClosed()) {
    throw runtime_error("DatabaseMetaData FAILURE - database connection closed");
  }

  cout << "\nDatabase Metadata" << endl;
  cout << "-----------------" << endl;

  cout << boolalpha;

  /* The following commented statement won't work with Connector/C++ 1.0.5 and later */
  //auto_ptr < DatabaseMetaData > dbcon_meta (dbcon -> getMetaData());

  DatabaseMetaData *dbcon_meta = dbcon -> getMetaData();

  cout << "Database Product Name: " << dbcon_meta -> getDatabaseProductName() << endl;
  cout << "Database Product Version: " << dbcon_meta -> getDatabaseProductVersion() << endl;
  cout << "Database User Name: " << dbcon_meta -> getUserName() << endl << endl;

  cout << "Driver name: " << dbcon_meta -> getDriverName() << endl;
  cout << "Driver version: " << dbcon_meta -> getDriverVersion() << endl << endl;

  cout << "Database in Read-Only Mode?: " << dbcon_meta -> isReadOnly() << endl;
  cout << "Supports Transactions?: " << dbcon_meta -> supportsTransactions() << endl;
  cout << "Supports DML Transactions only?: " << dbcon_meta -> supportsDataManipulationTransactionsOnly() << endl;
  cout << "Supports Batch Updates?: " << dbcon_meta -> supportsBatchUpdates() << endl;
  cout << "Supports Outer Joins?: " << dbcon_meta -> supportsOuterJoins() << endl;
  cout << "Supports Multiple Transactions?: " << dbcon_meta -> supportsMultipleTransactions() << endl;
  cout << "Supports Named Parameters?: " << dbcon_meta -> supportsNamedParameters() << endl;
  cout << "Supports Statement Pooling?: " << dbcon_meta -> supportsStatementPooling() << endl;
  cout << "Supports Stored Procedures?: " << dbcon_meta -> supportsStoredProcedures() << endl;
  cout << "Supports Union?: " << dbcon_meta -> supportsUnion() << endl << endl;

  cout << "Maximum Connections: " << dbcon_meta -> getMaxConnections() << endl;
  cout << "Maximum Columns per Table: " << dbcon_meta -> getMaxColumnsInTable() << endl;
  cout << "Maximum Columns per Index: " << dbcon_meta -> getMaxColumnsInIndex() << endl;
  cout << "Maximum Row Size per Table: " << dbcon_meta -> getMaxRowSize() << " bytes" << endl;

  cout << "\nDatabase schemas: " << endl;

  auto_ptr < ResultSet > rs ( dbcon_meta -> getSchemas());

  cout << "\nTotal number of schemas = " << rs -> rowsCount() << endl;
  cout << endl;

  int row = 1;

  while (rs -> next()) {
    cout << "\t" << row << ". " << rs -> getString("TABLE_SCHEM") << endl;
    ++row;
  } // while

  cout << endl << endl;

} // retrieve_dbmetadata_and_print()



void retrieve_rsmetadata_and_print (ResultSet *rs) {

  if (rs -> rowsCount() == 0) {
    throw runtime_error("ResultSetMetaData FAILURE - no records in the result set");
  }

  cout << "ResultSet Metadata" << endl;
  cout << "------------------" << endl;

  /* The following commented statement won't work with Connector/C++ 1.0.5 and later */
  //auto_ptr < ResultSetMetaData > res_meta ( rs -> getMetaData() );

  ResultSetMetaData *res_meta = rs -> getMetaData();

  int numcols = res_meta -> getColumnCount();
  cout << "\nNumber of columns in the result set = " << numcols << endl << endl;

  cout.width(20);
  cout << "Column Name/Label";
  cout.width(20);
  cout << "Column Type";
  cout.width(20);
  cout << "Column Size" ;
  cout.width(20);
  cout << "Charset" ;
  cout.width(20);
  cout << "Collation" ;
  cout<< endl;

  for (int i = 0; i < numcols; ++i) {
    cout.width(20);
    cout << res_meta -> getColumnLabel (i+1);
    cout.width(20);
    cout << res_meta -> getColumnTypeName (i+1);
    cout.width(20);
    cout << res_meta -> getColumnDisplaySize (i+1)  ;
    cout.width(20);
    cout << res_meta -> getColumnCharset (i+1)  ;
    cout.width(20);
    cout << res_meta -> getColumnCollation (i+1)  ;

    cout<< endl<< endl;
  }

  cout << "\nColumn \"" << res_meta -> getColumnLabel(1);
  cout << "\" belongs to the Table: \"" << res_meta -> getTableName(1);
  cout << "\" which belongs to the Schema: \"" << res_meta -> getSchemaName(1) << "\"" << endl << endl;

} // retrieve_rsmetadata_and_print()

//连接至服务器
//检查数据库的连接状态
//没有查到有监控数据库连接状态的回调函数
int test_connectToDatabase(){
  Driver *driver;
  Connection *con;
  Statement *stmt;
  ResultSet *res;
  PreparedStatement *prep_stmt;
  Savepoint *savept;

  try {
    driver = get_driver_instance();
    con = driver -> connect(url, user, password);
    //    con->
    cout<<"isValid:"<<con->isValid()<<endl;
    cout<<"isClosed:"<<con->isClosed()<<endl;

    retrieve_dbmetadata_and_print (con);

    con->close();
    cout<<"isValid:"<<con->isValid()<<endl;
    cout<<"isClosed:"<<con->isClosed()<<endl;

  } catch (SQLException &e) {
    cout << "ERROR: SQLException in " << __FILE__;
    cout << " (" << __func__<< ") on line " << __LINE__ << endl;
    cout << "ERROR: " << e.what();
    cout << " (MySQL error code: " << e.getErrorCode();
    cout << ", SQLState: " << e.getSQLState() << ")" << endl;

    if (e.getErrorCode() == 1047) {
      /*
            Error: 1047 SQLSTATE: 08S01 (ER_UNKNOWN_COM_ERROR)
            Message: Unknown command
            */
      cout << "\nYour server does not seem to support Prepared Statements at all. ";
      cout << "Perhaps MYSQL < 4.1?" << endl;
    }

    return EXIT_FAILURE;
  } catch (std::runtime_error &e) {

    cout << "ERROR: runtime_error in " << __FILE__;
    cout << " (" << __func__ << ") on line " << __LINE__ << endl;
    cout << "ERROR: " << e.what() << endl;

    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}


int test_createDatabase(){
  Driver *driver;
  Connection *con;
  Statement *stmt;
  ResultSet *res;
  PreparedStatement *prep_stmt;
  Savepoint *savept;

  try {
    driver = get_driver_instance();
    con = driver -> connect(url, user, password);
    retrieve_dbmetadata_and_print (con);
    con->setAutoCommit(false);
    //    con -> setSchema(database);

    //    stmt = con -> createStatement();
    //    prep_stmt = con -> prepareStatement ("CREATE DATABASE tb_create IF NOT EXISTS tb_create");

    prep_stmt = con -> prepareStatement ("CREATE DATABASE IF NOT EXISTS db_create");
    int updatecount = prep_stmt->executeUpdate();
    cout<<"updatecount:"<<updatecount<<endl;

    retrieve_dbmetadata_and_print (con);
    prep_stmt = con -> prepareStatement ("DROP DATABASE IF  EXISTS db_create");
    updatecount = prep_stmt->executeUpdate();
    cout<<"updatecount:"<<updatecount<<endl;

    retrieve_dbmetadata_and_print (con);

    con->close();


  } catch (SQLException &e) {
    cout << "ERROR: SQLException in " << __FILE__;
    cout << " (" << __func__<< ") on line " << __LINE__ << endl;
    cout << "ERROR: " << e.what();
    cout << " (MySQL error code: " << e.getErrorCode();
    cout << ", SQLState: " << e.getSQLState() << ")" << endl;

    if (e.getErrorCode() == 1047) {
      /*
            Error: 1047 SQLSTATE: 08S01 (ER_UNKNOWN_COM_ERROR)
            Message: Unknown command
            */
      cout << "\nYour server does not seem to support Prepared Statements at all. ";
      cout << "Perhaps MYSQL < 4.1?" << endl;
    }

    return EXIT_FAILURE;
  } catch (std::runtime_error &e) {

    cout << "ERROR: runtime_error in " << __FILE__;
    cout << " (" << __func__ << ") on line " << __LINE__ << endl;
    cout << "ERROR: " << e.what() << endl;

    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}


//检测某一数据库中的数据表
//创建数据表
//检测数据表
//删除数据表列表
//检测数据表
int test_createTable(){
  Driver *driver;
  Connection *con;
  Statement *stmt;
  ResultSet *res;
  PreparedStatement *prep_stmt;
  Savepoint *savept;
  string name_tb=database;

  try {
    driver = get_driver_instance();
    con = driver -> connect(url, user, password);
    retrieve_dbmetadata_and_print (con);
    con->setAutoCommit(false);
    con -> setSchema(name_tb);

    cout<<"[before]: TABLES"<<endl;
    stmt = con -> createStatement();
    res = stmt->executeQuery("SHOW TABLES");
    retrieve_rsmetadata_and_print (res);
    res = NULL;

    //[before:create]
    res = stmt->executeQuery("select TABLE_NAME  from information_schema.TABLES  where TABLE_SCHEMA = 'mysqlcpp_test' ");
    retrieve_data_and_print(res,COLNAME,0,"TABLE_NAME");

    //create
    prep_stmt = con -> prepareStatement ("CREATE TABLE IF NOT EXISTS tb_test (ID INT(11))");
    prep_stmt -> executeUpdate();

    cout<<"[after create]: "<<endl;
    res = stmt->executeQuery("select TABLE_NAME  from information_schema.TABLES  where TABLE_SCHEMA = 'mysqlcpp_test' ");
    retrieve_data_and_print(res,COLNAME,0,"TABLE_NAME");


    //    //rm
    prep_stmt = con -> prepareStatement ("DROP TABLE IF EXISTS tb_test");
    prep_stmt -> executeUpdate();
    retrieve_data_and_print(res,COLNAME,0,"TABLE_NAME");



    cout<<"[after drop]: "<<endl;
    //    res = stmt->executeQuery("SHOW TABLES");
    res = stmt->executeQuery("select TABLE_NAME  from information_schema.TABLES  where TABLE_SCHEMA = 'mysqlcpp_test' ");
    retrieve_data_and_print(res,COLNAME,0,"TABLE_NAME");


    con->close();


  } catch (SQLException &e) {
    cout << "ERROR: SQLException in " << __FILE__;
    cout << " (" << __func__<< ") on line " << __LINE__ << endl;
    cout << "ERROR: " << e.what();
    cout << " (MySQL error code: " << e.getErrorCode();
    cout << ", SQLState: " << e.getSQLState() << ")" << endl;

    if (e.getErrorCode() == 1047) {
      /*
            Error: 1047 SQLSTATE: 08S01 (ER_UNKNOWN_COM_ERROR)
            Message: Unknown command
            */
      cout << "\nYour server does not seem to support Prepared Statements at all. ";
      cout << "Perhaps MYSQL < 4.1?" << endl;
    }

    return EXIT_FAILURE;
  } catch (std::runtime_error &e) {

    cout << "ERROR: runtime_error in " << __FILE__;
    cout << " (" << __func__ << ") on line " << __LINE__ << endl;
    cout << "ERROR: " << e.what() << endl;

    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}



int test_wholeProcess(){

  Driver *driver;
  Connection *con;
  Statement *stmt;
  ResultSet *res;
  PreparedStatement *prep_stmt;
  Savepoint *savept;

  int updatecount = 0;

  /* initiate url, user, password and database variables */
  //    string url(argc >= 2 ? argv[1] : DBHOST);
  //    const string user(argc >= 3 ? argv[2] : USER);
  //    const string password(argc >= 4 ? argv[3] : PASSWORD);
  //    const string database(argc >= 5 ? argv[4] : DATABASE);
  string url="127.0.0.1";
  const string user="root";
  const string password="123456";
  const string database="db_test";


  try {


    driver = get_driver_instance();

    /* create a database connection using the Driver */
    con = driver -> connect(url, user, password);

    /* alternate syntax using auto_ptr to create the db connection */
    //auto_ptr  con (driver -> connect(url, user, password));

    /* turn off the autocommit */
    con -> setAutoCommit(0);

    cout << "\nDatabase connection\'s autocommit mode = " << con -> getAutoCommit() << endl;

    /* select appropriate database schema */
    con -> setSchema(database);

    /* retrieve and display the database metadata */
    retrieve_dbmetadata_and_print (con);

    /* create a statement object */
    stmt = con -> createStatement();

    cout << "Executing the Query: \"SELECT * FROM tb_test\" .." << endl;

    /* run a query which returns exactly one result set */
    res = stmt -> executeQuery ("SELECT * FROM tb_empl");

    cout << "Retrieving the result set .." << endl;

    /* retrieve the data from the result set and display on stdout */
    retrieve_data_and_print (res, COLNAME, 1, string("deptId"));

    /* retrieve and display the result set metadata */
    retrieve_rsmetadata_and_print (res);

    cout << "Demonstrating Prepared Statements .. " << endl << endl;

    /* insert couple of rows of data into City table using Prepared Statements */
    prep_stmt = con -> prepareStatement ("INSERT INTO tb_empl (name) VALUES (?)");

    cout << "\tInserting \"London, UK\" into the table, City .." << endl;

    prep_stmt -> setString (1, "London, UK");
    updatecount = prep_stmt -> executeUpdate();

    cout << "\tCreating a save point \"SAVEPT1\" .." << endl;
    savept = con -> setSavepoint ("SAVEPT1");

    cout << "\tInserting \"Paris, France\" into the table, City .." << endl;

    cout<<"before execute"<<endl;
    res = NULL;
    res = stmt -> executeQuery ("SELECT * FROM tb_empl");
    retrieve_data_and_print (res, COLNAME, 1, string ("name"));


    prep_stmt -> setString (1, "Paris, France");
    updatecount = prep_stmt -> executeUpdate();

    cout << "\tRolling back until the last save point \"SAVEPT1\" .." << endl;
    con -> rollback (savept);
    con -> releaseSavepoint (savept);

    cout<<"before commit"<<endl;
    res = NULL;
    res = stmt -> executeQuery ("SELECT * FROM tb_empl");
    retrieve_data_and_print (res, COLNAME, 1, string ("name"));


    cout << "\tCommitting outstanding updates to the database .." << endl;
    con -> commit();

    cout << "\nQuerying the City table again .." << endl;
    cout<<"after commit"<<endl;

    res = NULL;
    res = stmt -> executeQuery ("SELECT * FROM tb_empl");
    retrieve_data_and_print (res, COLNAME, 1, string ("name"));

    cout << "Cleaning up the resources .." << endl;

    /* Clean up */
    delete res;
    delete stmt;
    delete prep_stmt;
    con -> close();
    delete con;

  } catch (SQLException &e) {
    cout << "ERROR: SQLException in " << __FILE__;
    cout << " (" << __func__<< ") on line " << __LINE__ << endl;
    cout << "ERROR: " << e.what();
    cout << " (MySQL error code: " << e.getErrorCode();
    cout << ", SQLState: " << e.getSQLState() << ")" << endl;

    if (e.getErrorCode() == 1047) {
      /*
            Error: 1047 SQLSTATE: 08S01 (ER_UNKNOWN_COM_ERROR)
            Message: Unknown command
            */
      cout << "\nYour server does not seem to support Prepared Statements at all. ";
      cout << "Perhaps MYSQL < 4.1?" << endl;
    }

    return EXIT_FAILURE;
  } catch (std::runtime_error &e) {

    cout << "ERROR: runtime_error in " << __FILE__;
    cout << " (" << __func__ << ") on line " << __LINE__ << endl;
    cout << "ERROR: " << e.what() << endl;

    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}


int test_DataOP(){

  //init
  //  连接至数DBMS
  //  创建测试数据库
  //  测试测试数据表
  //  检查测试数据与测试基本表的状态
  Driver *driver;
  Connection *con;
  Statement *stmt;
  ResultSet *res;
  PreparedStatement *prep_stmt;

  string usrname="root";
  string password="123456";
  string host="127.0.0.1";
  string db_test="db_test_0909";
  string tb_test="tb_test_1003";



  try {

    cout<<"连接至DBMS"<<endl;
    driver=get_driver_instance();
    con=driver->connect(host,usrname,password);
    if(con->isValid()){
      cout<<"[connected]"<<endl;
    }
    else{
      cout<<"[unconnected]"<<endl;
    }
    con->setAutoCommit(false);


    cout<<"创建测试数据库"<<endl;
    prep_stmt = con -> prepareStatement ("CREATE DATABASE IF NOT EXISTS "+db_test
                                         );
    prep_stmt->executeUpdate();
    con->setSchema(db_test);
    retrieve_dbmetadata_and_print (con);


    cout<<"创建基本表"<<endl;
    prep_stmt = con -> prepareStatement ("CREATE TABLE IF NOT EXISTS "
                                         +tb_test+
                                         " (ID INT(11))");
    prep_stmt -> executeUpdate();
    stmt = con -> createStatement();
    //    res = stmt->executeQuery("select TABLE_NAME  from information_schema.TABLES  where TABLE_SCHEMA = '"
    //                             +db_test+
    //                             "' ");
    prep_stmt = con -> prepareStatement ("select TABLE_NAME  from information_schema.TABLES  where TABLE_SCHEMA = '"
                                         +db_test+
                                         "' ");
    prep_stmt -> executeUpdate();
    res =prep_stmt->getResultSet();
    retrieve_data_and_print(res,COLNAME,0,"TABLE_NAME");
    cout<<"[end] to 创建基本表"<<endl;

    cout<<"=====================主题部分 start====================="<<endl;

    cout<<"数据操作测试"<<endl;
    cout<<"1.插入操作"<<endl;
    prep_stmt = con -> prepareStatement ("INSERT INTO "
                                         +tb_test+
                                         " VALUES(?) ");
    //    prep_stmt->setString(1,tb_test);
    prep_stmt->setInt(1,0);
    prep_stmt -> executeUpdate();


    cout<<"2.查询操作"<<endl;
    prep_stmt = con -> prepareStatement ("SELECT * FROM  "+tb_test);
    prep_stmt -> executeUpdate();
    res =prep_stmt->getResultSet();
    retrieve_data_and_print(res,COLNAME,0,"ID");


    cout<<"3.修改操作"<<endl;
    cout<<"query:"<<"UPDATE "+tb_test+
          "SET ID=10 WHERE ID=0"<<endl;
    prep_stmt = con -> prepareStatement ("UPDATE "+tb_test+
                                         " SET ID=? WHERE ID=0"
                                         );

    prep_stmt->setInt(1,66);
    prep_stmt -> executeUpdate();
    //
    prep_stmt = con -> prepareStatement ("SELECT * FROM  "+tb_test);
    prep_stmt -> executeUpdate();
    res =prep_stmt->getResultSet();
    retrieve_data_and_print(res,COLNAME,0,"ID");


    cout<<"4.删除操作"<<endl;
    cout<<"query:"<<"UPDATE "+tb_test+
          "SET ID=10 WHERE ID=0"<<endl;
    prep_stmt = con -> prepareStatement ("DELETE FROM "+tb_test+
                                         " WHERE ID=?"
                                         );

    prep_stmt->setInt(1,66);
    prep_stmt -> executeUpdate();
    //
    prep_stmt = con -> prepareStatement ("SELECT * FROM  "+tb_test);
    prep_stmt -> executeUpdate();
    res =prep_stmt->getResultSet();
    retrieve_data_and_print(res,COLNAME,0,"ID");






    cout<<"=====================主题部分 end====================="<<endl;


    cout<<"删除基本表"<<endl;
    prep_stmt = con -> prepareStatement ("DROP TABLE IF  EXISTS "
                                         +tb_test);
    prep_stmt -> executeUpdate();
    res = stmt->executeQuery("select TABLE_NAME  from information_schema.TABLES  where TABLE_SCHEMA = '"
                             +db_test+
                             "' ");
    retrieve_data_and_print(res,COLNAME,0,"TABLE_NAME");
    cout<<"[end] to 删除基本表"<<endl;

    cout<<"删除测试数据库"<<endl;
    prep_stmt = con -> prepareStatement ("DROP DATABASE IF EXISTS "+db_test
                                         );
    prep_stmt->executeUpdate();
    retrieve_dbmetadata_and_print (con);
    cout<<"[end] to 删除测试数据库"<<endl;



    cout<<"断开与DBMS的连接"<<endl;
    con->close();



  }catch (SQLException &e) {
    cout << "ERROR: SQLException in " << __FILE__;
    cout << " (" << __func__<< ") on line " << __LINE__ << endl;
    cout << "ERROR: " << e.what();
    cout << " (MySQL error code: " << e.getErrorCode();
    cout << ", SQLState: " << e.getSQLState() << ")" << endl;

    if (e.getErrorCode() == 1047) {
      /*
            Error: 1047 SQLSTATE: 08S01 (ER_UNKNOWN_COM_ERROR)
            Message: Unknown command
            */
      cout << "\nYour server does not seem to support Prepared Statements at all. ";
      cout << "Perhaps MYSQL < 4.1?" << endl;
    }

    return EXIT_FAILURE;
  } catch (std::runtime_error &e) {

    cout << "ERROR: runtime_error in " << __FILE__;
    cout << " (" << __func__ << ") on line " << __LINE__ << endl;
    cout << "ERROR: " << e.what() << endl;

    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;




  //test
  //  测试数据插入操作
  //  测试数据查询操作
  //  测试数据修改操作
  //  测试数据删除操作

  //end
  //  删除基本表
  //  删除数据库
  //  断开与数据库的连接

}

//测试索引的常用操作和对检索的效果；关闭数据后是否会继续存在；数据更新后数据是否会增加
//  1. 创建测试数据库，包含一定数据
//  2. 创建索引
//  3. 输出索引
//  4. 借助索引进行搜索
//  5. 更新基本表时更新数据
//  6. 删除索引

int test_index(){

  //init
  //  连接至数DBMS
  //  创建测试数据库
  //  测试测试数据表
  //  检查测试数据与测试基本表的状态
  Driver *driver;
  Connection *con;
  Statement *stmt;
  ResultSet *res;
  PreparedStatement *prep_stmt;

  string usrname="root";
  string password="123456";
  string host="127.0.0.1";
  string db_test="db_test_0909";
  string tb_test="tb_test_1003";



  try {

    cout<<"连接至DBMS"<<endl;
    driver=get_driver_instance();
    con=driver->connect(host,usrname,password);
    if(con->isValid()){
      cout<<"[connected]"<<endl;
    }
    else{
      cout<<"[unconnected]"<<endl;
    }
    con->setAutoCommit(false);


    cout<<"创建测试数据库"<<endl;
    prep_stmt = con -> prepareStatement ("CREATE DATABASE IF NOT EXISTS "+db_test
                                         );
    prep_stmt->executeUpdate();
    con->setSchema(db_test);
    retrieve_dbmetadata_and_print (con);


    cout<<"创建基本表"<<endl;
    prep_stmt = con -> prepareStatement ("CREATE TABLE IF NOT EXISTS "
                                         +tb_test+
                                         " (ID INT(11),name VARCHAR(25))");
    prep_stmt -> executeUpdate();
    stmt = con -> createStatement();
    //    res = stmt->executeQuery("select TABLE_NAME  from information_schema.TABLES  where TABLE_SCHEMA = '"
    //                             +db_test+
    //                             "' ");
    prep_stmt = con -> prepareStatement ("select TABLE_NAME  from information_schema.TABLES  where TABLE_SCHEMA = '"
                                         +db_test+
                                         "' ");
    prep_stmt -> executeUpdate();
    res =prep_stmt->getResultSet();
    retrieve_data_and_print(res,COLNAME,0,"TABLE_NAME");
    cout<<"[end] to 创建基本表"<<endl;

    cout<<"初始化数据库"<<endl;
    {
    prep_stmt = con -> prepareStatement ("INSERT INTO "
                                         +tb_test+
                                         " VALUES(?,?) ");
    prep_stmt->setInt(1,0);
    prep_stmt->setString(2,"John");
    prep_stmt -> executeUpdate();

    prep_stmt = con -> prepareStatement ("INSERT INTO "
                                         +tb_test+
                                         " VALUES(?,?) ");
    prep_stmt->setInt(1,54);
    prep_stmt->setString(2,"Sff");
    prep_stmt -> executeUpdate();

    prep_stmt = con -> prepareStatement ("INSERT INTO "
                                         +tb_test+
                                         " VALUES(?,?) ");
    prep_stmt->setInt(1,78);
    prep_stmt->setString(2,"Rff");
    prep_stmt -> executeUpdate();

    prep_stmt = con -> prepareStatement ("INSERT INTO "
                                         +tb_test+
                                         " VALUES(?,?) ");
    prep_stmt->setInt(1,657);
    prep_stmt->setString(2,"Lgg");
    prep_stmt -> executeUpdate();

    prep_stmt = con -> prepareStatement ("INSERT INTO "
                                         +tb_test+
                                         " VALUES(?,?) ");
    prep_stmt->setInt(1,76);
    prep_stmt->setString(2,"Off");
    prep_stmt -> executeUpdate();

    prep_stmt = con -> prepareStatement ("INSERT INTO "
                                         +tb_test+
                                         " VALUES(?,?) ");
    prep_stmt->setInt(1,79);
    prep_stmt->setString(2,"Rrrr");
    prep_stmt -> executeUpdate();

    con->commit();
    }

    cout<<"查询操作"<<endl;
    prep_stmt = con -> prepareStatement ("SELECT * FROM  "+tb_test);
    prep_stmt -> executeUpdate();
    res =prep_stmt->getResultSet();
    retrieve_data_and_print(res,COLNAME,0,"name");

    cout<<"=====================主题部分 start====================="<<endl;

    cout<<"1. 查询基本表的索引"<<endl;
    prep_stmt = con -> prepareStatement ("SHOW INDEX FROM "
                                         +tb_test
                                         );
    prep_stmt -> executeUpdate();
    res =prep_stmt->getResultSet();
    retrieve_data_and_print(res,COLNAME,0,"Key_name");

    cout<<"2. 创建索引"<<endl;
    prep_stmt = con -> prepareStatement ("alter table "
                                         +tb_test+
                                         " add index index_name(name)"
                                         );
    prep_stmt -> executeUpdate();
    cout<<"【查询索引】"<<endl;
    prep_stmt = con -> prepareStatement ("SHOW INDEX FROM "
                                         +tb_test
                                         );
    prep_stmt -> executeUpdate();
    res =prep_stmt->getResultSet();
    retrieve_data_and_print(res,COLNAME,0,"Key_name");


    cout<<"4. 输出索引"<<endl;
    prep_stmt = con -> prepareStatement ("SELECT * FROM `"
                                         +tb_test+
                                         "`  FORCE INDEX(`"
                                         +"index_name"+
                                         "`)"
                                         );
    prep_stmt -> executeUpdate();
    res =prep_stmt->getResultSet();
    retrieve_data_and_print(res,COLNAME,0,"name");


    cout<<"*. 测试基本表数据修改时，索引内容是否相应改变"<<endl;

    prep_stmt = con -> prepareStatement ("INSERT INTO "
                                         +tb_test+
                                         " VALUES(?,?) ");
    prep_stmt->setInt(1,999);
    prep_stmt->setString(2,"insert");
    prep_stmt -> executeUpdate();

    cout<<"输出索引"<<endl;
    prep_stmt = con -> prepareStatement ("SELECT * FROM `"
                                         +tb_test+
                                         "`  FORCE INDEX(`"
                                         +"index_name"+
                                         "`)"
                                         );
    prep_stmt -> executeUpdate();
    res =prep_stmt->getResultSet();
    retrieve_data_and_print(res,COLNAME,0,"name");


    cout<<"3. 删除索引"<<endl;
    prep_stmt = con -> prepareStatement ("alter table "
                                         +tb_test+
                                         " DROP INDEX index_name"
                                         );
    prep_stmt -> executeUpdate();
    cout<<"【查询索引】"<<endl;
    prep_stmt = con -> prepareStatement ("SHOW INDEX FROM "
                                         +tb_test
                                         );

    prep_stmt -> executeUpdate();
    res =prep_stmt->getResultSet();
    retrieve_data_and_print(res,COLNAME,0,"Key_name");

    cout<<"=====================主题部分 end====================="<<endl;


    cout<<"删除基本表"<<endl;
    prep_stmt = con -> prepareStatement ("DROP TABLE IF  EXISTS "
                                         +tb_test);
    prep_stmt -> executeUpdate();
    res = stmt->executeQuery("select TABLE_NAME  from information_schema.TABLES  where TABLE_SCHEMA = '"
                             +db_test+
                             "' ");
    retrieve_data_and_print(res,COLNAME,0,"TABLE_NAME");
    cout<<"[end] to 删除基本表"<<endl;

    cout<<"删除测试数据库"<<endl;
    prep_stmt = con -> prepareStatement ("DROP DATABASE IF EXISTS "+db_test
                                         );
    prep_stmt->executeUpdate();
    retrieve_dbmetadata_and_print (con);
    cout<<"[end] to 删除测试数据库"<<endl;



    cout<<"断开与DBMS的连接"<<endl;
    con->close();



  }catch (SQLException &e) {
    cout << "ERROR: SQLException in " << __FILE__;
    cout << " (" << __func__<< ") on line " << __LINE__ << endl;
    cout << "ERROR: " << e.what();
    cout << " (MySQL error code: " << e.getErrorCode();
    cout << ", SQLState: " << e.getSQLState() << ")" << endl;

    if (e.getErrorCode() == 1047) {
      /*
            Error: 1047 SQLSTATE: 08S01 (ER_UNKNOWN_COM_ERROR)
            Message: Unknown command
            */
      cout << "\nYour server does not seem to support Prepared Statements at all. ";
      cout << "Perhaps MYSQL < 4.1?" << endl;
    }

    return EXIT_FAILURE;
  } catch (std::runtime_error &e) {

    cout << "ERROR: runtime_error in " << __FILE__;
    cout << " (" << __func__ << ") on line " << __LINE__ << endl;
    cout << "ERROR: " << e.what() << endl;

    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;


}





