cmake_minimum_required(VERSION 2.8)
project(portscan)
set( CMAKE_CXX_FLAGS "-std=c++11" )
add_executable(${PROJECT_NAME} "../src/main.cpp")

target_link_libraries( portscan )

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    target_link_libraries( portscan )
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    target_link_libraries( portscan -lstdc++)
ELSE ()
    MESSAGE(STATUS "platform error!")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")
