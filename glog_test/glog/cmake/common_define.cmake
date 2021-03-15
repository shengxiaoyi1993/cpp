

# 由于该项目有可能在不同平台（嵌入式linux/centos）下测试和与运行，因此使用该文件对总环境进行配置


# define path of compiler
SET(PATH_COMPILER_SDX "/storage/Software/xilinx/SDK/2019.1/gnu" CACHE STRING "Some user-specified option")
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_C_COMPILER ${PATH_COMPILER_SDX}/aarch32/lin/gcc-arm-linux-gnueabi/bin/arm-linux-gnueabihf-gcc)
SET(CMAKE_CXX_COMPILER ${PATH_COMPILER_SDX}/aarch32/lin/gcc-arm-linux-gnueabi/bin/arm-linux-gnueabihf-g++)

set( CMAKE_CXX_FLAGS "-std=c++11" )


# 对于一些已编译的库文件
# 最好是即时编译
