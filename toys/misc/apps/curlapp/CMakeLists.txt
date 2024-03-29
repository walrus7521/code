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
include_directories("${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/inc" "../common/curl-7.50.3/include")

add_executable(solution src/curlapp.cpp)
    target_compile_definitions(solution PUBLIC TIXML_USE_STL)

# installation
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(CMAKE_INSTALL_PREFIX "C:/dookie")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

install (TARGETS solution DESTINATION bin)
install (FILES demo.xml DESTINATION bin)

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
set (CTEST_PROJECT_NAME "curltest")
add_executable( curltest test/curltest.cpp )
target_link_libraries(curltest gtest_main gtest)

# Link test executable against gtest & gtest_main
add_test( curltest curltest )

