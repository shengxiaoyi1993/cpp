add_library(example "")

target_sources(
    example
    PRIVATE
        example.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/example.h
    )

target_include_directories(
    example
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
    )

add_library(cookproc "")
target_sources(
    cookproc
    PRIVATE
        CookProc.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/CookProc.h
    )

target_include_directories(
    cookproc
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
    )
