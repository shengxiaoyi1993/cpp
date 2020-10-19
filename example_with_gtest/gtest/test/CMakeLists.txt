add_executable(
    unit_tests
    example_add.cpp
    example_subtract.cpp
    cookproc_test.cpp
    node_test.cpp
    )

target_link_libraries(
    unit_tests
    gtest_main
    example
    cookproc
    node
    )

add_test(
  NAME
    unit
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
  )
