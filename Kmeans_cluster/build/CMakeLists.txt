cmake_minimum_required(VERSION 2.8)
project(example)
set( CMAKE_CXX_FLAGS "-std=c++11" )
set(CMAKE_BUILD_TYPE "Debug")
ADD_DEFINITIONS(-D DEBUG_SYSLOGGER)
include_directories("${PROJECT_SOURCE_DIR}/../../../opencv_cpp/start/lib/opencv-3.4.1/include/")
link_directories("${PROJECT_SOURCE_DIR}/../../../opencv_cpp/start/lib/opencv-3.4.1/lib64")
link_directories("/home/sxy/Software/Qt5.9.7/5.9.7/gcc_64/lib/")

add_executable(${PROJECT_NAME} "../src/main.cpp"
 "../src/kmeans_cluster/kmeanscluster.cpp"
 "../lib_copy/syslogger/syslogger.cpp"

)

message("PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
target_link_libraries( example -lopencv_highgui -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -lopencv_video)
