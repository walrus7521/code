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
include_directories("${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/inc")

add_executable(solution prj/XmlApp/XmlApp.cpp src/tinyxml.cpp src/tinyxmlparser.cpp src/tinyxmlerror.cpp)
    target_compile_definitions(solution PUBLIC TIXML_USE_STL)

# installation
set(CMAKE_INSTALL_PREFIX "C:/dookie")
install (TARGETS solution DESTINATION bin)
install (FILES demo.xml DESTINATION bin)

################################
# setup GTest testing
################################
set(GTEST_ROOT "C:/Program Files/gtest-1.6.0")
enable_testing()
find_package(GTest REQUIRED)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

################################
# Unit Tests
################################
# Add test cpp file
#add_executable( runUnitTests testgtest.cpp )
# Link test executable against gtest & gtest_main
#target_link_libraries(runUnitTests gtest gtest_main)
#add_test( runUnitTests runUnitTests )

