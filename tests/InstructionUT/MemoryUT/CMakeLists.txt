cmake_minimum_required(VERSION 3.16)

# Add include path
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions")

# Add executables (Unit tests)
add_executable(PushUT PushUT.cpp)
target_link_libraries(PushUT PRIVATE instr_lib io_library keyword_dict)

# Add Unit Tests
add_test(NAME PushUT COMMAND PushUT)