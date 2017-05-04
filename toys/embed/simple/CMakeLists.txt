cmake_minimum_required (VERSION 2.6)
project (solution)
# add the binary tree to the source path for
# include files so that we will find solution.h
#include_directories("${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/inc" "../common/sqlite/src")

#LINK_DIRECTORIES(../../common/sqlite/build/Debug)

add_executable(solution sniff.cpp snuff.cpp)


