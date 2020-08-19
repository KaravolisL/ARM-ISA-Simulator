cmake_minimum_required(VERSION 3.16)

### Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

# Set the project name
project(ARM_ISA_SIMULATOR)

# Set compiler flags
add_compile_options(-Wall -Weffc++ -pedantic -std=c++0x -g)
set(CMAKE_CXX_STANDARD 17)

# Optionally build tests
option(ENABLE_TESTS "Enable Testing" OFF)
if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Add source subdirectory
add_subdirectory(src)
