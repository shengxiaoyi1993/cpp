cmake_minimum_required(VERSION 2.8)
project(fdwithfork)
set( CMAKE_CXX_FLAGS "-std=c++11" )
add_executable(${PROJECT_NAME} "../../src/fdwithfork/fdwithfork.cpp")
message("PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../bin)
target_link_libraries( fdwithfork )
