cmake_minimum_required(VERSION 2.8)

project(log)
add_executable(${PROJECT_NAME}
  "../src/main.cpp"
  "../src/syslogger.cpp")
