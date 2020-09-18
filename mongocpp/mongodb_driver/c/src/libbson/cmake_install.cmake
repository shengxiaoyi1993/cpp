# Install script for directory: /home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libbson

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/usr")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libbson-1.0.so.0.0.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libbson-1.0.so.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libbson/libbson-1.0.so.0.0.0"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libbson/libbson-1.0.so.0"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libbson-1.0.so.0.0.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libbson-1.0.so.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libbson-1.0.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libbson-1.0.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libbson-1.0.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libbson/libbson-1.0.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libbson-1.0.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libbson-1.0.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libbson-1.0.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE STATIC_LIBRARY FILES "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libbson/libbson-static-1.0.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libbson-1.0/bson" TYPE FILE FILES
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libbson/src/bson/bson-config.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libbson/src/bson/bson-version.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libbson/src/bson/bcon.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libbson/src/bson/bson-atomic.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libbson/src/bson/bson-clock.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libbson/src/bson/bson-compat.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libbson/src/bson/bson-context.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libbson/src/bson/bson-decimal128.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libbson/src/bson/bson-endian.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libbson/src/bson/bson-error.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libbson/src/bson/bson.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libbson/src/bson/bson-iter.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libbson/src/bson/bson-json.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libbson/src/bson/bson-keys.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libbson/src/bson/bson-macros.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libbson/src/bson/bson-md5.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libbson/src/bson/bson-memory.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libbson/src/bson/bson-oid.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libbson/src/bson/bson-prelude.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libbson/src/bson/bson-reader.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libbson/src/bson/bson-string.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libbson/src/bson/bson-types.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libbson/src/bson/bson-utf8.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libbson/src/bson/bson-value.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libbson/src/bson/bson-version-functions.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libbson/src/bson/bson-writer.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libbson-1.0" TYPE FILE FILES "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libbson/src/bson/forwarding/bson.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/pkgconfig" TYPE FILE FILES "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libbson/src/libbson-1.0.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/pkgconfig" TYPE FILE FILES "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libbson/src/libbson-static-1.0.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/libbson-1.0" TYPE FILE FILES "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libbson/libbson-1.0-config.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/libbson-1.0" TYPE FILE FILES "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libbson/libbson-1.0-config-version.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/libbson-static-1.0" TYPE FILE FILES "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libbson/libbson-static-1.0-config.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/libbson-static-1.0" TYPE FILE FILES "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libbson/libbson-static-1.0-config-version.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libbson/build/cmake_install.cmake")
  include("/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libbson/examples/cmake_install.cmake")
  include("/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libbson/src/cmake_install.cmake")
  include("/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libbson/tests/cmake_install.cmake")

endif()

