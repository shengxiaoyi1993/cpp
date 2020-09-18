cmake_minimum_required(VERSION 2.8)
project(example)
set( CMAKE_CXX_FLAGS "-std=c++11" )
# add_executable(${PROJECT_NAME} "../src/main.cpp"
#   "../lib/pnm/pnm.cpp"
#   "../lib/common/string_manipulation.cpp"
#   "../lib/raw/raw.cpp"
#   "../lib/raw/bayer_convert.c"
#   "../lib/jpeg/jpgd.cpp"
#   "../lib/jpeg/jpge.cpp"
#   "../src/ImageConverter.cpp")
#

aux_source_directory("../lib/" DIR_SRCS)
message("DIR_SRCS: " ${DIR_SRCS})
add_executable(example ${DIR_SRCS}
  "../src/test.cpp"
  )
target_link_libraries( example )
