cmake_minimum_required (VERSION 2.8)
project (receiver)

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

add_executable (receiver
../../../lib/common/lib/msgchannnel/msgchannel.cpp
../../../lib/common/lib/channel_imagebuffer/channel_imagebuffer.cpp
../../src/receiver/receiver.cpp
)


target_link_libraries (receiver ${FC_DEP_LIBS} -pthread)
