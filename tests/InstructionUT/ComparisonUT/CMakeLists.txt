cmake_minimum_required(VERSION 3.16)

# Add include path
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions")
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions/Comparison")

# Add executables (Unit tests)
add_executable(CmnUT CmnUT.cpp)
target_link_libraries(CmnUT PRIVATE instr_lib)

# Add Unit Tests
add_test(NAME CmnUT COMMAND CmnUT)
