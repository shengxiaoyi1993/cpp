cmake_minimum_required(VERSION 2.8)
project(normalapp)
set( CMAKE_CXX_FLAGS "-std=c++11" )
add_executable(${PROJECT_NAME} "../../src/normalapp/normalapp.cpp")
message("PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../bin)
target_link_libraries( normalapp )
