cmake_minimum_required(VERSION 3.16)

# Set the project name
project(ARM_ISA_SIMULATOR)

# Set compiler flags
add_compile_options(-Wall -Weffc++ -pedantic -std=c++0x -fstack-protector)
set(CMAKE_CXX_STANDARD 17)

# Enable testing
enable_testing()

# Add subdirectories
add_subdirectory (src)
add_subdirectory (UnitTests)