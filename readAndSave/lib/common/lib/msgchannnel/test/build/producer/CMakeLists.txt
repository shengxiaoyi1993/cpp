cmake_minimum_required(VERSION 2.8)
project(producer)
set( CMAKE_CXX_FLAGS "-std=c++11" )
add_executable(${PROJECT_NAME}
"../../src/producer/producer.cpp"
"../../../msgchannel.cpp")
message("PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
target_link_libraries( producer -pthread)
