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
include CMakeFiles/httpParser.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/httpParser.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/httpParser.dir/flags.make

CMakeFiles/httpParser.dir/main.cc.o: CMakeFiles/httpParser.dir/flags.make
CMakeFiles/httpParser.dir/main.cc.o: ../main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zzx/roughServer/examples/httpParser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/httpParser.dir/main.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/httpParser.dir/main.cc.o -c /home/zzx/roughServer/examples/httpParser/main.cc

CMakeFiles/httpParser.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/httpParser.dir/main.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zzx/roughServer/examples/httpParser/main.cc > CMakeFiles/httpParser.dir/main.cc.i

CMakeFiles/httpParser.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/httpParser.dir/main.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zzx/roughServer/examples/httpParser/main.cc -o CMakeFiles/httpParser.dir/main.cc.s

CMakeFiles/httpParser.dir/main.cc.o.requires:

.PHONY : CMakeFiles/httpParser.dir/main.cc.o.requires

CMakeFiles/httpParser.dir/main.cc.o.provides: CMakeFiles/httpParser.dir/main.cc.o.requires
	$(MAKE) -f CMakeFiles/httpParser.dir/build.make CMakeFiles/httpParser.dir/main.cc.o.provides.build
.PHONY : CMakeFiles/httpParser.dir/main.cc.o.provides

CMakeFiles/httpParser.dir/main.cc.o.provides.build: CMakeFiles/httpParser.dir/main.cc.o


CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpParser.cc.o: CMakeFiles/httpParser.dir/flags.make
CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpParser.cc.o: /home/zzx/roughServer/src/httpParser.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zzx/roughServer/examples/httpParser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpParser.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpParser.cc.o -c /home/zzx/roughServer/src/httpParser.cc

CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpParser.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpParser.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zzx/roughServer/src/httpParser.cc > CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpParser.cc.i

CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpParser.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpParser.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zzx/roughServer/src/httpParser.cc -o CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpParser.cc.s

CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpParser.cc.o.requires:

.PHONY : CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpParser.cc.o.requires

CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpParser.cc.o.provides: CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpParser.cc.o.requires
	$(MAKE) -f CMakeFiles/httpParser.dir/build.make CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpParser.cc.o.provides.build
.PHONY : CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpParser.cc.o.provides

CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpParser.cc.o.provides.build: CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpParser.cc.o


CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpResponder.cc.o: CMakeFiles/httpParser.dir/flags.make
CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpResponder.cc.o: /home/zzx/roughServer/src/httpResponder.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zzx/roughServer/examples/httpParser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpResponder.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpResponder.cc.o -c /home/zzx/roughServer/src/httpResponder.cc

CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpResponder.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpResponder.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zzx/roughServer/src/httpResponder.cc > CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpResponder.cc.i

CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpResponder.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpResponder.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zzx/roughServer/src/httpResponder.cc -o CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpResponder.cc.s

CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpResponder.cc.o.requires:

.PHONY : CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpResponder.cc.o.requires

CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpResponder.cc.o.provides: CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpResponder.cc.o.requires
	$(MAKE) -f CMakeFiles/httpParser.dir/build.make CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpResponder.cc.o.provides.build
.PHONY : CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpResponder.cc.o.provides

CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpResponder.cc.o.provides.build: CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpResponder.cc.o


# Object files for target httpParser
httpParser_OBJECTS = \
"CMakeFiles/httpParser.dir/main.cc.o" \
"CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpParser.cc.o" \
"CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpResponder.cc.o"

# External object files for target httpParser
httpParser_EXTERNAL_OBJECTS =

httpParser: CMakeFiles/httpParser.dir/main.cc.o
httpParser: CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpParser.cc.o
httpParser: CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpResponder.cc.o
httpParser: CMakeFiles/httpParser.dir/build.make
httpParser: CMakeFiles/httpParser.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zzx/roughServer/examples/httpParser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable httpParser"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/httpParser.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/httpParser.dir/build: httpParser

.PHONY : CMakeFiles/httpParser.dir/build

CMakeFiles/httpParser.dir/requires: CMakeFiles/httpParser.dir/main.cc.o.requires
CMakeFiles/httpParser.dir/requires: CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpParser.cc.o.requires
CMakeFiles/httpParser.dir/requires: CMakeFiles/httpParser.dir/home/zzx/roughServer/src/httpResponder.cc.o.requires

.PHONY : CMakeFiles/httpParser.dir/requires

CMakeFiles/httpParser.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/httpParser.dir/cmake_clean.cmake
.PHONY : CMakeFiles/httpParser.dir/clean

CMakeFiles/httpParser.dir/depend:
	cd /home/zzx/roughServer/examples/httpParser/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zzx/roughServer/examples/httpParser /home/zzx/roughServer/examples/httpParser /home/zzx/roughServer/examples/httpParser/build /home/zzx/roughServer/examples/httpParser/build /home/zzx/roughServer/examples/httpParser/build/CMakeFiles/httpParser.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/httpParser.dir/depend

