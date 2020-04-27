cmake_minimum_required(VERSION 3.16)

# set(CMAKE_C_COMPILER "C:/MinGW/bin/gcc.exe")
# set(CMAKE_CXX_COMPILER "C:/MinGW/bin/g++.exe")

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

# Enable testing
enable_testing()

# Add subdirectories
add_subdirectory (src)
add_subdirectory (tests)