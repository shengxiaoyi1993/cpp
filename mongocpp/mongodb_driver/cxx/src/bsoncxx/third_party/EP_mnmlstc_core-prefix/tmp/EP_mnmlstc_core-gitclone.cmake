if("v1.1.0" STREQUAL "")
  message(FATAL_ERROR "Tag for git checkout should not be empty.")
endif()

set(run 0)

if("/home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/src/bsoncxx/third_party/EP_mnmlstc_core-prefix/src/EP_mnmlstc_core-stamp/EP_mnmlstc_core-gitinfo.txt" IS_NEWER_THAN "/home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/src/bsoncxx/third_party/EP_mnmlstc_core-prefix/src/EP_mnmlstc_core-stamp/EP_mnmlstc_core-gitclone-lastrun.txt")
  set(run 1)
endif()

if(NOT run)
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: '/home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/src/bsoncxx/third_party/EP_mnmlstc_core-prefix/src/EP_mnmlstc_core-stamp/EP_mnmlstc_core-gitclone-lastrun.txt'")
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E remove_directory "/home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/src/bsoncxx/third_party/EP_mnmlstc_core-prefix/src/EP_mnmlstc_core"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: '/home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/src/bsoncxx/third_party/EP_mnmlstc_core-prefix/src/EP_mnmlstc_core'")
endif()

set(git_options)

# disable cert checking if explicitly told not to do it
set(tls_verify "")
if(NOT "x" STREQUAL "x" AND NOT tls_verify)
  list(APPEND git_options
    -c http.sslVerify=false)
endif()

set(git_clone_options)

set(git_shallow "")
if(git_shallow)
  list(APPEND git_clone_options --depth 1 --no-single-branch)
endif()

set(git_progress "")
if(git_progress)
  list(APPEND git_clone_options --progress)
endif()

set(git_config "")
foreach(config IN LISTS git_config)
  list(APPEND git_clone_options --config ${config})
endforeach()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "/usr/bin/git" ${git_options} clone ${git_clone_options} --origin "origin" "https://github.com/mnmlstc/core" "EP_mnmlstc_core"
    WORKING_DIRECTORY "/home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/src/bsoncxx/third_party/EP_mnmlstc_core-prefix/src"
    RESULT_VARIABLE error_code
    )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once:
          ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/mnmlstc/core'")
endif()

execute_process(
  COMMAND "/usr/bin/git" ${git_options} checkout v1.1.0 
  WORKING_DIRECTORY "/home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/src/bsoncxx/third_party/EP_mnmlstc_core-prefix/src/EP_mnmlstc_core"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'v1.1.0'")
endif()

execute_process(
  COMMAND "/usr/bin/git" ${git_options} submodule init 
  WORKING_DIRECTORY "/home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/src/bsoncxx/third_party/EP_mnmlstc_core-prefix/src/EP_mnmlstc_core"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to init submodules in: '/home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/src/bsoncxx/third_party/EP_mnmlstc_core-prefix/src/EP_mnmlstc_core'")
endif()

execute_process(
  COMMAND "/usr/bin/git" ${git_options} submodule update --recursive --init 
  WORKING_DIRECTORY "/home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/src/bsoncxx/third_party/EP_mnmlstc_core-prefix/src/EP_mnmlstc_core"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: '/home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/src/bsoncxx/third_party/EP_mnmlstc_core-prefix/src/EP_mnmlstc_core'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/src/bsoncxx/third_party/EP_mnmlstc_core-prefix/src/EP_mnmlstc_core-stamp/EP_mnmlstc_core-gitinfo.txt"
    "/home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/src/bsoncxx/third_party/EP_mnmlstc_core-prefix/src/EP_mnmlstc_core-stamp/EP_mnmlstc_core-gitclone-lastrun.txt"
  WORKING_DIRECTORY "/home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/src/bsoncxx/third_party/EP_mnmlstc_core-prefix/src/EP_mnmlstc_core"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: '/home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/src/bsoncxx/third_party/EP_mnmlstc_core-prefix/src/EP_mnmlstc_core-stamp/EP_mnmlstc_core-gitclone-lastrun.txt'")
endif()

