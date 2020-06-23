# cmake_minimum_required(VERSION 2.8)
# project(example)
# # set( CMAKE_CXX_FLAGS "-std=c++11" )
# add_executable(${PROJECT_NAME} "../src/main.c")
# INCLUDE_DIRECTORIES("/usr/include/gtk-2.0/" "/usr/include/glib-2.0/")
#
# message("PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
# target_link_libraries( example )


cmake_minimum_required (VERSION 2.8)
project (hello-gtk)
# set( CMAKE_CXX_FLAGS "-std=c++11" )
set(CMAKE_SYSROOT /home/sxy/ultra96_v1/ultra96/images/bsp2018.3/build/ultra96v1_full_2018_3/images/linux/)
set(CMAKE_FIND_ROOT_PATH
/home/sxy/ultra96_v1/ultra96/images/bsp2018.3/build/ultra96v1_full_2018_3/images/linux/)
SET(COMBILEPATH "/home/sxy/Software/petalinux/tools/linux-i386/aarch64-linux-gnu/bin/" CACHE STRING "Some user-specified option")
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_C_COMPILER ${COMBILEPATH}aarch64-linux-gnu-gcc)
SET(CMAKE_CXX_COMPILER ${COMBILEPATH}aarch64-linux-gnu-c++)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)


if (CMAKE_SYSTEM_NAME MATCHES "Linux")
  #  find_package(PkgConfig REQUIRED)
    find_package(GTK2 REQUIRED )
    message(STATUS "----- GTK2_INCLUDE_DIRS: ${GTK2_INCLUDE_DIRS}")
    message(STATUS "----- GKT3_LIBRARIES: ${GTK2_LIBRARIES}")
    message(STATUS "----- GTK2_LINK_LIBRARIES: ${GTK2_LINK_LIBRARIES}")
        include_directories(${GTK2_INCLUDE_DIRS})
        link_directories(${GTK2_LIBRARY_DIRS})
        list(APPEND FC_DEP_LIBS ${GTK2_LIBRARIES})
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    #export PKG_CONFIG_PATH="$(brew --prefix libffi)/lib/pkgconfig/"
    set(ENV{PKG_CONFIG_PATH} /usr/local/opt/libffi/lib/pkgconfig)
    find_package(PkgConfig REQUIRED)
        pkg_check_modules(GTK2 REQUIRED gtk+-2.0)
    message(STATUS "----- GKT3_LIBRARIES: ${GTK2_LIBRARIES}")
    message(STATUS "----- GTK2_LINK_LIBRARIES: ${GTK2_LINK_LIBRARIES}")
        include_directories(${GTK2_INCLUDE_DIRS})
    list(APPEND FC_DEP_LIBS ${GTK2_LINK_LIBRARIES})
endif()

add_executable (gtk-test ../src/main.c)

#add_definitions (${GTK2_CFLAGS_OTHER})
message(STATUS "----- ${GTK2_CFLAGS_OTHER}")
# -pthread

target_link_libraries (gtk-test ${FC_DEP_LIBS})



#cmake_minimum_required (VERSION 2.8)
#project (hello-gtk)

#if (CMAKE_SYSTEM_NAME MATCHES "Linux")
#    find_package(PkgConfig REQUIRED)
#	pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
#    message(STATUS "----- GTK3_INCLUDE_DIRS: ${GTK3_INCLUDE_DIRS}")
#    message(STATUS "----- GKT3_LIBRARIES: ${GTK3_LIBRARIES}")
#    message(STATUS "----- GTK3_LINK_LIBRARIES: ${GTK3_LINK_LIBRARIES}")
#	include_directories(${GTK3_INCLUDE_DIRS})
#	link_directories(${GTK3_LIBRARY_DIRS})
#	list(APPEND FC_DEP_LIBS ${GTK3_LIBRARIES})
#elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
#    #export PKG_CONFIG_PATH="$(brew --prefix libffi)/lib/pkgconfig/"
#    set(ENV{PKG_CONFIG_PATH} /usr/local/opt/libffi/lib/pkgconfig)
#    find_package(PkgConfig REQUIRED)
#	pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
#    message(STATUS "----- GKT3_LIBRARIES: ${GTK3_LIBRARIES}")
#    message(STATUS "----- GTK3_LINK_LIBRARIES: ${GTK3_LINK_LIBRARIES}")
#	include_directories(${GTK3_INCLUDE_DIRS})
#    list(APPEND FC_DEP_LIBS ${GTK3_LINK_LIBRARIES})
#endif()

#add_executable (gtk-test ../src/main.c)

##add_definitions (${GTK3_CFLAGS_OTHER})
#message(STATUS "----- ${GTK3_CFLAGS_OTHER}")
## -pthread

#target_link_libraries (gtk-test ${FC_DEP_LIBS})
