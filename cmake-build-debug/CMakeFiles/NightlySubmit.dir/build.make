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

# Utility rule file for NightlySubmit.

# Include the progress variables for this target.
include CMakeFiles/NightlySubmit.dir/progress.make

CMakeFiles/NightlySubmit:
	/home/radek/clion-2017.3/bin/cmake/bin/ctest -D NightlySubmit

NightlySubmit: CMakeFiles/NightlySubmit
NightlySubmit: CMakeFiles/NightlySubmit.dir/build.make

.PHONY : NightlySubmit

# Rule to build all files generated by this target.
CMakeFiles/NightlySubmit.dir/build: NightlySubmit

.PHONY : CMakeFiles/NightlySubmit.dir/build

CMakeFiles/NightlySubmit.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/NightlySubmit.dir/cmake_clean.cmake
.PHONY : CMakeFiles/NightlySubmit.dir/clean

CMakeFiles/NightlySubmit.dir/depend:
	cd /home/radek/Desktop/Vector-vs-List/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/radek/Desktop/Vector-vs-List /home/radek/Desktop/Vector-vs-List /home/radek/Desktop/Vector-vs-List/cmake-build-debug /home/radek/Desktop/Vector-vs-List/cmake-build-debug /home/radek/Desktop/Vector-vs-List/cmake-build-debug/CMakeFiles/NightlySubmit.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/NightlySubmit.dir/depend

