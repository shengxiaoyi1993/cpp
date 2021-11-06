# cmake_minimum_required(VERSION 2.8)
# project(example)
# set( CMAKE_CXX_FLAGS "-std=c++11" )
# add_executable(${PROJECT_NAME} "../src/main.cpp""../src/export.cpp")
# message("PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
# target_link_libraries( example )


cmake_minimum_required (VERSION 3.0.2)
project (myproj VERSION 1.0)
 set( CMAKE_CXX_FLAGS "-std=c++11" )


# find_package (glog 0.5.0 REQUIRED)

add_executable(${PROJECT_NAME}
"../src/main.cpp"
"../src/jpeg_op.cpp"
"../src/bf_search.cpp"
)

# add_executable (myapp main.cpp)
# target_link_libraries (myapp glog::glog)
