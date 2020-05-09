cmake_minimum_required(VERSION 3.16)

# Add include path
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions")
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions/Other")

# Add executables (Unit tests)
add_executable(MovUT MovUT.cpp)
target_link_libraries(MovUT PRIVATE instr_lib)

# Add Unit Tests
add_test(NAME MovUT COMMAND MovUT)

