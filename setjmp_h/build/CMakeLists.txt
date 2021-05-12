cmake_minimum_required (VERSION 3.0.2)
project (setjmp_h VERSION 1.0 LANGUAGES C)

#find_package (glog 0.5.0 REQUIRED)

add_executable(${PROJECT_NAME} "../src/main.c")

# add_executable (${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} )
