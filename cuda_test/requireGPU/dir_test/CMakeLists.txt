cmake_minimum_required(VERSION 2.8)
PROJECT(testCUDA)
FIND_PACKAGE(CUDA REQUIRED)
INCLUDE_DIRECTORIES(
./
${CUDA_INCLUDE_DIRS}
)
SET(CMAKE_C_COMPILER g++)
add_compile_options(-std=c++11)
add_compile_options(-g)
set(SRC_LIST test1.cu)
CUDA_ADD_EXECUTABLE(testCUDA ${SRC_LIST})
target_link_libraries(testCUDA ${CUDA_LIBRARIES})

