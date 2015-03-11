# Copyright (c) 2013-2015 Sébastien Rombauts (sebastien.rombauts@gmail.com)
#
# Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
# or copy at http://opensource.org/licenses/MIT)

cmake_minimum_required(VERSION 2.6)
project(CppSkeleton)

# Print some standard CMake variables
message(STATUS "CMAKE_SYSTEM_NAME/_VERSION      '${CMAKE_SYSTEM_NAME}' '${CMAKE_SYSTEM_VERSION}'")
message(STATUS "CMAKE_CXX_COMPILER_ID/_VERSION  '${CMAKE_CXX_COMPILER_ID}' '${CMAKE_CXX_COMPILER_VERSION}'")
if (NOT MSVC)
    message(STATUS "CMAKE_BUILD_TYPE                '${CMAKE_BUILD_TYPE}'")
endif (NOT MSVC)

# Define useful variables to handle OS/Compiler differences
if (MSVC)
    # Flags for linking with multithread static C++ runtime
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    set(CPPLINT_ARG_OUTPUT      "--output=vs7")
    set(CPPCHECK_ARG_TEMPLATE   "--template=vs")
    set(DEV_NULL                "NUL")
    set(SYSTEM_LIBRARIES        "")
    add_definitions(/D_CRT_SECURE_NO_WARNINGS)
    # Set warning level to maximum (instead of default /W3)
    set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} /W4")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else (MSVC)
    set(CPPLINT_ARG_OUTPUT      "--output=eclipse")
    set(CPPCHECK_ARG_TEMPLATE   "--template=gcc")
    set(DEV_NULL                "/dev/null")
    set(SYSTEM_LIBRARIES        "rt")

    # C++11 :
    add_definitions(-std=c++0x) # equivalent to "-std=c++11" but backward compatible for GCC 4.6 on Travic-CI
    # Stack protection
    add_definitions(-fstack-protector-all)
    
    if (CMAKE_COMPILER_IS_GNUCXX)
        # GCC flags
        # For stacktraces:
        add_definitions(-rdynamic -fstack-protector-all)
        # Enable maximum of Warnings :
        add_definitions(-Wall -Wextra -Wswitch-default -Wswitch-enum -Winit-self -Wformat-security -Wfloat-equal -Wcast-qual -Wconversion -Wlogical-op -Winline)
        if (CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL "4.9" OR CMAKE_CXX_COMPILER_VERSION VERSION_GREATER "4.9")
            add_definitions (-Wfloat-conversion)
            add_definitions (-Wshadow)
        endif ()
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        # Clang flags
        # Enable maximum of Warnings :
        add_definitions(-Weverything)
        add_definitions(-Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded -Wno-covered-switch-default -Wno-unreachable-code)
    endif (CMAKE_COMPILER_IS_GNUCXX)
endif (MSVC)
set(CPPLINT_ARG_LINELENGTH "--linelength=120")
set(CPPLINT_ARG_VERBOSE    "--verbose=1")

# List all sources/headers files
set(all_source_files
 ${CMAKE_SOURCE_DIR}/src/Main.cpp
 ${CMAKE_SOURCE_DIR}/src/Utils/DateTime.cpp src/Utils/DateTime.h
 ${CMAKE_SOURCE_DIR}/src/Utils/Measure.cpp src/Utils/Measure.h
 ${CMAKE_SOURCE_DIR}/src/Utils/Random.cpp src/Utils/Random.h
 ${CMAKE_SOURCE_DIR}/src/Utils/Time.cpp src/Utils/Time.h
 ${CMAKE_SOURCE_DIR}/src/Utils/Utils.h
)

# All includes are relative to the "src" directory
include_directories("${PROJECT_SOURCE_DIR}/src")

# add the application executable
add_executable(CppSkeleton ${all_source_files})
target_link_libraries(CppSkeleton ${SYSTEM_LIBRARIES})


# Optional additional targets:

option(CPPSKELETON_RUN_CPPLINT "Run cpplint.py tool for Google C++ StyleGuide." ON)
if (CPPSKELETON_RUN_CPPLINT)
    # add a cpplint target to the "all" target
    add_custom_target(cpplint
     ALL
     COMMAND python ${PROJECT_SOURCE_DIR}/cpplint/cpplint.py ${CPPLINT_ARG_OUTPUT} ${CPPLINT_ARG_LINELENGTH} ${CPPLINT_ARG_VERBOSE} ${all_source_files}
    )
else (CPPSKELETON_RUN_CPPLINT)
    message(STATUS "CPPSKELETON_RUN_CPPLINT OFF")
endif (CPPSKELETON_RUN_CPPLINT)

option(CPPSKELETON_RUN_CPPCHECK "Run cppcheck C++ static analysis tool." ON)
if (CPPSKELETON_RUN_CPPCHECK)
    find_program(CPPCHECK_EXECUTABLE NAMES cppcheck)
    if (CPPCHECK_EXECUTABLE)
        # add a cppcheck target to the "all" target
        add_custom_target(cppcheck
         ALL
         COMMAND cppcheck -j 4 --enable=style --quiet ${CPPCHECK_ARG_TEMPLATE} ${PROJECT_SOURCE_DIR}/src
        )
    else (CPPCHECK_EXECUTABLE)
        message(STATUS "Could NOT find cppcheck")
    endif (CPPCHECK_EXECUTABLE)
else (CPPSKELETON_RUN_CPPCHECK)
    message(STATUS "CPPSKELETON_RUN_CPPCHECK OFF")
endif (CPPSKELETON_RUN_CPPCHECK)

option(CPPSKELETON_RUN_DOXYGEN "Run Doxygen C++ documentation tool." ON)
if (CPPSKELETON_RUN_DOXYGEN)
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
        # add a Doxygen target to the "all" target
        add_custom_target(doxygen
         ALL
         COMMAND doxygen Doxyfile > ${DEV_NULL}
         WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        )
    endif (DOXYGEN_FOUND)
else (CPPSKELETON_RUN_DOXYGEN)
    message(STATUS "CPPSKELETON_RUN_DOXYGEN OFF")
endif (CPPSKELETON_RUN_DOXYGEN)


option(CPPSKELETON_RUN_TESTS "Run gtest unit-test suite." ON)
if (CPPSKELETON_RUN_TESTS)
    # add the subdirectory containing the CMakeLists.txt for the gtest library
    add_subdirectory(googletest) 
    include_directories("${PROJECT_SOURCE_DIR}/googletest/include")

    # add the test executable
    add_executable(TestSkeleton
     src/Utils/Time.cpp src/Utils/Time.h src/Utils/Time_test.cpp)
    target_link_libraries(TestSkeleton gtest_main ${SYSTEM_LIBRARIES})

    # add a "test" target:
    enable_testing()

    # does the application runs
    add_test(ApplicationRuns CppSkeleton)

    # does the tests pass
    add_test(TestsPass TestSkeleton)
else (CPPSKELETON_RUN_TESTS)
    message(STATUS "CPPSKELETON_RUN_TESTS OFF")
endif (CPPSKELETON_RUN_TESTS)

