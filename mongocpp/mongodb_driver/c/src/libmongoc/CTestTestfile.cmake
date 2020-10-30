# CMake generated Testfile for 
# Source directory: /home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc
# Build directory: /home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libmongoc
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test-libmongoc "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libmongoc/test-libmongoc")
set_tests_properties(test-libmongoc PROPERTIES  WORKING_DIRECTORY "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/../.." _BACKTRACE_TRIPLES "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/CMakeLists.txt;801;add_test;/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/CMakeLists.txt;0;")
subdirs("build")
subdirs("examples")
subdirs("src")
subdirs("tests")
