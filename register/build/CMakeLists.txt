cmake_minimum_required(VERSION 2.8)
project(register_test)
set( CMAKE_CXX_FLAGS "-std=c++11" )
add_executable(${PROJECT_NAME}
"../src/main.cpp"
"../src/device.cpp"
"../src/register.cpp"
"../src/dvt-uio.cpp"
"../src/cJSON.c"
"../src/basic.cpp"

)
message("PROJECT_SOURCE_DIR: "${PROJECT_SOURCE_DIR})
target_link_libraries( example )

