# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\20200213\ForDevelopment\CLion 2020.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\20200213\ForDevelopment\CLion 2020.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Project_codeing\CLion\C_ThreadPool

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Project_codeing\CLion\C_ThreadPool\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/C_ThreadPool.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/C_ThreadPool.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/C_ThreadPool.dir/flags.make

CMakeFiles/C_ThreadPool.dir/main.c.obj: CMakeFiles/C_ThreadPool.dir/flags.make
CMakeFiles/C_ThreadPool.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Project_codeing\CLion\C_ThreadPool\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/C_ThreadPool.dir/main.c.obj"
	D:\20200213\ForDevelopment\mingw64_8.1.0\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\C_ThreadPool.dir\main.c.obj -c D:\Project_codeing\CLion\C_ThreadPool\main.c

CMakeFiles/C_ThreadPool.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/C_ThreadPool.dir/main.c.i"
	D:\20200213\ForDevelopment\mingw64_8.1.0\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Project_codeing\CLion\C_ThreadPool\main.c > CMakeFiles\C_ThreadPool.dir\main.c.i

CMakeFiles/C_ThreadPool.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/C_ThreadPool.dir/main.c.s"
	D:\20200213\ForDevelopment\mingw64_8.1.0\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Project_codeing\CLion\C_ThreadPool\main.c -o CMakeFiles\C_ThreadPool.dir\main.c.s

# Object files for target C_ThreadPool
C_ThreadPool_OBJECTS = \
"CMakeFiles/C_ThreadPool.dir/main.c.obj"

# External object files for target C_ThreadPool
C_ThreadPool_EXTERNAL_OBJECTS =

C_ThreadPool.exe: CMakeFiles/C_ThreadPool.dir/main.c.obj
C_ThreadPool.exe: CMakeFiles/C_ThreadPool.dir/build.make
C_ThreadPool.exe: CMakeFiles/C_ThreadPool.dir/linklibs.rsp
C_ThreadPool.exe: CMakeFiles/C_ThreadPool.dir/objects1.rsp
C_ThreadPool.exe: CMakeFiles/C_ThreadPool.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Project_codeing\CLion\C_ThreadPool\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable C_ThreadPool.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\C_ThreadPool.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/C_ThreadPool.dir/build: C_ThreadPool.exe

.PHONY : CMakeFiles/C_ThreadPool.dir/build

CMakeFiles/C_ThreadPool.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\C_ThreadPool.dir\cmake_clean.cmake
.PHONY : CMakeFiles/C_ThreadPool.dir/clean

CMakeFiles/C_ThreadPool.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Project_codeing\CLion\C_ThreadPool D:\Project_codeing\CLion\C_ThreadPool D:\Project_codeing\CLion\C_ThreadPool\cmake-build-debug D:\Project_codeing\CLion\C_ThreadPool\cmake-build-debug D:\Project_codeing\CLion\C_ThreadPool\cmake-build-debug\CMakeFiles\C_ThreadPool.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/C_ThreadPool.dir/depend

