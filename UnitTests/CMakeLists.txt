cmake_minimum_required(VERSION 3.17)
set(CMAKE_C_COMPILER "C:/MinGW/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/MinGW/bin/g++.exe")
# Set the project name
project(UnitTests)

# Add include path
include_directories("../src")

# Add executables (Unit tests)
add_executable(SLListUT SLListUT.cpp)