# cmake_minimum_required(VERSION 2.8)
# project(example)
# set( CMAKE_CXX_FLAGS "-std=c++11" )
# add_executable(${PROJECT_NAME} "../src/main.cpp""../src/export.cpp")
# message("PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
# target_link_libraries( example )

SET(PATH_COMPILER_SDX "/storage/Software/xilinx/SDK/2019.1/gnu" CACHE STRING "Some user-specified option")
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_C_COMPILER ${PATH_COMPILER_SDX}/aarch32/lin/gcc-arm-linux-gnueabi/bin/arm-linux-gnueabihf-gcc)
SET(CMAKE_CXX_COMPILER ${PATH_COMPILER_SDX}/aarch32/lin/gcc-arm-linux-gnueabi/bin/arm-linux-gnueabihf-g++)


cmake_minimum_required (VERSION 3.0.2)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../API)
# set( CMAKE_CXX_FLAGS "-std=c++11" )

#message("CMAKE_CURRENT_SOURCE_DIR:"${CMAKE_CURRENT_SOURCE_DIR})

project (myproj VERSION 1.0)


add_executable(${PROJECT_NAME}
  "../src/main.c"
  "../API/core/VL53L1X_api.c"
  "../API/core/VL53L1X_calibration.c"
  "../API/platform/vl53l1_platform.c"
  )

target_link_libraries( ${PROJECT_NAME} )
