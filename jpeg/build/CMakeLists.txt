cmake_minimum_required(VERSION 2.8)
project(example)
set( CMAKE_CXX_FLAGS "-std=c++11" )
add_executable(${PROJECT_NAME} "../src/main.cpp"
  "../lib/jpeg-compressor/jpge.cpp"
  "../lib/jpeg-compressor/jpgd.cpp"
  "../lib_copy/pnm/pnm.cpp"
  "../lib_copy/common/string_manipulation.cpp"
  )
message("PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
target_link_libraries( example )
