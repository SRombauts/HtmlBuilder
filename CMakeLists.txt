# Copyright (c) 2013 Sébastien Rombauts (sebastien.rombauts@gmail.com)
#
# Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
# or copy at http://opensource.org/licenses/MIT)

cmake_minimum_required (VERSION 2.6)
project (CppSkeleton)

if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

# add the application executable
add_executable (CppSkeleton
 src/main.cpp
 src/foo.cpp src/foo.h)

# add the subdirectory containing the CMakeLists.txt for the gtest library
add_subdirectory (googletest) 
include_directories ("${PROJECT_SOURCE_DIR}/googletest/include")

# add the test executable
add_executable (TestSkeleton
 src/foo.cpp src/foo.h src/foo_test.cpp)
target_link_libraries (TestSkeleton gtest_main)
 
# add a "test" target:
enable_testing()

# does the application runs
add_test (ApplicationRuns CppSkeleton)

# does the tests pass
add_test (TestsPass TestSkeleton)

