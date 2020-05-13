# googletest-release-1.8.0

- download

  ```
  https://github.com/google/googletest/archive/release-1.8.0.tar.gz
  ```

  - 

- build

  ```
  cd googletest-release-1.8.0/
  $ cd googletest
  $ cmake -DBUILD_SHARED_LIBS=ON .
  $ make
  //编译成功 头文件在include,动态库libgtest_main.so,libgtest.so
  mkdir /home/sxy/opt/gtest1.8.0/include/ -p
  mkdir /home/sxy/opt/gtest1.8.0/lib/ -p
  $ sudo cp -a include/gtest /home/sxy/opt/gtest1.8.0/include
  $ sudo cp -a libgtest_main.so libgtest.so /home/sxy/opt/gtest1.8.0/lib/
  
  ```

  

- test

```
export GTEST_HOME=/home/sxy/opt/gtest1.8.0
export LD_LIBRARY_PATH=$GTEST_HOME/lib:$LD_LIBRARY_PATH
g++ -I $GTEST_HOME/include -L $GTEST_HOME/lib -lgtest -lgtest_main -lpthread gtest_demo.c 
```

- cmake
  ```
  cmake_minimum_required(VERSION 2.8)
  project(example)
  set( CMAKE_CXX_FLAGS "-std=c++11" )
  SET(CMAKE_C_COMPILER "g++")
  add_executable(${PROJECT_NAME} "../src/gtest_demo.c")
  include_directories("/home/sxy/opt/gtest1.8.0/include/")
  link_directories("/home/sxy/opt/gtest1.8.0/lib")
  
  message("PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
  target_link_libraries( example 
  /home/sxy/opt/gtest1.8.0/lib/libgtest.so
  /home/sxy/opt/gtest1.8.0/lib/libgtest_main.so -lpthread )
  ```

  