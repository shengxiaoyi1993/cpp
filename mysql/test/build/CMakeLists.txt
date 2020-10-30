cmake_minimum_required(VERSION 2.8)

set( CMAKE_CXX_FLAGS "-std=c++11" )
set(CMAKE_BUILD_TYPE "Debug")

project(test_uvss_label)
include_directories("${PROJECT_SOURCE_DIR}/../lib/uvss_label_distance/include/")
link_directories("${PROJECT_SOURCE_DIR}/../lib/uvss_label_distance/lib/")
include_directories("${PROJECT_SOURCE_DIR}/../../../../opencv_cpp/start/lib/opencv-3.4.1/include/")
link_directories("${PROJECT_SOURCE_DIR}/../../../../opencv_cpp/start/lib/opencv-3.4.1/lib64")
link_directories("/home/sxy/Software/Qt5.9.7/5.9.7/gcc_64/lib/")

MESSAGE(${PROJECT_SOURCE_DIR})
add_executable(${PROJECT_NAME}
    "../src/main.cpp"
    "../src/mysql.cpp"
    "../src/mysql.cpp"
#    "../lib/clog/log.c"
    "../../../../opencv_cpp/learn/imagesort/src/basic/cJSON.c"
    "../lib_copy/licenseGenerator/licensegenerator.cpp"
    "../lib_copy/kmeans_cluster/kmeanscluster.cpp"

    )
target_link_libraries(${PROJECT_NAME} -luvss_label_distance -L/usr/lib64/mysql
    -lmysqlclient -lmysqlcppconn -lpthread -lm -ldl -lopencv_highgui -lopencv_core -lopencv_imgcodecs -lopencv_imgproc)
