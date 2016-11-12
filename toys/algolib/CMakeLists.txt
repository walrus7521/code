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
include_directories("${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/src" "${PROJECT_SOURCE_DIR}/inc")

add_executable(solution src/slist.cpp)

# installation
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(CMAKE_INSTALL_PREFIX "C:/dookie")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

install (TARGETS solution DESTINATION bin)
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
set (CTEST_PROJECT_NAME "algolib_test")
add_executable( algolib_test test/algolib_test.cpp )
# Link test executable against gtest & gtest_main
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    include_directories("C:/Program Files/gtest-1.6.0/msvc/gtest-md/Debug")
    target_link_libraries(algolib_test gtest_main-md gtest-md)
else(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    target_link_libraries(algolib_test gtest_main gtest)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
add_test( algolib_test algolib_test )


