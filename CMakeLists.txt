# Copyright (c) 2017-2019 Sébastien Rombauts (sebastien.rombauts@gmail.com)
#
# Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
# or copy at http://opensource.org/licenses/MIT)

cmake_minimum_required(VERSION 2.8.12) # first version with add_compile_options()
project(HtmlBuilder CXX)

# Verbose Makefile
#set (CMAKE_VERBOSE_MAKEFILE ON)

# Print some standard CMake variables
message(STATUS "CMake version: ${CMAKE_VERSION}")
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
    add_compile_options(-std=c++0x) # equivalent to "-std=c++11" but backward compatible for GCC 4.6 on Travic-CI
    # Stack protection
    add_compile_options(-fstack-protector-all)
    
    if (CMAKE_COMPILER_IS_GNUCXX)
        # GCC flags
        # For stacktraces:
        add_compile_options(-rdynamic -fstack-protector-all)
        # Enable maximum of Warnings :
        add_compile_options(-Wall -Wextra -Wswitch-default -Wswitch-enum -Winit-self -Wformat-security -Wfloat-equal -Wcast-qual -Wconversion -Wlogical-op -Winline)
        if (CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL "4.9" OR CMAKE_CXX_COMPILER_VERSION VERSION_GREATER "4.9")
            add_compile_options (-Wfloat-conversion)
            add_compile_options (-Wshadow)
        endif ()
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        # Clang flags
        # Enable maximum of Warnings :
        add_compile_options(-Weverything)
        add_compile_options(-Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded -Wno-covered-switch-default -Wno-unreachable-code)
    endif (CMAKE_COMPILER_IS_GNUCXX)
endif (MSVC)
set(CPPLINT_ARG_LINELENGTH "--linelength=120")
set(CPPLINT_ARG_VERBOSE    "--verbose=1")

# List all headers files
set(headers_files
 ${CMAKE_SOURCE_DIR}/include/HTML/HTML.h
 ${CMAKE_SOURCE_DIR}/include/HTML/Element.h
 ${CMAKE_SOURCE_DIR}/include/HTML/Document.h
)
source_group(headers  FILES ${headers_files})

# List all example source files
set(examples_files
 ${CMAKE_SOURCE_DIR}/src/Main.cpp
)
source_group(example  FILES ${examples_files})

# List script files
set(script_files
 ${CMAKE_SOURCE_DIR}/.travis.yml
 ${CMAKE_SOURCE_DIR}/appveyor.yml
 ${CMAKE_SOURCE_DIR}/build.bat
 ${CMAKE_SOURCE_DIR}/build.sh
)
source_group(scripts  FILES ${script_files})

# List doc files
set(doc_files
 ${CMAKE_SOURCE_DIR}/README.md
 ${CMAKE_SOURCE_DIR}/LICENSE.txt
)
#source_group(doc      FILES ${doc_files})

# All includes are relative to the "include" directory
include_directories("${PROJECT_SOURCE_DIR}/include")

# add the application executable
add_executable(HtmlBuilder_example ${headers_files} ${doc_files} ${script_files} ${examples_files})
target_link_libraries(HtmlBuilder_example ${SYSTEM_LIBRARIES})


# Optional additional targets:

option(RUN_CPPLINT "Run cpplint.py tool for Google C++ StyleGuide." ON)
if (RUN_CPPLINT)
    find_package(PythonInterp)
    if (PYTHONINTERP_FOUND)
        # add a cpplint target to the "all" target
        add_custom_target(cpplint
         ALL
         COMMAND ${PYTHON_EXECUTABLE} ${PROJECT_SOURCE_DIR}/cpplint/cpplint.py ${CPPLINT_ARG_OUTPUT} ${CPPLINT_ARG_LINELENGTH} ${CPPLINT_ARG_VERBOSE} ${headers_files}
        )
    endif (PYTHONINTERP_FOUND)
else (RUN_CPPLINT)
    message(STATUS "RUN_CPPLINT OFF")
endif (RUN_CPPLINT)

option(RUN_CPPCHECK "Run cppcheck C++ static analysis tool." ON)
if (RUN_CPPCHECK)
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
else (RUN_CPPCHECK)
    message(STATUS "RUN_CPPCHECK OFF")
endif (RUN_CPPCHECK)

option(RUN_DOXYGEN "Run Doxygen C++ documentation tool." ON)
if (RUN_DOXYGEN)
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
        # add a Doxygen target to the "all" target
        add_custom_target(doxygen
         ALL
         COMMAND doxygen Doxyfile > ${DEV_NULL}
         WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        )
    endif (DOXYGEN_FOUND)
else (RUN_DOXYGEN)
    message(STATUS "RUN_DOXYGEN OFF")
endif (RUN_DOXYGEN)


    # add a "test" target:
    enable_testing()

    # does the example1 runs successfully?
    add_test(ExampleRun HtmlBuilder_example)
