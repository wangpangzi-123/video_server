# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/joe/yibo_server/yibo_server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/joe/yibo_server/yibo_server/build

# Include any dependencies generated for this target.
include CMakeFiles/run.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/run.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/run.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/run.dir/flags.make

CMakeFiles/run.dir/main.cpp.o: CMakeFiles/run.dir/flags.make
CMakeFiles/run.dir/main.cpp.o: /home/joe/yibo_server/yibo_server/main.cpp
CMakeFiles/run.dir/main.cpp.o: CMakeFiles/run.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/joe/yibo_server/yibo_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/run.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/run.dir/main.cpp.o -MF CMakeFiles/run.dir/main.cpp.o.d -o CMakeFiles/run.dir/main.cpp.o -c /home/joe/yibo_server/yibo_server/main.cpp

CMakeFiles/run.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/run.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joe/yibo_server/yibo_server/main.cpp > CMakeFiles/run.dir/main.cpp.i

CMakeFiles/run.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/run.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joe/yibo_server/yibo_server/main.cpp -o CMakeFiles/run.dir/main.cpp.s

CMakeFiles/run.dir/include/Logger.cpp.o: CMakeFiles/run.dir/flags.make
CMakeFiles/run.dir/include/Logger.cpp.o: /home/joe/yibo_server/yibo_server/include/Logger.cpp
CMakeFiles/run.dir/include/Logger.cpp.o: CMakeFiles/run.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/joe/yibo_server/yibo_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/run.dir/include/Logger.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/run.dir/include/Logger.cpp.o -MF CMakeFiles/run.dir/include/Logger.cpp.o.d -o CMakeFiles/run.dir/include/Logger.cpp.o -c /home/joe/yibo_server/yibo_server/include/Logger.cpp

CMakeFiles/run.dir/include/Logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/run.dir/include/Logger.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joe/yibo_server/yibo_server/include/Logger.cpp > CMakeFiles/run.dir/include/Logger.cpp.i

CMakeFiles/run.dir/include/Logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/run.dir/include/Logger.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joe/yibo_server/yibo_server/include/Logger.cpp -o CMakeFiles/run.dir/include/Logger.cpp.s

CMakeFiles/run.dir/include/check_error.cpp.o: CMakeFiles/run.dir/flags.make
CMakeFiles/run.dir/include/check_error.cpp.o: /home/joe/yibo_server/yibo_server/include/check_error.cpp
CMakeFiles/run.dir/include/check_error.cpp.o: CMakeFiles/run.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/joe/yibo_server/yibo_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/run.dir/include/check_error.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/run.dir/include/check_error.cpp.o -MF CMakeFiles/run.dir/include/check_error.cpp.o.d -o CMakeFiles/run.dir/include/check_error.cpp.o -c /home/joe/yibo_server/yibo_server/include/check_error.cpp

CMakeFiles/run.dir/include/check_error.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/run.dir/include/check_error.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joe/yibo_server/yibo_server/include/check_error.cpp > CMakeFiles/run.dir/include/check_error.cpp.i

CMakeFiles/run.dir/include/check_error.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/run.dir/include/check_error.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joe/yibo_server/yibo_server/include/check_error.cpp -o CMakeFiles/run.dir/include/check_error.cpp.s

CMakeFiles/run.dir/server/server.cpp.o: CMakeFiles/run.dir/flags.make
CMakeFiles/run.dir/server/server.cpp.o: /home/joe/yibo_server/yibo_server/server/server.cpp
CMakeFiles/run.dir/server/server.cpp.o: CMakeFiles/run.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/joe/yibo_server/yibo_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/run.dir/server/server.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/run.dir/server/server.cpp.o -MF CMakeFiles/run.dir/server/server.cpp.o.d -o CMakeFiles/run.dir/server/server.cpp.o -c /home/joe/yibo_server/yibo_server/server/server.cpp

CMakeFiles/run.dir/server/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/run.dir/server/server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joe/yibo_server/yibo_server/server/server.cpp > CMakeFiles/run.dir/server/server.cpp.i

CMakeFiles/run.dir/server/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/run.dir/server/server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joe/yibo_server/yibo_server/server/server.cpp -o CMakeFiles/run.dir/server/server.cpp.s

CMakeFiles/run.dir/bussiness/bussiness.cpp.o: CMakeFiles/run.dir/flags.make
CMakeFiles/run.dir/bussiness/bussiness.cpp.o: /home/joe/yibo_server/yibo_server/bussiness/bussiness.cpp
CMakeFiles/run.dir/bussiness/bussiness.cpp.o: CMakeFiles/run.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/joe/yibo_server/yibo_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/run.dir/bussiness/bussiness.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/run.dir/bussiness/bussiness.cpp.o -MF CMakeFiles/run.dir/bussiness/bussiness.cpp.o.d -o CMakeFiles/run.dir/bussiness/bussiness.cpp.o -c /home/joe/yibo_server/yibo_server/bussiness/bussiness.cpp

CMakeFiles/run.dir/bussiness/bussiness.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/run.dir/bussiness/bussiness.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joe/yibo_server/yibo_server/bussiness/bussiness.cpp > CMakeFiles/run.dir/bussiness/bussiness.cpp.i

CMakeFiles/run.dir/bussiness/bussiness.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/run.dir/bussiness/bussiness.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joe/yibo_server/yibo_server/bussiness/bussiness.cpp -o CMakeFiles/run.dir/bussiness/bussiness.cpp.s

CMakeFiles/run.dir/socket/socket.cpp.o: CMakeFiles/run.dir/flags.make
CMakeFiles/run.dir/socket/socket.cpp.o: /home/joe/yibo_server/yibo_server/socket/socket.cpp
CMakeFiles/run.dir/socket/socket.cpp.o: CMakeFiles/run.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/joe/yibo_server/yibo_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/run.dir/socket/socket.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/run.dir/socket/socket.cpp.o -MF CMakeFiles/run.dir/socket/socket.cpp.o.d -o CMakeFiles/run.dir/socket/socket.cpp.o -c /home/joe/yibo_server/yibo_server/socket/socket.cpp

CMakeFiles/run.dir/socket/socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/run.dir/socket/socket.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joe/yibo_server/yibo_server/socket/socket.cpp > CMakeFiles/run.dir/socket/socket.cpp.i

CMakeFiles/run.dir/socket/socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/run.dir/socket/socket.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joe/yibo_server/yibo_server/socket/socket.cpp -o CMakeFiles/run.dir/socket/socket.cpp.s

CMakeFiles/run.dir/thread_pool/thread_pool.cpp.o: CMakeFiles/run.dir/flags.make
CMakeFiles/run.dir/thread_pool/thread_pool.cpp.o: /home/joe/yibo_server/yibo_server/thread_pool/thread_pool.cpp
CMakeFiles/run.dir/thread_pool/thread_pool.cpp.o: CMakeFiles/run.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/joe/yibo_server/yibo_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/run.dir/thread_pool/thread_pool.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/run.dir/thread_pool/thread_pool.cpp.o -MF CMakeFiles/run.dir/thread_pool/thread_pool.cpp.o.d -o CMakeFiles/run.dir/thread_pool/thread_pool.cpp.o -c /home/joe/yibo_server/yibo_server/thread_pool/thread_pool.cpp

CMakeFiles/run.dir/thread_pool/thread_pool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/run.dir/thread_pool/thread_pool.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joe/yibo_server/yibo_server/thread_pool/thread_pool.cpp > CMakeFiles/run.dir/thread_pool/thread_pool.cpp.i

CMakeFiles/run.dir/thread_pool/thread_pool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/run.dir/thread_pool/thread_pool.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joe/yibo_server/yibo_server/thread_pool/thread_pool.cpp -o CMakeFiles/run.dir/thread_pool/thread_pool.cpp.s

CMakeFiles/run.dir/http_parser/http_parser.cpp.o: CMakeFiles/run.dir/flags.make
CMakeFiles/run.dir/http_parser/http_parser.cpp.o: /home/joe/yibo_server/yibo_server/http_parser/http_parser.cpp
CMakeFiles/run.dir/http_parser/http_parser.cpp.o: CMakeFiles/run.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/joe/yibo_server/yibo_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/run.dir/http_parser/http_parser.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/run.dir/http_parser/http_parser.cpp.o -MF CMakeFiles/run.dir/http_parser/http_parser.cpp.o.d -o CMakeFiles/run.dir/http_parser/http_parser.cpp.o -c /home/joe/yibo_server/yibo_server/http_parser/http_parser.cpp

CMakeFiles/run.dir/http_parser/http_parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/run.dir/http_parser/http_parser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joe/yibo_server/yibo_server/http_parser/http_parser.cpp > CMakeFiles/run.dir/http_parser/http_parser.cpp.i

CMakeFiles/run.dir/http_parser/http_parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/run.dir/http_parser/http_parser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joe/yibo_server/yibo_server/http_parser/http_parser.cpp -o CMakeFiles/run.dir/http_parser/http_parser.cpp.s

# Object files for target run
run_OBJECTS = \
"CMakeFiles/run.dir/main.cpp.o" \
"CMakeFiles/run.dir/include/Logger.cpp.o" \
"CMakeFiles/run.dir/include/check_error.cpp.o" \
"CMakeFiles/run.dir/server/server.cpp.o" \
"CMakeFiles/run.dir/bussiness/bussiness.cpp.o" \
"CMakeFiles/run.dir/socket/socket.cpp.o" \
"CMakeFiles/run.dir/thread_pool/thread_pool.cpp.o" \
"CMakeFiles/run.dir/http_parser/http_parser.cpp.o"

# External object files for target run
run_EXTERNAL_OBJECTS =

/home/joe/yibo_server/yibo_server/run: CMakeFiles/run.dir/main.cpp.o
/home/joe/yibo_server/yibo_server/run: CMakeFiles/run.dir/include/Logger.cpp.o
/home/joe/yibo_server/yibo_server/run: CMakeFiles/run.dir/include/check_error.cpp.o
/home/joe/yibo_server/yibo_server/run: CMakeFiles/run.dir/server/server.cpp.o
/home/joe/yibo_server/yibo_server/run: CMakeFiles/run.dir/bussiness/bussiness.cpp.o
/home/joe/yibo_server/yibo_server/run: CMakeFiles/run.dir/socket/socket.cpp.o
/home/joe/yibo_server/yibo_server/run: CMakeFiles/run.dir/thread_pool/thread_pool.cpp.o
/home/joe/yibo_server/yibo_server/run: CMakeFiles/run.dir/http_parser/http_parser.cpp.o
/home/joe/yibo_server/yibo_server/run: CMakeFiles/run.dir/build.make
/home/joe/yibo_server/yibo_server/run: CMakeFiles/run.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/joe/yibo_server/yibo_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable /home/joe/yibo_server/yibo_server/run"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/run.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/run.dir/build: /home/joe/yibo_server/yibo_server/run
.PHONY : CMakeFiles/run.dir/build

CMakeFiles/run.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/run.dir/cmake_clean.cmake
.PHONY : CMakeFiles/run.dir/clean

CMakeFiles/run.dir/depend:
	cd /home/joe/yibo_server/yibo_server/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/joe/yibo_server/yibo_server /home/joe/yibo_server/yibo_server /home/joe/yibo_server/yibo_server/build /home/joe/yibo_server/yibo_server/build /home/joe/yibo_server/yibo_server/build/CMakeFiles/run.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/run.dir/depend

