# CMake generated Testfile for 
# Source directory: /home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-cxx-driver-3.4.0/src/mongocxx/test
# Build directory: /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/src/mongocxx/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(driver "test_driver")
set_tests_properties(driver PROPERTIES  _BACKTRACE_TRIPLES "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-cxx-driver-3.4.0/src/mongocxx/test/CMakeLists.txt;160;add_test;/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-cxx-driver-3.4.0/src/mongocxx/test/CMakeLists.txt;0;")
add_test(logging "test_logging")
set_tests_properties(logging PROPERTIES  _BACKTRACE_TRIPLES "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-cxx-driver-3.4.0/src/mongocxx/test/CMakeLists.txt;161;add_test;/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-cxx-driver-3.4.0/src/mongocxx/test/CMakeLists.txt;0;")
add_test(instance "test_instance")
set_tests_properties(instance PROPERTIES  _BACKTRACE_TRIPLES "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-cxx-driver-3.4.0/src/mongocxx/test/CMakeLists.txt;162;add_test;/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-cxx-driver-3.4.0/src/mongocxx/test/CMakeLists.txt;0;")
add_test(crud_specs "test_crud_specs")
set_tests_properties(crud_specs PROPERTIES  ENVIRONMENT "CRUD_TESTS_PATH=/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-cxx-driver-3.4.0/data/crud" _BACKTRACE_TRIPLES "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-cxx-driver-3.4.0/src/mongocxx/test/CMakeLists.txt;163;add_test;/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-cxx-driver-3.4.0/src/mongocxx/test/CMakeLists.txt;0;")
add_test(gridfs_specs "test_gridfs_specs")
set_tests_properties(gridfs_specs PROPERTIES  ENVIRONMENT "GRIDFS_TESTS_PATH=/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-cxx-driver-3.4.0/data/gridfs" _BACKTRACE_TRIPLES "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-cxx-driver-3.4.0/src/mongocxx/test/CMakeLists.txt;164;add_test;/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-cxx-driver-3.4.0/src/mongocxx/test/CMakeLists.txt;0;")
add_test(command_monitoring_specs "test_command_monitoring_specs")
set_tests_properties(command_monitoring_specs PROPERTIES  ENVIRONMENT "COMMAND_MONITORING_TESTS_PATH=/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-cxx-driver-3.4.0/data/command-monitoring" _BACKTRACE_TRIPLES "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-cxx-driver-3.4.0/src/mongocxx/test/CMakeLists.txt;165;add_test;/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-cxx-driver-3.4.0/src/mongocxx/test/CMakeLists.txt;0;")
add_test(change_stream_specs "test_change_stream_specs")
set_tests_properties(change_stream_specs PROPERTIES  ENVIRONMENT "CHANGE_STREAM_TESTS_PATH=/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-cxx-driver-3.4.0/data/change_stream" _BACKTRACE_TRIPLES "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-cxx-driver-3.4.0/src/mongocxx/test/CMakeLists.txt;166;add_test;/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-cxx-driver-3.4.0/src/mongocxx/test/CMakeLists.txt;0;")
add_test(transactions_specs "test_transactions_specs")
set_tests_properties(transactions_specs PROPERTIES  ENVIRONMENT "TRANSACTIONS_TESTS_PATH=/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-cxx-driver-3.4.0/data/transactions" _BACKTRACE_TRIPLES "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-cxx-driver-3.4.0/src/mongocxx/test/CMakeLists.txt;167;add_test;/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-cxx-driver-3.4.0/src/mongocxx/test/CMakeLists.txt;0;")
