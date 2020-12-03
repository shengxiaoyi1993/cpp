# test


## compile in win
### 1
- mysql server 8.0.20
- mysql workbench 8.0 CE
- can connect to mysql_server by terminal and mysql_cpp compiled in centos


### 2
- connect to mysql_server by lib `mysql-connector-c++-8.0.21-winx64` failed

- but compiled is succeed ,cmake file as fellow
```
cmake_minimum_required(VERSION 2.8)
#cmake_minimum_required(VERSION 3.5)

project(mysqlcpp_warpper )
set( CMAKE_CXX_FLAGS "-std=c++11"  )
set(CMAKE_BUILD_TYPE "Debug")
set( DMYSQL_CXXFLAGS "-stdlib=libc++"  )

#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} "../src/main.cpp"
  "../src/mysqlcpp/mysqlcpp_test.cpp"
  "../src/mysqlcpp/mysqlcpp_tool.cpp"
  "../src/mysqlcpp/mysqlcpp_warpper.cpp"
  "../lib_copy/cjson/cJSON.c"
  )
message("PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
string(REGEX REPLACE "(.+)\\cpp/mysqlcpp/build.*" "\\1" PROJECT_INIT_PATH ${PROJECT_SOURCE_DIR})
message("PROJECT_INIT_PATH: " ${PROJECT_INIT_PATH})


set(mysql_INCLUDE_DIRS "${PROJECT_INIT_PATH}/mysql-connector-c++-8.0.21-winx64/mysql-connector-c++-8.0.21-winx64/include")

set(mysql_LIBRARIES_DIRS "${PROJECT_INIT_PATH}/mysql-connector-c++-8.0.21-winx64/mysql-connector-c++-8.0.21-winx64/lib64")


# FILE(GLOB_RECURSE mysql_LIBs "${PROJECT_INIT_PATH}start/lib/mysql-3.4.1/lib64/*.so")
FILE(GLOB_RECURSE mysql_LIBs "${PROJECT_INIT_PATH}mysql-connector-c++-8.0.21-winx64/mysql-connector-c++-8.0.21-winx64/lib64/*.dll")


message("mysql_LIBs: " ${mysql_LIBs})

message(${mysql_LIBRARIES_DIRS})
include_directories(${mysql_INCLUDE_DIRS})
link_directories(${mysql_LIBRARIES_DIRS})
target_link_libraries( mysqlcpp_warpper "${mysql_LIBs}")

#target_link_libraries( ${PROJECT_NAME} -L/usr/lib64/mysql -lmysqlclient -lmysqlcppconn -lpthread -lm -ldl)



```
