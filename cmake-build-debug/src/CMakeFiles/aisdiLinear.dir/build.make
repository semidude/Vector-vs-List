# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /home/radek/clion-2017.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/radek/clion-2017.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/radek/Desktop/Vector-vs-List

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/radek/Desktop/Vector-vs-List/cmake-build-debug

# Include any dependencies generated for this target.
include src/CMakeFiles/aisdiLinear.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/aisdiLinear.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/aisdiLinear.dir/flags.make

src/CMakeFiles/aisdiLinear.dir/main.cpp.o: src/CMakeFiles/aisdiLinear.dir/flags.make
src/CMakeFiles/aisdiLinear.dir/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/radek/Desktop/Vector-vs-List/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/aisdiLinear.dir/main.cpp.o"
	cd /home/radek/Desktop/Vector-vs-List/cmake-build-debug/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/aisdiLinear.dir/main.cpp.o -c /home/radek/Desktop/Vector-vs-List/src/main.cpp

src/CMakeFiles/aisdiLinear.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aisdiLinear.dir/main.cpp.i"
	cd /home/radek/Desktop/Vector-vs-List/cmake-build-debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/radek/Desktop/Vector-vs-List/src/main.cpp > CMakeFiles/aisdiLinear.dir/main.cpp.i

src/CMakeFiles/aisdiLinear.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aisdiLinear.dir/main.cpp.s"
	cd /home/radek/Desktop/Vector-vs-List/cmake-build-debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/radek/Desktop/Vector-vs-List/src/main.cpp -o CMakeFiles/aisdiLinear.dir/main.cpp.s

src/CMakeFiles/aisdiLinear.dir/main.cpp.o.requires:

.PHONY : src/CMakeFiles/aisdiLinear.dir/main.cpp.o.requires

src/CMakeFiles/aisdiLinear.dir/main.cpp.o.provides: src/CMakeFiles/aisdiLinear.dir/main.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/aisdiLinear.dir/build.make src/CMakeFiles/aisdiLinear.dir/main.cpp.o.provides.build
.PHONY : src/CMakeFiles/aisdiLinear.dir/main.cpp.o.provides

src/CMakeFiles/aisdiLinear.dir/main.cpp.o.provides.build: src/CMakeFiles/aisdiLinear.dir/main.cpp.o


# Object files for target aisdiLinear
aisdiLinear_OBJECTS = \
"CMakeFiles/aisdiLinear.dir/main.cpp.o"

# External object files for target aisdiLinear
aisdiLinear_EXTERNAL_OBJECTS =

src/aisdiLinear: src/CMakeFiles/aisdiLinear.dir/main.cpp.o
src/aisdiLinear: src/CMakeFiles/aisdiLinear.dir/build.make
src/aisdiLinear: src/CMakeFiles/aisdiLinear.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/radek/Desktop/Vector-vs-List/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable aisdiLinear"
	cd /home/radek/Desktop/Vector-vs-List/cmake-build-debug/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/aisdiLinear.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/aisdiLinear.dir/build: src/aisdiLinear

.PHONY : src/CMakeFiles/aisdiLinear.dir/build

src/CMakeFiles/aisdiLinear.dir/requires: src/CMakeFiles/aisdiLinear.dir/main.cpp.o.requires

.PHONY : src/CMakeFiles/aisdiLinear.dir/requires

src/CMakeFiles/aisdiLinear.dir/clean:
	cd /home/radek/Desktop/Vector-vs-List/cmake-build-debug/src && $(CMAKE_COMMAND) -P CMakeFiles/aisdiLinear.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/aisdiLinear.dir/clean

src/CMakeFiles/aisdiLinear.dir/depend:
	cd /home/radek/Desktop/Vector-vs-List/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/radek/Desktop/Vector-vs-List /home/radek/Desktop/Vector-vs-List/src /home/radek/Desktop/Vector-vs-List/cmake-build-debug /home/radek/Desktop/Vector-vs-List/cmake-build-debug/src /home/radek/Desktop/Vector-vs-List/cmake-build-debug/src/CMakeFiles/aisdiLinear.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/aisdiLinear.dir/depend

