# the following code to fetch googlelog
# is inspired by and adapted after https://crascit.com/2015/07/25/cmake-gtest/
# download and unpack googlelog at configure time

macro(fetch_googlelog _download_module_path _download_root)
    set(GOOGLELOG_DOWNLOAD_ROOT ${_download_root})
    configure_file(
        ${_download_module_path}/googlelog-download.cmake
        ${_download_root}/CMakeLists.txt
        @ONLY
        )
    unset(GOOGLELOG_DOWNLOAD_ROOT)

    execute_process(
        COMMAND
            "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY
            ${_download_root}
        )
    execute_process(
        COMMAND
            "${CMAKE_COMMAND}" --build .
        WORKING_DIRECTORY
            ${_download_root}
        )

    # adds the targers: gtest, gtest_main, gmock, gmock_main
    add_subdirectory(
        ${_download_root}/googlelog-src
        ${_download_root}/googlelog-build
        )
endmacro()
