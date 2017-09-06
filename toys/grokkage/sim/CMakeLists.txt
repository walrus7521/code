cmake_minimum_required (VERSION 2.6)
project (dsim)
# the vertion number
set (dsim_VERSION_MAJOR 4)
set (dsim_VERSION_MINOR 2)


# configure the header file to pass some of the CMake
# settings to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/dsim.h.in"
  "${PROJECT_BINARY_DIR}/dsim.h"
)

# add the binary tree to the source path for
# include files so that we will find dsim.h
include_directories("${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/inc")

add_executable(dsim dsim.c)
#add_executable(dsim dsim.cpp)

# installation
if(CYGWIN)
  message("Hello, cygwin!")
endif()
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(CMAKE_INSTALL_PREFIX "C:/dookie")
    set(CMAKE_INSTALL_PREFIX "c/cygwin64/usr/include")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

install (TARGETS dsim DESTINATION bin)
install (FILES demo.xml DESTINATION bin)

# only if c++ needing c-11
set_property(TARGET dsim PROPERTY CXX_STANDARD 11)


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

