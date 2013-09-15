cmake_minimum_required (VERSION 2.6)
project (CppSkeleton)

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

