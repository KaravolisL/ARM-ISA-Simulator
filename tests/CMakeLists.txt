cmake_minimum_required(VERSION 3.16)

# Add include path
include_directories("${PROJECT_SOURCE_DIR}/include")

# Add executables (Unit tests)
add_executable(SLListUT SLListUT.cpp)
add_executable(StackUT StackUT.cpp)
add_executable(QueueUT QueueUT.cpp)
add_executable(DLBUT DLBUT.cpp)

# Add Unit Tests
add_test(NAME SLListUT COMMAND SLListUT)
add_test(NAME StackUT COMMAND StackUT)
add_test(NAME QueueUT COMMAND QueueUT)
add_test(NAME DLBUT COMMAND DLBUT)