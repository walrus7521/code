cmake_minimum_required (VERSION 2.6)
project (solution)
# the vertion number
set (solution_VERSION_MAJOR 4)
set (solution_VERSION_MINOR 2)

# configure the header file to pass some of the CMake
# settings to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/solution.h.in"
  "${PROJECT_BINARY_DIR}/solution.h"
)

# add the binary tree to the source path for
# include files so that we will find solution.h
include_directories("${PROJECT_BINARY_DIR}")

add_executable(solution solution.cpp)
