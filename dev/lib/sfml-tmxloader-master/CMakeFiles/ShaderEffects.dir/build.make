# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

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
CMAKE_SOURCE_DIR = /home/alexy/Documents/ENSL/PROJET/Projet_C++/Retro-Wars/dev/lib/sfml-tmxloader-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alexy/Documents/ENSL/PROJET/Projet_C++/Retro-Wars/dev/lib/sfml-tmxloader-master

# Include any dependencies generated for this target.
include CMakeFiles/ShaderEffects.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ShaderEffects.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ShaderEffects.dir/flags.make

CMakeFiles/ShaderEffects.dir/examples/ShaderEffects.cpp.o: CMakeFiles/ShaderEffects.dir/flags.make
CMakeFiles/ShaderEffects.dir/examples/ShaderEffects.cpp.o: examples/ShaderEffects.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/alexy/Documents/ENSL/PROJET/Projet_C++/Retro-Wars/dev/lib/sfml-tmxloader-master/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/ShaderEffects.dir/examples/ShaderEffects.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ShaderEffects.dir/examples/ShaderEffects.cpp.o -c /home/alexy/Documents/ENSL/PROJET/Projet_C++/Retro-Wars/dev/lib/sfml-tmxloader-master/examples/ShaderEffects.cpp

CMakeFiles/ShaderEffects.dir/examples/ShaderEffects.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ShaderEffects.dir/examples/ShaderEffects.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/alexy/Documents/ENSL/PROJET/Projet_C++/Retro-Wars/dev/lib/sfml-tmxloader-master/examples/ShaderEffects.cpp > CMakeFiles/ShaderEffects.dir/examples/ShaderEffects.cpp.i

CMakeFiles/ShaderEffects.dir/examples/ShaderEffects.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ShaderEffects.dir/examples/ShaderEffects.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/alexy/Documents/ENSL/PROJET/Projet_C++/Retro-Wars/dev/lib/sfml-tmxloader-master/examples/ShaderEffects.cpp -o CMakeFiles/ShaderEffects.dir/examples/ShaderEffects.cpp.s

CMakeFiles/ShaderEffects.dir/examples/ShaderEffects.cpp.o.requires:
.PHONY : CMakeFiles/ShaderEffects.dir/examples/ShaderEffects.cpp.o.requires

CMakeFiles/ShaderEffects.dir/examples/ShaderEffects.cpp.o.provides: CMakeFiles/ShaderEffects.dir/examples/ShaderEffects.cpp.o.requires
	$(MAKE) -f CMakeFiles/ShaderEffects.dir/build.make CMakeFiles/ShaderEffects.dir/examples/ShaderEffects.cpp.o.provides.build
.PHONY : CMakeFiles/ShaderEffects.dir/examples/ShaderEffects.cpp.o.provides

CMakeFiles/ShaderEffects.dir/examples/ShaderEffects.cpp.o.provides.build: CMakeFiles/ShaderEffects.dir/examples/ShaderEffects.cpp.o

# Object files for target ShaderEffects
ShaderEffects_OBJECTS = \
"CMakeFiles/ShaderEffects.dir/examples/ShaderEffects.cpp.o"

# External object files for target ShaderEffects
ShaderEffects_EXTERNAL_OBJECTS =

ShaderEffects: CMakeFiles/ShaderEffects.dir/examples/ShaderEffects.cpp.o
ShaderEffects: CMakeFiles/ShaderEffects.dir/build.make
ShaderEffects: libtmx-loader.so
ShaderEffects: libpugi.so
ShaderEffects: /usr/lib/libsfml-graphics.so
ShaderEffects: /usr/lib/libsfml-window.so
ShaderEffects: /usr/lib/libsfml-system.so
ShaderEffects: /usr/local/lib/libz.so
ShaderEffects: CMakeFiles/ShaderEffects.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ShaderEffects"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ShaderEffects.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ShaderEffects.dir/build: ShaderEffects
.PHONY : CMakeFiles/ShaderEffects.dir/build

CMakeFiles/ShaderEffects.dir/requires: CMakeFiles/ShaderEffects.dir/examples/ShaderEffects.cpp.o.requires
.PHONY : CMakeFiles/ShaderEffects.dir/requires

CMakeFiles/ShaderEffects.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ShaderEffects.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ShaderEffects.dir/clean

CMakeFiles/ShaderEffects.dir/depend:
	cd /home/alexy/Documents/ENSL/PROJET/Projet_C++/Retro-Wars/dev/lib/sfml-tmxloader-master && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alexy/Documents/ENSL/PROJET/Projet_C++/Retro-Wars/dev/lib/sfml-tmxloader-master /home/alexy/Documents/ENSL/PROJET/Projet_C++/Retro-Wars/dev/lib/sfml-tmxloader-master /home/alexy/Documents/ENSL/PROJET/Projet_C++/Retro-Wars/dev/lib/sfml-tmxloader-master /home/alexy/Documents/ENSL/PROJET/Projet_C++/Retro-Wars/dev/lib/sfml-tmxloader-master /home/alexy/Documents/ENSL/PROJET/Projet_C++/Retro-Wars/dev/lib/sfml-tmxloader-master/CMakeFiles/ShaderEffects.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ShaderEffects.dir/depend

