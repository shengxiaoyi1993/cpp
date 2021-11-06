# cmake_minimum_required (VERSION 3.0.2)
# project (myproj VERSION 1.0)
#
# # find_package (glog 0.5.0 REQUIRED)
# #
# # include(${CMAKE_CURRENT_SOURCE_DIR}/../)
# #
#
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../glog)
#
# add_executable(${PROJECT_NAME} "../src/main.cpp""../src/export.cpp")
#
# # add_executable (myapp main.cpp)
# target_link_libraries (${PROJECT_NAME}  glog::glog)



cmake_minimum_required (VERSION 3.0.2)
include(${CMAKE_CURRENT_SOURCE_DIR}/../glog/cmake/common_define.cmake)

project (myproj VERSION 1.0)

# find_package (glog 0.5.0 REQUIRED)
#
message("CMAKE_CURRENT_SOURCE_DIR:" ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../glog/ ${CMAKE_CURRENT_BINARY_DIR}/build/glog.out)


add_executable(${PROJECT_NAME}
"../src/main.cpp"
"../src/export.cpp")

# add_executable (myapp main.cpp)
target_link_libraries (${PROJECT_NAME}  glog::glog)
set( CMAKE_BUILD_TYPE RELEASE )

