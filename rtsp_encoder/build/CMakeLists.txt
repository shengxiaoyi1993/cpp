
cmake_minimum_required(VERSION 2.8)
project(rtsp_encoder)
set( CMAKE_CXX_FLAGS "-std=c++11" )

add_executable(${PROJECT_NAME}
"../src/main.cpp"
"../src/AVPacketBuffer.cpp"
"../src/mediaproc.cpp"
"../src/rtsp_encoder.cpp"
)

string(REGEX REPLACE "(.+)\\rtsp_encoder.*" "\\1" PROJECT_INIT_PATH ${PROJECT_SOURCE_DIR})

message("PROJECT_INIT_PATH:${PROJECT_INIT_PATH}")

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
	MESSAGE(STATUS "current platform: Linux ")
  set(Opencv_INCLUDE_DIRS "${PROJECT_INIT_PATH}../opencv_cpp/start/lib/opencv-3.4.1//include")
  set(Opencv_LIBRARIES_DIRS "${PROJECT_INIT_PATH}../opencv_cpp/start/lib/opencv-3.4.1//lib64")
  FILE(GLOB_RECURSE Opencv_LIBs "${PROJECT_INIT_PATH}../opencv_cpp/start/lib/opencv-3.4.1//lib64/*.so")
  set(FFMPEG_INCLUDE_DIRS "${PROJECT_INIT_PATH}rtsp_encoder/lib/ffmpeg/include")
  set(FFMPEG_LIBRARIES_DIRS "${PROJECT_INIT_PATH}rtsp_encoder/lib/ffmpeg/so")
  FILE(GLOB_RECURSE FFMPEG_LIBs "${PROJECT_INIT_PATH}rtsp_encoder/lib/ffmpeg/so/*.so*")

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
  MESSAGE(STATUS "current platform: Windows")
  set(Opencv_INCLUDE_DIRS "${PROJECT_INIT_PATH}../opencv_cpp/start/lib/opencv-3.4.1//include")
  set(Opencv_LIBRARIES_DIRS "${PROJECT_INIT_PATH}../opencv_cpp/start/lib/opencv-3.4.1//x64/mingw/bin")
  FILE(GLOB_RECURSE Opencv_LIBs "${PROJECT_INIT_PATH}../opencv_cpp/start/lib/opencv-3.4.1//x64/mingw/bin/*.dll")
  set(FFMPEG_INCLUDE_DIRS "${PROJECT_INIT_PATH}rtsp_encoder/lib/ffmpeg/include")
  set(FFMPEG_LIBRARIES_DIRS "${PROJECT_INIT_PATH}rtsp_encoder/lib/ffmpeg/dll")
  FILE(GLOB_RECURSE FFMPEG_LIBs "${PROJECT_INIT_PATH}rtsp_encoder/lib/ffmpeg/dll/*.dll")
  file(COPY ${PROJECT_INIT_PATH}../opencv_cpp/start/lib/opencv-3.4.1//x64/mingw/bin/libopencv_core341.dll DESTINATION . FOLLOW_SYMLINK_CHAIN)
  file(COPY ${PROJECT_INIT_PATH}../opencv_cpp/start/lib/opencv-3.4.1//x64/mingw/bin/libopencv_highgui341.dll DESTINATION . FOLLOW_SYMLINK_CHAIN)
  file(COPY ${PROJECT_INIT_PATH}../opencv_cpp/start/lib/opencv-3.4.1//x64/mingw/bin/libopencv_imgproc341.dll DESTINATION . FOLLOW_SYMLINK_CHAIN)
  file(COPY ${PROJECT_INIT_PATH}../opencv_cpp/start/lib/opencv-3.4.1//x64/mingw/bin/libopencv_imgcodecs341.dll DESTINATION . FOLLOW_SYMLINK_CHAIN)
  file(COPY ${PROJECT_INIT_PATH}rtsp_encoder/lib/ffmpeg/dll/avcodec-56.dll DESTINATION . FOLLOW_SYMLINK_CHAIN)
  file(COPY ${PROJECT_INIT_PATH}rtsp_encoder/lib/ffmpeg/dll/avdevice-56.dll DESTINATION . FOLLOW_SYMLINK_CHAIN)
  file(COPY ${PROJECT_INIT_PATH}rtsp_encoder/lib/ffmpeg/dll/avfilter-5.dll DESTINATION . FOLLOW_SYMLINK_CHAIN)
  file(COPY ${PROJECT_INIT_PATH}rtsp_encoder/lib/ffmpeg/dll/avformat-56.dll DESTINATION . FOLLOW_SYMLINK_CHAIN)
  file(COPY ${PROJECT_INIT_PATH}rtsp_encoder/lib/ffmpeg/dll/avutil-54.dll DESTINATION . FOLLOW_SYMLINK_CHAIN)
  file(COPY ${PROJECT_INIT_PATH}rtsp_encoder/lib/ffmpeg/dll/postproc-53.dll DESTINATION . FOLLOW_SYMLINK_CHAIN)
  file(COPY ${PROJECT_INIT_PATH}rtsp_encoder/lib/ffmpeg/dll/swresample-1.dll DESTINATION . FOLLOW_SYMLINK_CHAIN)
  file(COPY ${PROJECT_INIT_PATH}rtsp_encoder/lib/ffmpeg/dll/swscale-3.dll DESTINATION . FOLLOW_SYMLINK_CHAIN)
ELSE ()
	MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF ()



message(${Opencv_LIBRARIES_DIRS})
include_directories(${Opencv_INCLUDE_DIRS} ${FFMPEG_INCLUDE_DIRS})
link_directories(${Opencv_LIBRARIES_DIRS} ${FFMPEG_LIBRARIES_DIRS})
target_link_libraries( rtsp_encoder "${Opencv_LIBs}" "${FFMPEG_LIBs}"  -pthread)
