cmake_minimum_required(VERSION 2.8)
project(hand_test)
set( CMAKE_CXX_FLAGS "-std=c++11" )
add_executable(${PROJECT_NAME}
  "../src/main.cpp"
  "../src/hand.cpp"
  "../src/finger.cpp"
  "../src/basic.cpp"
  "../src/handgesturegame.cpp"
  )
message("PROJECT_SOURCE_DIR: "${PROJECT_SOURCE_DIR})
target_link_libraries( hand_test )
