# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /home/emanuel/.local/lib/python2.7/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/emanuel/.local/lib/python2.7/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/emanuel/Desktop/FPI/final_git

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/emanuel/Desktop/FPI/final_git

# Include any dependencies generated for this target.
include CMakeFiles/tf.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tf.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tf.dir/flags.make

CMakeFiles/tf.dir/tf.cpp.o: CMakeFiles/tf.dir/flags.make
CMakeFiles/tf.dir/tf.cpp.o: tf.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/emanuel/Desktop/FPI/final_git/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tf.dir/tf.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tf.dir/tf.cpp.o -c /home/emanuel/Desktop/FPI/final_git/tf.cpp

CMakeFiles/tf.dir/tf.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tf.dir/tf.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/emanuel/Desktop/FPI/final_git/tf.cpp > CMakeFiles/tf.dir/tf.cpp.i

CMakeFiles/tf.dir/tf.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tf.dir/tf.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/emanuel/Desktop/FPI/final_git/tf.cpp -o CMakeFiles/tf.dir/tf.cpp.s

# Object files for target tf
tf_OBJECTS = \
"CMakeFiles/tf.dir/tf.cpp.o"

# External object files for target tf
tf_EXTERNAL_OBJECTS =

tf: CMakeFiles/tf.dir/tf.cpp.o
tf: CMakeFiles/tf.dir/build.make
tf: /usr/local/lib/libopencv_gapi.so.4.5.1
tf: /usr/local/lib/libopencv_highgui.so.4.5.1
tf: /usr/local/lib/libopencv_ml.so.4.5.1
tf: /usr/local/lib/libopencv_objdetect.so.4.5.1
tf: /usr/local/lib/libopencv_photo.so.4.5.1
tf: /usr/local/lib/libopencv_stitching.so.4.5.1
tf: /usr/local/lib/libopencv_video.so.4.5.1
tf: /usr/local/lib/libopencv_videoio.so.4.5.1
tf: /usr/local/lib/libopencv_dnn.so.4.5.1
tf: /usr/local/lib/libopencv_imgcodecs.so.4.5.1
tf: /usr/local/lib/libopencv_calib3d.so.4.5.1
tf: /usr/local/lib/libopencv_features2d.so.4.5.1
tf: /usr/local/lib/libopencv_flann.so.4.5.1
tf: /usr/local/lib/libopencv_imgproc.so.4.5.1
tf: /usr/local/lib/libopencv_core.so.4.5.1
tf: CMakeFiles/tf.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/emanuel/Desktop/FPI/final_git/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable tf"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tf.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tf.dir/build: tf

.PHONY : CMakeFiles/tf.dir/build

CMakeFiles/tf.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tf.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tf.dir/clean

CMakeFiles/tf.dir/depend:
	cd /home/emanuel/Desktop/FPI/final_git && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/emanuel/Desktop/FPI/final_git /home/emanuel/Desktop/FPI/final_git /home/emanuel/Desktop/FPI/final_git /home/emanuel/Desktop/FPI/final_git /home/emanuel/Desktop/FPI/final_git/CMakeFiles/tf.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tf.dir/depend
