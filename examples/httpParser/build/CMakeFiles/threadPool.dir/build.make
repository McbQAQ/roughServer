# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zzx/roughServer/examples/httpParser

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zzx/roughServer/examples/httpParser/build

# Include any dependencies generated for this target.
include CMakeFiles/threadPool.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/threadPool.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/threadPool.dir/flags.make

CMakeFiles/threadPool.dir/main.cc.o: CMakeFiles/threadPool.dir/flags.make
CMakeFiles/threadPool.dir/main.cc.o: ../main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zzx/roughServer/examples/httpParser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/threadPool.dir/main.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/threadPool.dir/main.cc.o -c /home/zzx/roughServer/examples/httpParser/main.cc

CMakeFiles/threadPool.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/threadPool.dir/main.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zzx/roughServer/examples/httpParser/main.cc > CMakeFiles/threadPool.dir/main.cc.i

CMakeFiles/threadPool.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/threadPool.dir/main.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zzx/roughServer/examples/httpParser/main.cc -o CMakeFiles/threadPool.dir/main.cc.s

CMakeFiles/threadPool.dir/main.cc.o.requires:

.PHONY : CMakeFiles/threadPool.dir/main.cc.o.requires

CMakeFiles/threadPool.dir/main.cc.o.provides: CMakeFiles/threadPool.dir/main.cc.o.requires
	$(MAKE) -f CMakeFiles/threadPool.dir/build.make CMakeFiles/threadPool.dir/main.cc.o.provides.build
.PHONY : CMakeFiles/threadPool.dir/main.cc.o.provides

CMakeFiles/threadPool.dir/main.cc.o.provides.build: CMakeFiles/threadPool.dir/main.cc.o


CMakeFiles/threadPool.dir/home/zzx/roughServer/src/httpParser.cc.o: CMakeFiles/threadPool.dir/flags.make
CMakeFiles/threadPool.dir/home/zzx/roughServer/src/httpParser.cc.o: /home/zzx/roughServer/src/httpParser.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zzx/roughServer/examples/httpParser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/threadPool.dir/home/zzx/roughServer/src/httpParser.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/threadPool.dir/home/zzx/roughServer/src/httpParser.cc.o -c /home/zzx/roughServer/src/httpParser.cc

CMakeFiles/threadPool.dir/home/zzx/roughServer/src/httpParser.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/threadPool.dir/home/zzx/roughServer/src/httpParser.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zzx/roughServer/src/httpParser.cc > CMakeFiles/threadPool.dir/home/zzx/roughServer/src/httpParser.cc.i

CMakeFiles/threadPool.dir/home/zzx/roughServer/src/httpParser.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/threadPool.dir/home/zzx/roughServer/src/httpParser.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zzx/roughServer/src/httpParser.cc -o CMakeFiles/threadPool.dir/home/zzx/roughServer/src/httpParser.cc.s

CMakeFiles/threadPool.dir/home/zzx/roughServer/src/httpParser.cc.o.requires:

.PHONY : CMakeFiles/threadPool.dir/home/zzx/roughServer/src/httpParser.cc.o.requires

CMakeFiles/threadPool.dir/home/zzx/roughServer/src/httpParser.cc.o.provides: CMakeFiles/threadPool.dir/home/zzx/roughServer/src/httpParser.cc.o.requires
	$(MAKE) -f CMakeFiles/threadPool.dir/build.make CMakeFiles/threadPool.dir/home/zzx/roughServer/src/httpParser.cc.o.provides.build
.PHONY : CMakeFiles/threadPool.dir/home/zzx/roughServer/src/httpParser.cc.o.provides

CMakeFiles/threadPool.dir/home/zzx/roughServer/src/httpParser.cc.o.provides.build: CMakeFiles/threadPool.dir/home/zzx/roughServer/src/httpParser.cc.o


# Object files for target threadPool
threadPool_OBJECTS = \
"CMakeFiles/threadPool.dir/main.cc.o" \
"CMakeFiles/threadPool.dir/home/zzx/roughServer/src/httpParser.cc.o"

# External object files for target threadPool
threadPool_EXTERNAL_OBJECTS =

threadPool: CMakeFiles/threadPool.dir/main.cc.o
threadPool: CMakeFiles/threadPool.dir/home/zzx/roughServer/src/httpParser.cc.o
threadPool: CMakeFiles/threadPool.dir/build.make
threadPool: CMakeFiles/threadPool.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zzx/roughServer/examples/httpParser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable threadPool"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/threadPool.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/threadPool.dir/build: threadPool

.PHONY : CMakeFiles/threadPool.dir/build

CMakeFiles/threadPool.dir/requires: CMakeFiles/threadPool.dir/main.cc.o.requires
CMakeFiles/threadPool.dir/requires: CMakeFiles/threadPool.dir/home/zzx/roughServer/src/httpParser.cc.o.requires

.PHONY : CMakeFiles/threadPool.dir/requires

CMakeFiles/threadPool.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/threadPool.dir/cmake_clean.cmake
.PHONY : CMakeFiles/threadPool.dir/clean

CMakeFiles/threadPool.dir/depend:
	cd /home/zzx/roughServer/examples/httpParser/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zzx/roughServer/examples/httpParser /home/zzx/roughServer/examples/httpParser /home/zzx/roughServer/examples/httpParser/build /home/zzx/roughServer/examples/httpParser/build /home/zzx/roughServer/examples/httpParser/build/CMakeFiles/threadPool.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/threadPool.dir/depend

