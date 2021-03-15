# code copied from https://crascit.com/2015/07/25/cmake-gtest/
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(googlelog-download NONE)

include(ExternalProject)

ExternalProject_Add(
  googlelog
  SOURCE_DIR "@GOOGLELOG_DOWNLOAD_ROOT@/googlelog-src"
  BINARY_DIR "@GOOGLELOG_DOWNLOAD_ROOT@/googlelog-build"
  URL
    ftp://pub:9900@192.168.1.238/lib/glog-0.4.0.zip
  # GIT_REPOSITORY
  #   https://github.com/google/glog.git
  # GIT_TAG
  #   v0.4.0
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  TEST_COMMAND ""
  # -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR}/install
  )
