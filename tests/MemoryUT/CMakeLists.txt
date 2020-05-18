cmake_minimum_required(VERSION 3.16)

# Add include path
include_directories("${PROJECT_SOURCE_DIR}/include/Memory")

# Add executables (Unit tests)
add_executable(MemoryManagerUT MemoryManagerUT.cpp)
target_link_libraries(MemoryManagerUT PRIVATE mem_library debug_lib)

# Add Unit Tests
add_test(NAME MemoryManagerUT COMMAND MemoryManagerUT)

