cmake_minimum_required(VERSION 2.8)

project(log)
set(CMAKE_BUILD_TYPE "Debug")
#ADD_DEFINITIONS(-D DEBUG_SYSLOGGER)

add_executable(${PROJECT_NAME}
  "../src/main.cpp"
  "../src/syslogger/syslogger.cpp")
