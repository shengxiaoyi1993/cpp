# cmake_minimum_required(VERSION 2.8)
# project(example)
# add_executable(${PROJECT_NAME} "../src/main.cpp""../src/export.cpp")
# message("PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
# target_link_libraries( example )


cmake_minimum_required (VERSION 3.0.2)
project (myproj VERSION 1.0)

# find_package (glog 0.5.0 REQUIRED)
set( CMAKE_CXX_FLAGS "-std=c++11" )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib/)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib/dahua/lib/) #添加动态连接库的路径

add_executable(${PROJECT_NAME} "../src/main.cpp""../src/export.cpp")

# add_executable (myapp main.cpp)
target_link_libraries (${PROJECT_NAME}  
-ldhnetsdk)
