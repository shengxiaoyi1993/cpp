# gtest的嵌入式程序测试

## 基本过程
- 使用嵌入式编译器编译gtest库
- 将待测试类编译成动态库
- 编写gtest测试方法
- 补充gtest 测试用例
- 实际测试与优化



### 更改编译器编译gtest通过
- CMakefiles添加编译器设置
```

SET(PATH_COMPILER_SDX "/storage/Software/xilinx/SDK/2019.1/gnu" CACHE STRING "Some user-specified option")
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_C_COMPILER ${PATH_COMPILER_SDX}/aarch32/lin/gcc-arm-linux-gnueabi/bin/arm-linux-gnueabihf-gcc)
SET(CMAKE_CXX_COMPILER ${PATH_COMPILER_SDX}/aarch32/lin/gcc-arm-linux-gnueabi/bin/arm-linux-gnueabihf-g++)
set( CMAKE_CXX_FLAGS "-std=c++11" )

```
- 正常使用cmake进行编译

- 编写的程序未经相应平台测试


### 一次编译供多个模块使用的项目结构
