# Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
#
# Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
# or copy at http://opensource.org/licenses/MIT)

cmake_minimum_required (VERSION 2.6)
project (CppSkeleton)

if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    set(CCPPLINT_ARG_OUTPUT "--output=vs7")
    add_definitions (/D_CRT_SECURE_NO_WARNINGS)
else()
    set(CCPPLINT_ARG_OUTPUT "--output=eclipse")
#   add_definitions (-std=c++0x)  # -std=c++11
endif()
set(CCPPLINT_ARG_VERBOSE "--verbose=3")

# add the application executable
add_executable (CppSkeleton
 src/main.cpp
 src/base/time.cpp src/base/time.h)
if(MSVC)
    target_link_libraries (CppSkeleton)
else()
    target_link_libraries (CppSkeleton rt)
endif()

# add a cpplint target
add_custom_target(cpplint
 ALL
 COMMAND python ${PROJECT_SOURCE_DIR}/cpplint.py ${CCPPLINT_ARG_OUTPUT} ${CCPPLINT_ARG_VERBOSE} ${PROJECT_SOURCE_DIR}/src/*.* ${PROJECT_SOURCE_DIR}/src/*/*.* 
)

# add the subdirectory containing the CMakeLists.txt for the gtest library
add_subdirectory (googletest) 
include_directories ("${PROJECT_SOURCE_DIR}/googletest/include")

include_directories ("${PROJECT_SOURCE_DIR}/src")

# add the test executable
add_executable (TestSkeleton
 src/base/time.cpp src/base/time.h src/base/time_test.cpp)
if(MSVC)
    target_link_libraries (TestSkeleton gtest_main)
else()
    target_link_libraries (TestSkeleton rt gtest_main)
endif()

# add a "test" target:
enable_testing()

# does the application runs
add_test (ApplicationRuns CppSkeleton)

# does the tests pass
add_test (TestsPass TestSkeleton)

