# Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
#
# Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
# or copy at http://opensource.org/licenses/MIT)

cmake_minimum_required(VERSION 2.6)
project(CppSkeleton)

if (MSVC)
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
add_executable(CppSkeleton
 src/main.cpp
 src/utils/datetime.cpp src/utils/datetime.h
 src/utils/measure.cpp src/utils/measure.h
 src/utils/random.cpp src/utils/random.h
 src/utils/time.cpp src/utils/time.h
 src/utils/utils.h)

if (MSVC)
    target_link_libraries (CppSkeleton)
else()
    target_link_libraries (CppSkeleton rt)
endif()

# add a cpplint target to the "all" target
add_custom_target(cpplint
 ALL
 COMMAND python cpplint.py ${CCPPLINT_ARG_OUTPUT} ${CCPPLINT_ARG_VERBOSE} src/*.* src/*/*.* 
 WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

# add a cppcheck target to the "all" target
add_custom_target(cppcheck
 ALL
 COMMAND cppcheck -j 4 cppcheck --enable=style,portability,performance,information --quiet --template='{file}:{line}: warning: cppcheck: {message} [{severity}/{id}]' src
 WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}  
)

if (NOT DEFINED ENV{TRAVIS})
    # add a Doxygen target to the "all" target
    add_custom_target(doxygen
     ALL
     COMMAND doxygen Doxyfile > /dev/null 
     WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    )
else()
    # but no Doxygen under Travis CI: too costly and no real benefit
    message("no Doxygen target when TRAVIS is defined")
endif()


# add the subdirectory containing the CMakeLists.txt for the gtest library
add_subdirectory (googletest) 
include_directories ("${PROJECT_SOURCE_DIR}/googletest/include")

include_directories ("${PROJECT_SOURCE_DIR}/src")

# add the test executable
add_executable (TestSkeleton
 src/utils/time.cpp src/utils/time.h src/utils/time_test.cpp)

if (MSVC)
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

