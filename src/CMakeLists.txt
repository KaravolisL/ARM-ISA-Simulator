cmake_minimum_required(VERSION 3.16)

# Set the project name
project(src)

# Set compiler flags
add_compile_options(-Wall -Weffc++ -pedantic -std=c++0x -fstack-protector)
set(CMAKE_CXX_STANDARD 17)

# Set include directory
include_directories("../include")

# Set source files
set(SOURCES
    Process.cpp
    Main.cpp
)

# Add executable
add_executable(ARM-ISA-SIMULATOR ${SOURCES})