cmake_minimum_required(VERSION 2.8)
project(encrypt)
set( CMAKE_CXX_FLAGS "-std=c++11" )
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/lib/)

add_library(${PROJECT_NAME} SHARED
"../../src/lib_encrypt/aes/aes.cpp"
# "../../src/lib_encrypt/cjsonobject/cJSON.cpp"
"../../src/lib_encrypt/hex/hex.cpp"
"../../src/lib_encrypt/cjsonobject/cJSONcpp.cpp"
"../../src/lib_encrypt/cjsonobject/CJsonObject.cpp"
"../../src/lib_encrypt/aes_cpp.cpp"
"../../src/lib_encrypt/response_data.cpp"
)

# add_library(${PROJECT_NAME} SHARED
# "../../src/lib_encrypt/response_data.cpp"
# )

message("PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})


INSTALL(FILES ../../src/lib_encrypt/response_data.h
        DESTINATION ${PROJECT_SOURCE_DIR}/bin/include
        )

# target_link_libraries( encrypt )
