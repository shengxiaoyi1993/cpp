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

# Utility rule file for run-examples.

# Include the progress variables for this target.
include examples/CMakeFiles/run-examples.dir/progress.make

examples/CMakeFiles/run-examples:


run-examples: examples/CMakeFiles/run-examples
run-examples: examples/CMakeFiles/run-examples.dir/build.make
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples && mongocxx/aggregate
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples && mongocxx/bulk_write
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples && mongocxx/connect
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples && mongocxx/create
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples && mongocxx/document_validation
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples && mongocxx/exception
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples && mongocxx/get_values_from_documents
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples && mongocxx/gridfs
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples && mongocxx/index
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples && mongocxx/inserted_id
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples && mongocxx/instance_management
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples && mongocxx/aggregation_examples
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples && mongocxx/runcommand_examples
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples && mongocxx/index_examples
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples && mongocxx/documentation_examples
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples && mongocxx/usage_overview
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples && mongocxx/query_projection
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples && mongocxx/query
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples && mongocxx/remove
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples && mongocxx/tailable_cursor
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples && mongocxx/update
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples && mongocxx/view_or_value_variant
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples && mongocxx/pool
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples && bsoncxx/builder_core
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples && bsoncxx/builder_basic
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples && bsoncxx/builder_stream
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples && bsoncxx/builder_stream_customization
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples && bsoncxx/decimal128
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples && bsoncxx/getting_values
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples && bsoncxx/view_and_value
.PHONY : run-examples

# Rule to build all files generated by this target.
examples/CMakeFiles/run-examples.dir/build: run-examples

.PHONY : examples/CMakeFiles/run-examples.dir/build

examples/CMakeFiles/run-examples.dir/clean:
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples && $(CMAKE_COMMAND) -P CMakeFiles/run-examples.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/run-examples.dir/clean

examples/CMakeFiles/run-examples.dir/depend:
	cd /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-cxx-driver-3.4.0 /home/sxy/Github/cpp/mongocpp/mongodb_driver/mongo-cxx-driver-3.4.0/examples /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples /home/sxy/Github/cpp/mongocpp/mongodb_driver/cxx/examples/CMakeFiles/run-examples.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/run-examples.dir/depend

