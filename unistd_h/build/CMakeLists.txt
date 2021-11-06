# cmake_minimum_required(VERSION 2.8)
# project(example)
# set( CMAKE_CXX_FLAGS "-std=c++11" )
# add_executable(${PROJECT_NAME} "../src/main.cpp""../src/export.cpp")
# message("PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
# target_link_libraries( example )


cmake_minimum_required (VERSION 3.0.2)
project (unistd_h VERSION 1.0 LANGUAGES C)

#find_package (glog 0.5.0 REQUIRED)

add_executable(${PROJECT_NAME} "../src/main.c")

# add_executable (${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} )
