cmake_minimum_required (VERSION 2.8)
project (displaydemo)

# cross_compile_setting
set(CMAKE_SYSROOT /home/sxy/Software/Petalinux_18_3/2018_3_ultra96v1/ultra96v1_rootfs)
set(CMAKE_FIND_ROOT_PATH /home/sxy/Software/Petalinux_18_3/2018_3_ultra96v1/ultra96v1_rootfs)
SET(COMBILEPATH "/home/sxy/Software/petalinux/tools/linux-i386/aarch64-linux-gnu/bin/" CACHE STRING "Some user-specified option")
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_C_COMPILER ${COMBILEPATH}aarch64-linux-gnu-gcc)
SET(CMAKE_CXX_COMPILER ${COMBILEPATH}aarch64-linux-gnu-c++)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
  #  find_package(PkgConfig REQUIRED)
    find_package(GTK2 REQUIRED )
    message(STATUS "----- GTK2_INCLUDE_DIRS: ${GTK2_INCLUDE_DIRS}")
    message(STATUS "----- GKT3_LIBRARIES: ${GTK2_LIBRARIES}")
    message(STATUS "----- GTK2_LINK_LIBRARIES: ${GTK2_LINK_LIBRARIES}")
    include_directories(${GTK2_INCLUDE_DIRS})
    link_directories(${GTK2_LIBRARY_DIRS})
    list(APPEND FC_DEP_LIBS ${GTK2_LIBRARIES})
endif()

add_executable (displaydemo
  ../../lib/common/lib/msgchannnel/msgchannel.cpp
  ../../lib/common/lib/channel_imagebuffer/channel_imagebuffer.cpp
  ../src/displaydemo.cpp)

target_link_libraries (displaydemo ${FC_DEP_LIBS} -pthread)
