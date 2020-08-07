cmake_minimum_required(VERSION 2.8)
project(example)
set( CMAKE_CXX_FLAGS "-std=c++11  " )
add_executable(${PROJECT_NAME}
  "../src/mysql_query.cpp"
  "../src/sha512.cpp"
   "../src/basic.cpp" )
message("PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
target_link_libraries( example -L/usr/lib64/mysql -lmysqlclient -lmysqlcppconn -lpthread -lm -ldl)
