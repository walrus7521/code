cmake_minimum_required (VERSION 2.6)
project (solution)

set (solution_VERSION_MAJOR 4)
set (solution_VERSION_MINOR 2)

# configure the header file to pass some of the CMake
# settings to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/solution.h.in"
  "${PROJECT_BINARY_DIR}/solution.h"
)

include_directories("${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/inc" "../common/jsmn")
add_executable(solution src/jsonapp.c ../common/jsmn/json.c)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(CMAKE_INSTALL_PREFIX "C:/dookie")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

# installation
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
    #set(GTEST_ROOT "C:/Program Files/gtest-1.7")
    set(GTEST_ROOT "C:/Program Files/gtest-1.6.0")
    #set(GTEST_ROOT "C:/gtest-1.6.0")
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
set (CTEST_PROJECT_NAME "jsontest")
add_executable( jsontest test/jsontest.cpp )
# Link test executable against gtest & gtest_main
#target_link_libraries(jsontest gtest_maind gtestd)
target_link_libraries(jsontest gtest_main gtest)

add_test( jsontest jsontest )

