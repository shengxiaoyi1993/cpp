cmake_minimum_required(VERSION 2.8)
project(encrypt_test)
set( CMAKE_CXX_FLAGS "-std=c++11" )
include_directories(${PROJECT_SOURCE_DIR}/../build_lib/bin/include)

add_executable(${PROJECT_NAME} "../../src/test/test.cpp")
message("PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR}/../build_lib/bin/include)

target_link_libraries(encrypt_test -L${PROJECT_SOURCE_DIR}/../build_lib/bin/lib/ -lencrypt)
