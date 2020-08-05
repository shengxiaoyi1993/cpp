cmake_minimum_required(VERSION 2.8)
project(onvif)
#set( CMAKE_CXX_FLAGS "-std=c++11" )
add_compile_options(-DWITH_OPENSSL -DWITH_DOM  -DWITH_NONAMESPACES)
add_executable(${PROJECT_NAME}
"../src/main.cpp"
"../src/onvif_export.c"
"../src/onvif/smdevp.c"
"../src/onvif/wsseapi.c"
"../src/onvif/dom.c"
"../src/onvif/duration.c"
"../src/onvif/mecevp.c"
"../src/onvif/threads.c"
"../src/onvif/soapC.c"
"../src/onvif/stdsoap2.c"
"../src/onvif/wsaapi.c"
"../src/onvif/soapClient.c"
"../src/onvif/wsdd.nsmap")
message("PROJECT_SOURCE_DIR: "${PROJECT_SOURCE_DIR})


IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    target_link_libraries( onvif uuid ssl crypto pthread z dl)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    target_link_libraries( onvif uuid ssl crypto pthread z ws2_32)
ELSE ()
    MESSAGE(STATUS "platform error!")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")
