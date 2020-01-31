cmake_minimum_required (VERSION 2.6)
project (groklib)
# the vertion number
set (groklib_VERSION_MAJOR 4)
set (groklib_VERSION_MINOR 2)

# configure the header file to pass some of the CMake
# settings to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/groklib.h.in"
  "${PROJECT_BINARY_DIR}/groklib.h"
)

# add the binary tree to the source path for
# include files so that we will find groklib.h
include_directories("${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/src" "${PROJECT_SOURCE_DIR}/inc")

add_executable( groklib hash.c test.c )

# installation
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(CMAKE_INSTALL_PREFIX "C:/dookie")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

install (TARGETS groklib DESTINATION bin)
install (FILES demo.xml DESTINATION bin)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

################################
# setup GTest testing
################################
# export GTEST_ROOT=/usr
# place libgtest.* in /usr/lib
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(GTEST_ROOT "C:/Program Files/gtest-1.6.0")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})
include_directories(${GTEST_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

################################
# Unit Tests
################################
# Add test cpp file
include(CTest)
set (CTEST_PROJECT_NAME "groklib_test")
add_executable( groklib_test test/test.c hash.c )
# Link test executable against gtest & gtest_main
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    include_directories("C:/Program Files/gtest-1.6.0/msvc/gtest-md/Debug")
    target_link_libraries(groklib_test gtest_main-md gtest-md)
else(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    target_link_libraries(groklib_test gtest_main gtest)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
add_test( groklib_test groklib_test )


