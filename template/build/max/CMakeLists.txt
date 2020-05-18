cmake_minimum_required(VERSION 2.8)
project(max)
set( CMAKE_CXX_FLAGS "-std=c++11" )
add_executable(${PROJECT_NAME}
"../../src/max/test.cpp"
)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../bin)
message("PROJECT_SOURCE_DIR: "${PROJECT_SOURCE_DIR})
target_link_libraries( max )
