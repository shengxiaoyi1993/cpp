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

# Include any dependencies generated for this target.
include examples/mongocxx/CMakeFiles/query_projection.dir/depend.make

# Include the progress variables for this target.
include examples/mongocxx/CMakeFiles/query_projection.dir/progress.make

# Include the compile flags for this target's objects.
include examples/mongocxx/CMakeFiles/query_projection.dir/flags.make

examples/mongocxx/CMakeFiles/query_projection.dir/query_projection.cpp.o: examples/mongocxx/CMakeFiles/query_projection.dir/flags.make
examples/mongocxx/CMakeFiles/query_projection.dir/query_projection.cpp.o: /home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-cxx-driver-3.4.0/examples/mongocxx/query_projection.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/mongocxx/CMakeFiles/query_projection.dir/query_projection.cpp.o"
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples/mongocxx && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/query_projection.dir/query_projection.cpp.o -c /home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-cxx-driver-3.4.0/examples/mongocxx/query_projection.cpp

examples/mongocxx/CMakeFiles/query_projection.dir/query_projection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/query_projection.dir/query_projection.cpp.i"
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples/mongocxx && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-cxx-driver-3.4.0/examples/mongocxx/query_projection.cpp > CMakeFiles/query_projection.dir/query_projection.cpp.i

examples/mongocxx/CMakeFiles/query_projection.dir/query_projection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/query_projection.dir/query_projection.cpp.s"
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples/mongocxx && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-cxx-driver-3.4.0/examples/mongocxx/query_projection.cpp -o CMakeFiles/query_projection.dir/query_projection.cpp.s

# Object files for target query_projection
query_projection_OBJECTS = \
"CMakeFiles/query_projection.dir/query_projection.cpp.o"

# External object files for target query_projection
query_projection_EXTERNAL_OBJECTS =

examples/mongocxx/query_projection: examples/mongocxx/CMakeFiles/query_projection.dir/query_projection.cpp.o
examples/mongocxx/query_projection: examples/mongocxx/CMakeFiles/query_projection.dir/build.make
examples/mongocxx/query_projection: src/mongocxx/libmongocxx.so.3.4.0
examples/mongocxx/query_projection: src/bsoncxx/libbsoncxx.so.3.4.0
examples/mongocxx/query_projection: examples/mongocxx/CMakeFiles/query_projection.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable query_projection"
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples/mongocxx && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/query_projection.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/mongocxx/CMakeFiles/query_projection.dir/build: examples/mongocxx/query_projection

.PHONY : examples/mongocxx/CMakeFiles/query_projection.dir/build

examples/mongocxx/CMakeFiles/query_projection.dir/clean:
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples/mongocxx && $(CMAKE_COMMAND) -P CMakeFiles/query_projection.dir/cmake_clean.cmake
.PHONY : examples/mongocxx/CMakeFiles/query_projection.dir/clean

examples/mongocxx/CMakeFiles/query_projection.dir/depend:
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-cxx-driver-3.4.0 /home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-cxx-driver-3.4.0/examples/mongocxx /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples/mongocxx /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples/mongocxx/CMakeFiles/query_projection.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/mongocxx/CMakeFiles/query_projection.dir/depend

