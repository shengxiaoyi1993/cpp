# Install script for directory: /home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE PROGRAM FILES "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libmongoc/mongoc-stat")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmongoc-1.0.so.0.0.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmongoc-1.0.so.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libmongoc/libmongoc-1.0.so.0.0.0"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libmongoc/libmongoc-1.0.so.0"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmongoc-1.0.so.0.0.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmongoc-1.0.so.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libbson:"
           NEW_RPATH "")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmongoc-1.0.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmongoc-1.0.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmongoc-1.0.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libmongoc/libmongoc-1.0.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmongoc-1.0.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmongoc-1.0.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmongoc-1.0.so"
         OLD_RPATH "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libbson:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmongoc-1.0.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmongoc-1.0.so.0.0.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmongoc-1.0.so.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libmongoc/libmongoc-1.0.so.0.0.0"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libmongoc/libmongoc-1.0.so.0"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmongoc-1.0.so.0.0.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmongoc-1.0.so.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libbson:"
           NEW_RPATH "")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmongoc-1.0.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmongoc-1.0.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmongoc-1.0.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libmongoc/libmongoc-1.0.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmongoc-1.0.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmongoc-1.0.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmongoc-1.0.so"
         OLD_RPATH "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libbson:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmongoc-1.0.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE STATIC_LIBRARY FILES "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libmongoc/libmongoc-static-1.0.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libmongoc-1.0/mongoc" TYPE FILE FILES
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libmongoc/src/mongoc/mongoc-config.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libmongoc/src/mongoc/mongoc-version.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-apm.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-bulk-operation.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-change-stream.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-client.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-client-pool.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-collection.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-cursor.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-database.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-error.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-flags.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-find-and-modify.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-gridfs.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-gridfs-bucket.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-gridfs-file.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-gridfs-file-page.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-gridfs-file-list.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-handshake.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-host-list.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-init.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-index.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-iovec.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-log.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-macros.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-matcher.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-opcode.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-prelude.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-read-concern.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-read-prefs.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-server-description.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-client-session.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-socket.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-stream-tls-libressl.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-stream-tls-openssl.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-stream.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-stream-buffered.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-stream-file.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-stream-gridfs.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-stream-socket.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-topology-description.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-uri.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-version-functions.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-write-concern.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-rand.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-stream-tls.h"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/mongoc-ssl.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libmongoc-1.0" TYPE FILE FILES "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-c-driver-1.14.0/src/libmongoc/src/mongoc/forwarding/mongoc.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/pkgconfig" TYPE FILE FILES "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libmongoc/src/libmongoc-1.0.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/pkgconfig" TYPE FILE FILES "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libmongoc/src/libmongoc-static-1.0.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/libmongoc-1.0" TYPE FILE FILES "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libmongoc/libmongoc-1.0-config.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/libmongoc-1.0" TYPE FILE FILES "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libmongoc/libmongoc-1.0-config-version.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/libmongoc-static-1.0" TYPE FILE FILES "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libmongoc/libmongoc-static-1.0-config.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/libmongoc-static-1.0" TYPE FILE FILES "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libmongoc/libmongoc-static-1.0-config-version.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libmongoc/build/cmake_install.cmake")
  include("/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libmongoc/examples/cmake_install.cmake")
  include("/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libmongoc/src/cmake_install.cmake")
  include("/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/src/libmongoc/tests/cmake_install.cmake")

endif()

