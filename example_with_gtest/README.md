
# gtest-demo

> change the file frame from https://github.com/bast/gtest-demo.git


## 项目说明
- 本项目说明gtest的使用范例和文件组织形式
- 每个被测试的类/或者模块使用各自的cmake编译成动态库，gtest调用动态库的接口进行测试



## run the app
- 暂时没有写
<!-- - run app
```bash
cd build
cmake ../
make
./xxx

``` -->

## run gtest

### How to build this gtest

- run gtest
```bash

cd gtest
mkdir build
cd build
cmake ..
cmake --build .
```


### Running the tests

Either using `ctest`:
```
$ ctest

Running tests...
Test project /home/user/gtest-demo/build
    Start 1: unit
1/1 Test #1: unit .............................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.00 sec
```

Or directly using `unit_tests`:
```
$ ./bin/unit_tests

[==========] Running 2 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 2 tests from example
[ RUN      ] example.add
[       OK ] example.add (0 ms)
[ RUN      ] example.subtract
[       OK ] example.subtract (0 ms)
[----------] 2 tests from example (1 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test case ran. (1 ms total)
[  PASSED  ] 2 tests.

```




## References

- https://crascit.com/2015/07/25/cmake-gtest/

- https://github.com/bast/gtest-demo
