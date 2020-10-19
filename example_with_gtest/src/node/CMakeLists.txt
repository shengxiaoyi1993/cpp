add_library(node "")

target_sources(
    node
    PRIVATE
        node.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/node.h
    )

target_include_directories(
    node
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
    )
