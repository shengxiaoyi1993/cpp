cmake_minimum_required(VERSION 2.8)

project(test_restclient)

set(INC_DIR ../../clone/restclient-cpp/lib/include/)
#set(LINK_DIR ../../lib/clone/restclient-cpp/lib/lib/)

include_directories(${INC_DIR}) # 头文件目录
#link_directories(${LINK_DIR})   # 库目录
#link_libraries(restclient-cpp)    # 要包含的库

add_executable(${PROJECT_NAME}
  "main.cpp"
  )
target_link_libraries(${PROJECT_NAME} -L/home/sxy/Github/clone/restclient-cpp/lib/lib -lrestclient-cpp)
