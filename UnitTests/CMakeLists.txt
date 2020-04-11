cmake_minimum_required(VERSION 3.16)

# Set the project name
project(UnitTests)

# Add include path
include_directories("../include")

# Set compiler flags
add_compile_options(-Wall -Weffc++ -pedantic -std=c++0x)
set(CMAKE_CXX_STANDARD 17)

# Add executables (Unit tests)
add_executable(SLListUT SLListUT.cpp)
add_executable(StackUT StackUT.cpp)
add_executable(DLBUT DLBUT.cpp)

# Add Unit Tests
add_test(NAME SLListUT COMMAND SLListUT)
add_test(NAME StackUT COMMAND StackUT)
add_test(NAME DLBUT COMMAND DLBUT)