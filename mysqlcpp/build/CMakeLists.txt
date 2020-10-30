cmake_minimum_required(VERSION 2.8)
project(mysqlcpp_warpper)
set( CMAKE_CXX_FLAGS "-std=c++11" )
set(CMAKE_BUILD_TYPE "Debug")

add_executable(${PROJECT_NAME} "../src/main.cpp"
  "../src/mysqlcpp/mysqlcpp_test.cpp"
  "../src/mysqlcpp/mysqlcpp_tool.cpp"
  "../src/mysqlcpp/mysqlcpp_warpper.cpp"
  "../lib_copy/log/syslogger.cpp"
  "../lib_copy/cjson/cJSON.c"
  )
message("PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
target_link_libraries( ${PROJECT_NAME} -L/usr/lib64/mysql -lmysqlclient -lmysqlcppconn -lpthread -lm -ldl)
