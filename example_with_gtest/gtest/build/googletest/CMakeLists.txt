# code copied from https://crascit.com/2015/07/25/cmake-gtest/
# 该模块用于复制到另一目录下运行
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(googletest-download NONE)

include(ExternalProject)
#/home/sxy/Github/cpp/example_with_gtest/gtest/build/googletest 由configure_file()完成替换
ExternalProject_Add(
  googletest
  SOURCE_DIR "/home/sxy/Github/cpp/example_with_gtest/gtest/build/googletest/googletest-src"
  BINARY_DIR "/home/sxy/Github/cpp/example_with_gtest/gtest/build/googletest/googletest-build"
  URL
    ftp://pub:9900@192.168.1.238/lib/googletest-release-1.8.0.zip
    # https://github.com/google/googletest.git
  # GIT_TAG
  #   release-1.8.0
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  TEST_COMMAND ""
  )
