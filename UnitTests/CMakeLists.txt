cmake_minimum_required(VERSION 3.16)

# Set the project name
project(UnitTests)

# Add include path
include_directories("../src")

# Add executables (Unit tests)
add_executable(SLListUT SLListUT.cpp)
add_executable(StackUT StackUT.cpp)

# Add Unit Tests
add_test(NAME SLListUT COMMAND SLListUT)
add_test(NAME StackUT COMMAND StackUT)