# Install script for directory: /home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-cxx-driver-3.4.0/src/mongocxx

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/usr")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mongocxx/v_noabi" TYPE DIRECTORY FILES "/home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-cxx-driver-3.4.0/src/mongocxx" FILES_MATCHING REGEX "/[^/]*\\.hpp$")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mongocxx/v_noabi/mongocxx/config" TYPE FILE FILES "/home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/src/mongocxx/config/export.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xruntimex" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmongocxx.so.3.4.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmongocxx.so._noabi"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/usr/lib64")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/src/mongocxx/libmongocxx.so.3.4.0"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/src/mongocxx/libmongocxx.so._noabi"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmongocxx.so.3.4.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmongocxx.so._noabi"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "/home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/src/bsoncxx:/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/usr/lib64:"
           NEW_RPATH "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/usr/lib64")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xruntimex" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmongocxx.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmongocxx.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmongocxx.so"
         RPATH "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/usr/lib64")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES "/home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/src/mongocxx/libmongocxx.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmongocxx.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmongocxx.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmongocxx.so"
         OLD_RPATH "/home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/src/bsoncxx:/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/usr/lib64:"
         NEW_RPATH "/home/sxy/Github/cpp/mongocpp/mongodb_driver/c/usr/lib64")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libmongocxx.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/libmongocxx-3.4.0" TYPE FILE FILES
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/src/mongocxx/libmongocxx-config.cmake"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/src/mongocxx/libmongocxx-config-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/src/mongocxx/config/cmake_install.cmake")
  include("/home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/src/mongocxx/test/cmake_install.cmake")

endif()

