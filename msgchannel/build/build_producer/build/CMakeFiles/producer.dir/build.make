# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sxy/Github/cpp/msgchannel/build/build_producer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sxy/Github/cpp/msgchannel/build/build_producer/build

# Include any dependencies generated for this target.
include CMakeFiles/producer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/producer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/producer.dir/flags.make

CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/main/msgchannel.cpp.o: CMakeFiles/producer.dir/flags.make
CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/main/msgchannel.cpp.o: /home/sxy/Github/cpp/msgchannel/src/main/msgchannel.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/sxy/Github/cpp/msgchannel/build/build_producer/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/main/msgchannel.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/main/msgchannel.cpp.o -c /home/sxy/Github/cpp/msgchannel/src/main/msgchannel.cpp

CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/main/msgchannel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/main/msgchannel.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/sxy/Github/cpp/msgchannel/src/main/msgchannel.cpp > CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/main/msgchannel.cpp.i

CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/main/msgchannel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/main/msgchannel.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/sxy/Github/cpp/msgchannel/src/main/msgchannel.cpp -o CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/main/msgchannel.cpp.s

CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/main/msgchannel.cpp.o.requires:
.PHONY : CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/main/msgchannel.cpp.o.requires

CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/main/msgchannel.cpp.o.provides: CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/main/msgchannel.cpp.o.requires
	$(MAKE) -f CMakeFiles/producer.dir/build.make CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/main/msgchannel.cpp.o.provides.build
.PHONY : CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/main/msgchannel.cpp.o.provides

CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/main/msgchannel.cpp.o.provides.build: CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/main/msgchannel.cpp.o

CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/example/producer/producer.cpp.o: CMakeFiles/producer.dir/flags.make
CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/example/producer/producer.cpp.o: /home/sxy/Github/cpp/msgchannel/src/example/producer/producer.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/sxy/Github/cpp/msgchannel/build/build_producer/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/example/producer/producer.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/example/producer/producer.cpp.o -c /home/sxy/Github/cpp/msgchannel/src/example/producer/producer.cpp

CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/example/producer/producer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/example/producer/producer.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/sxy/Github/cpp/msgchannel/src/example/producer/producer.cpp > CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/example/producer/producer.cpp.i

CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/example/producer/producer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/example/producer/producer.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/sxy/Github/cpp/msgchannel/src/example/producer/producer.cpp -o CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/example/producer/producer.cpp.s

CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/example/producer/producer.cpp.o.requires:
.PHONY : CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/example/producer/producer.cpp.o.requires

CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/example/producer/producer.cpp.o.provides: CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/example/producer/producer.cpp.o.requires
	$(MAKE) -f CMakeFiles/producer.dir/build.make CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/example/producer/producer.cpp.o.provides.build
.PHONY : CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/example/producer/producer.cpp.o.provides

CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/example/producer/producer.cpp.o.provides.build: CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/example/producer/producer.cpp.o

# Object files for target producer
producer_OBJECTS = \
"CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/main/msgchannel.cpp.o" \
"CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/example/producer/producer.cpp.o"

# External object files for target producer
producer_EXTERNAL_OBJECTS =

producer: CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/main/msgchannel.cpp.o
producer: CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/example/producer/producer.cpp.o
producer: CMakeFiles/producer.dir/build.make
producer: CMakeFiles/producer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable producer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/producer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/producer.dir/build: producer
.PHONY : CMakeFiles/producer.dir/build

CMakeFiles/producer.dir/requires: CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/main/msgchannel.cpp.o.requires
CMakeFiles/producer.dir/requires: CMakeFiles/producer.dir/home/sxy/Github/cpp/msgchannel/src/example/producer/producer.cpp.o.requires
.PHONY : CMakeFiles/producer.dir/requires

CMakeFiles/producer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/producer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/producer.dir/clean

CMakeFiles/producer.dir/depend:
	cd /home/sxy/Github/cpp/msgchannel/build/build_producer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sxy/Github/cpp/msgchannel/build/build_producer /home/sxy/Github/cpp/msgchannel/build/build_producer /home/sxy/Github/cpp/msgchannel/build/build_producer/build /home/sxy/Github/cpp/msgchannel/build/build_producer/build /home/sxy/Github/cpp/msgchannel/build/build_producer/build/CMakeFiles/producer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/producer.dir/depend

