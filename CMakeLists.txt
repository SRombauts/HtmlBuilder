# Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
#
# Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
# or copy at http://opensource.org/licenses/MIT)

cmake_minimum_required(VERSION 2.6)
project(CppSkeleton)

# Define useful variables to handle OS/Compiler differences
if (MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    set(CPPLINT_ARG_OUTPUT      "--output=vs7")
    set(CPPCHECK_ARG_TEMPLATE   "--template=vs")
    set(DEV_NULL                "NUL")
    set(SYSTEM_LIBRARIES        "")
    add_definitions (/D_CRT_SECURE_NO_WARNINGS)
else()
    set(CPPLINT_ARG_OUTPUT      "--output=eclipse")
    set(CPPCHECK_ARG_TEMPLATE   "--template=gcc")
    set(DEV_NULL                "/dev/null")
    set(SYSTEM_LIBRARIES        "rt")
#   add_definitions (-std=c++0x)  # -std=c++11
endif()
set(CPPLINT_ARG_VERBOSE "--verbose=3")

# List all sources/headers files
# used only for cpplint: adding a file still require modifing the CMakeLists.txt
# so that CMake know that it should rebuild the project (and better practice)
file(GLOB all_source_files
    "${PROJECT_SOURCE_DIR}/src/*.h"
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

# All includes are relative to the "src" directory
include_directories ("${PROJECT_SOURCE_DIR}/src")

# add the application executable
add_executable(CppSkeleton
 src/main.cpp
 src/utils/datetime.cpp src/utils/datetime.h
 src/utils/measure.cpp src/utils/measure.h
 src/utils/random.cpp src/utils/random.h
 src/utils/time.cpp src/utils/time.h
 src/utils/utils.h)
target_link_libraries (CppSkeleton ${SYSTEM_LIBRARIES})

# add a cpplint target to the "all" target
add_custom_target(cpplint
 ALL
 COMMAND python cpplint.py ${CPPLINT_ARG_OUTPUT} ${CPPLINT_ARG_VERBOSE} ${all_source_files}
 WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

# add a cppcheck target to the "all" target
add_custom_target(cppcheck
 ALL
 COMMAND cppcheck -j 4 cppcheck --enable=style --quiet ${CPPCHECK_ARG_TEMPLATE} ${PROJECT_SOURCE_DIR}/src
)

# add a Doxygen target to the "all" target
if (NOT DEFINED ENV{TRAVIS})
    # if not runing on a Travis CI Virtual Machine
    add_custom_target(doxygen
     ALL
     COMMAND doxygen Doxyfile > ${DEV_NULL}
     WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    )
else()
    # but no Doxygen under Travis CI: too costly and no real benefit
    message("no Doxygen target when TRAVIS is defined")
endif()


# add the subdirectory containing the CMakeLists.txt for the gtest library
add_subdirectory (googletest) 
include_directories ("${PROJECT_SOURCE_DIR}/googletest/include")

# add the test executable
add_executable (TestSkeleton
 src/utils/time.cpp src/utils/time.h src/utils/time_test.cpp)
target_link_libraries (TestSkeleton gtest_main ${SYSTEM_LIBRARIES})

# add a "test" target:
enable_testing()

# does the application runs
add_test (ApplicationRuns CppSkeleton)

# does the tests pass
add_test (TestsPass TestSkeleton)

