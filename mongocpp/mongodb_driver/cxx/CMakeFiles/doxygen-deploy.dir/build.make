# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-cxx-driver-3.4.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx

# Utility rule file for doxygen-deploy.

# Include the progress variables for this target.
include CMakeFiles/doxygen-deploy.dir/progress.make

CMakeFiles/doxygen-deploy:
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-cxx-driver-3.4.0 && etc/deploy-to-ghpages.pl --doxygen git@github.com:mongodb/mongo-cxx-driver

doxygen-deploy: CMakeFiles/doxygen-deploy
doxygen-deploy: CMakeFiles/doxygen-deploy.dir/build.make

.PHONY : doxygen-deploy

# Rule to build all files generated by this target.
CMakeFiles/doxygen-deploy.dir/build: doxygen-deploy

.PHONY : CMakeFiles/doxygen-deploy.dir/build

CMakeFiles/doxygen-deploy.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/doxygen-deploy.dir/cmake_clean.cmake
.PHONY : CMakeFiles/doxygen-deploy.dir/clean

CMakeFiles/doxygen-deploy.dir/depend:
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-cxx-driver-3.4.0 /home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-cxx-driver-3.4.0 /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/CMakeFiles/doxygen-deploy.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/doxygen-deploy.dir/depend
