
cmake_minimum_required (VERSION 2.8)
project (gtk_screenshoot)
set( CMAKE_CXX_FLAGS "-std=c++11" )

# if (CMAKE_SYSTEM_NAME MATCHES "Linux")
#   #  find_package(PkgConfig REQUIRED)
#     find_package(GTK2 REQUIRED )
#     message(STATUS "----- GTK2_INCLUDE_DIRS: ${GTK2_INCLUDE_DIRS}")
#     message(STATUS "----- GKT3_LIBRARIES: ${GTK2_LIBRARIES}")
#     message(STATUS "----- GTK2_LINK_LIBRARIES: ${GTK2_LINK_LIBRARIES}")
#         include_directories(${GTK2_INCLUDE_DIRS})
#         link_directories(${GTK2_LIBRARY_DIRS})
#         list(APPEND FC_DEP_LIBS ${GTK2_LIBRARIES})
# elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
#     #export PKG_CONFIG_PATH="$(brew --prefix libffi)/lib/pkgconfig/"
#     set(ENV{PKG_CONFIG_PATH} /usr/local/opt/libffi/lib/pkgconfig)
#     find_package(PkgConfig REQUIRED)
#         pkg_check_modules(GTK2 REQUIRED gtk+-2.0)
#     message(STATUS "----- GKT3_LIBRARIES: ${GTK2_LIBRARIES}")
#     message(STATUS "----- GTK2_LINK_LIBRARIES: ${GTK2_LINK_LIBRARIES}")
#         include_directories(${GTK2_INCLUDE_DIRS})
#     list(APPEND FC_DEP_LIBS ${GTK2_LINK_LIBRARIES})
# endif()

# find_package(GTK2  )
# message(STATUS "----- GTK2_INCLUDE_DIRS: ${GTK2_INCLUDE_DIRS}")
# message(STATUS "----- GKT3_LIBRARIES: ${GTK2_LIBRARIES}")
# message(STATUS "----- GTK2_LINK_LIBRARIES: ${GTK2_LINK_LIBRARIES}")
# include_directories(${GTK2_INCLUDE_DIRS})
# link_directories(${GTK2_LIBRARY_DIRS})
# list(APPEND FC_DEP_LIBS ${GTK2_LIBRARIES})
# set(gtk_INCLUDE_DIRS "/mingw64/include/gtk-3.0/")
# message(${gtk_INCLUDE_DIRS})
#
#
find_package(PkgConfig)
pkg_search_module(GTK3 REQUIRED gtk+-3.0)
MESSAGE(STATUS "GTK3 dirs:" ${GTK3_INCLUDE_DIRS})
MESSAGE(STATUS "GTK3 lib:" ${GTK3_LIBRARIES})
include_directories(${GTK3_INCLUDE_DIRS})
# link_directories(${GTK3_LIBRARY_DIRS})
list(APPEND FC_DEP_LIBS ${GTK3_LIBRARIES})

add_executable (gtk_screenshoot ../src/main.cpp)


# include_directories(${gtk_INCLUDE_DIRS})

add_definitions (${GTK2_CFLAGS_OTHER})
message(STATUS "----- ${GTK3_CFLAGS_OTHER}")
# -pthread

target_link_libraries (gtk_screenshoot ${FC_DEP_LIBS} -pthread)
