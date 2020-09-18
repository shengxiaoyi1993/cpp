cmake_minimum_required(VERSION 2.8)
project(example)
set( CMAKE_CXX_FLAGS "-std=c++11" )
add_executable(${PROJECT_NAME} "../src/main.cpp"
  "../lib/pnm/pnm.cpp"
  "../lib/common/string_manipulation.cpp"
  "../lib/raw/raw.cpp"
  "../lib/raw/bayer_convert.c"
  "../lib/jpeg/jpgd.cpp"
  "../lib/jpeg/jpge.cpp"
  "../src/ImageConverter.cpp")
message("PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
target_link_libraries( example )
