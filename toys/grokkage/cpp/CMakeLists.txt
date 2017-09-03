cmake_minimum_required (VERSION 2.6)
project (tears)
# the vertion number
set (tears_VERSION_MAJOR 4)
set (tears_VERSION_MINOR 2)


# configure the header file to pass some of the CMake
# settings to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/tears.h.in"
  "${PROJECT_BINARY_DIR}/tears.h"
)

# add the binary tree to the source path for
# include files so that we will find tears.h
include_directories("${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/inc")

#add_executable(tears tears.c)
add_executable(tears tears.cpp)

# installation
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(CMAKE_INSTALL_PREFIX "C:/dookie")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

install (TARGETS tears DESTINATION bin)
install (FILES demo.xml DESTINATION bin)

# only if c++ needing c-11
set_property(TARGET tears PROPERTY CXX_STANDARD 11)


if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    find_package(BISON)
    find_package(FLEX)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

################################
# setup GTest testing
################################
# export GTEST_ROOT=/usr
# place libgtest.* in /usr/lib
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(GTEST_ROOT "C:/Program Files/gtest-1.6.0")
    enable_testing()
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIR})
    include_directories(${GTEST_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

################################
# Unit Tests
################################
# Add test cpp file
#include(CTest)
#set (CTEST_PROJECT_NAME "XmlApp")

#add_executable( runUnitTests testgtest.cpp )
# Link test executable against gtest & gtest_main
#target_link_libraries(runUnitTests gtest gtest_main)
#add_test( runUnitTests runUnitTests )

