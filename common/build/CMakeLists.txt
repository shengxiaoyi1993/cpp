cmake_minimum_required(VERSION 2.8)
project(common)
set( CMAKE_CXX_FLAGS "-std=c++11" )
add_executable(${PROJECT_NAME} "../src/main.cpp"
  "../src/cpp/basicio.cpp"
  "../src/cpp/string_manipulation.cpp")
message("PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
target_link_libraries( ${PROJECT_NAME} )
