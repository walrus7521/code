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
  "${PROJECT_SOURCE_DIR}/inc/tinyxml.h"
)

add_custom_command(COMMAND TIXML_USE_STL)

# add the binary tree to the source path for
# include files so that we will find solution.h
include_directories("${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/inc")

add_executable(solution1 prj/XmlTest/XmlTest.cpp)
add_executable(solution2 src/tinyxml.cpp)
add_executable(solution3 src/tinyxmlparser.cpp)
add_executable(solution4 src/tinyxmlerror.cpp)
