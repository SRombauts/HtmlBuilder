cmake_minimum_required (VERSION 2.6)
project (CppSkeleton)

# add the subdirectory containing the CMakeLists.txt for a library
#add_subdirectory (MyLib) 
#include_directories ("${PROJECT_SOURCE_DIR}/MyLib")
 
# add the application executable
add_executable (CppSkeleton src/main.cpp)
#target_link_libraries (CppSkeleton MyLib)

# add a "test" target:
enable_testing()

# does the application run
add_test (ApplicationRuns CppSkeleton)


