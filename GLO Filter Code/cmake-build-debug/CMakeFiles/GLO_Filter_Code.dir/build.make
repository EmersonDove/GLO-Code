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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/Emerson/Documents/Space@VT/Code/GLO-Code/GLO Filter Code"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/Emerson/Documents/Space@VT/Code/GLO-Code/GLO Filter Code/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/GLO_Filter_Code.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/GLO_Filter_Code.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/GLO_Filter_Code.dir/flags.make

CMakeFiles/GLO_Filter_Code.dir/main.cpp.o: CMakeFiles/GLO_Filter_Code.dir/flags.make
CMakeFiles/GLO_Filter_Code.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/Emerson/Documents/Space@VT/Code/GLO-Code/GLO Filter Code/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/GLO_Filter_Code.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GLO_Filter_Code.dir/main.cpp.o -c "/Users/Emerson/Documents/Space@VT/Code/GLO-Code/GLO Filter Code/main.cpp"

CMakeFiles/GLO_Filter_Code.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GLO_Filter_Code.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/Emerson/Documents/Space@VT/Code/GLO-Code/GLO Filter Code/main.cpp" > CMakeFiles/GLO_Filter_Code.dir/main.cpp.i

CMakeFiles/GLO_Filter_Code.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GLO_Filter_Code.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/Emerson/Documents/Space@VT/Code/GLO-Code/GLO Filter Code/main.cpp" -o CMakeFiles/GLO_Filter_Code.dir/main.cpp.s

CMakeFiles/GLO_Filter_Code.dir/Filters.cpp.o: CMakeFiles/GLO_Filter_Code.dir/flags.make
CMakeFiles/GLO_Filter_Code.dir/Filters.cpp.o: ../Filters.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/Emerson/Documents/Space@VT/Code/GLO-Code/GLO Filter Code/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/GLO_Filter_Code.dir/Filters.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GLO_Filter_Code.dir/Filters.cpp.o -c "/Users/Emerson/Documents/Space@VT/Code/GLO-Code/GLO Filter Code/Filters.cpp"

CMakeFiles/GLO_Filter_Code.dir/Filters.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GLO_Filter_Code.dir/Filters.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/Emerson/Documents/Space@VT/Code/GLO-Code/GLO Filter Code/Filters.cpp" > CMakeFiles/GLO_Filter_Code.dir/Filters.cpp.i

CMakeFiles/GLO_Filter_Code.dir/Filters.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GLO_Filter_Code.dir/Filters.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/Emerson/Documents/Space@VT/Code/GLO-Code/GLO Filter Code/Filters.cpp" -o CMakeFiles/GLO_Filter_Code.dir/Filters.cpp.s

# Object files for target GLO_Filter_Code
GLO_Filter_Code_OBJECTS = \
"CMakeFiles/GLO_Filter_Code.dir/main.cpp.o" \
"CMakeFiles/GLO_Filter_Code.dir/Filters.cpp.o"

# External object files for target GLO_Filter_Code
GLO_Filter_Code_EXTERNAL_OBJECTS =

GLO_Filter_Code: CMakeFiles/GLO_Filter_Code.dir/main.cpp.o
GLO_Filter_Code: CMakeFiles/GLO_Filter_Code.dir/Filters.cpp.o
GLO_Filter_Code: CMakeFiles/GLO_Filter_Code.dir/build.make
GLO_Filter_Code: CMakeFiles/GLO_Filter_Code.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/Emerson/Documents/Space@VT/Code/GLO-Code/GLO Filter Code/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable GLO_Filter_Code"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/GLO_Filter_Code.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/GLO_Filter_Code.dir/build: GLO_Filter_Code

.PHONY : CMakeFiles/GLO_Filter_Code.dir/build

CMakeFiles/GLO_Filter_Code.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/GLO_Filter_Code.dir/cmake_clean.cmake
.PHONY : CMakeFiles/GLO_Filter_Code.dir/clean

CMakeFiles/GLO_Filter_Code.dir/depend:
	cd "/Users/Emerson/Documents/Space@VT/Code/GLO-Code/GLO Filter Code/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/Emerson/Documents/Space@VT/Code/GLO-Code/GLO Filter Code" "/Users/Emerson/Documents/Space@VT/Code/GLO-Code/GLO Filter Code" "/Users/Emerson/Documents/Space@VT/Code/GLO-Code/GLO Filter Code/cmake-build-debug" "/Users/Emerson/Documents/Space@VT/Code/GLO-Code/GLO Filter Code/cmake-build-debug" "/Users/Emerson/Documents/Space@VT/Code/GLO-Code/GLO Filter Code/cmake-build-debug/CMakeFiles/GLO_Filter_Code.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/GLO_Filter_Code.dir/depend
