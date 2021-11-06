cmake_minimum_required(VERSION 2.8)
project(producer)
set( CMAKE_CXX_FLAGS "-std=c++11" )

# SET(COMBILEPATH "/home/sxy/Software/Xilinx/SDK/2019.1/gnu/aarch32/lin/gcc-arm-linux-gnueabi/bin" CACHE STRING "Some user-specified option")
# SET(CMAKE_SYSTEM_NAME Linux)
# # SET(CMAKE_C_COMPILER ${COMBILEPATH}/aarch32/lin/gcc-arm-linux-gnueabi/bin/aarch64-linux-gnu-gcc)
# SET(CMAKE_C_COMPILER ${COMBILEPATH}/aarch32/lin/gcc-arm-linux-gnueabi/bin/arm-linux-gnueabihf-gcc)
# # SET(CMAKE_C_COMPILER ${COMBILEPATH}/aarch32/lin/gcc-arm-linux-gnueabi/bin/aarch64-linux-gnu-g++)
# # SET(CMAKE_CXX_COMPILER ${COMBILEPATH}/aarch32/lin/gcc-arm-linux-gnueabi/bin/aarch64-linux-gnu-g++)
# SET(CMAKE_CXX_COMPILER ${COMBILEPATH}/aarch32/lin/gcc-arm-linux-gnueabi/bin/arm-linux-gnueabihf-g++)

add_executable(${PROJECT_NAME} "../../src/main/msgchannel.cpp"
"../../src/example/producer/producer.cpp")
message("PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
target_link_libraries( producer -lpthread)
