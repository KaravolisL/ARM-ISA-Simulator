cmake_minimum_required(VERSION 3.16)

# Add include path
include_directories("${PROJECT_SOURCE_DIR}/include/Memory")

# Individual unit tests
set(MEMORY_UTS
    MemoryManagerUT.cpp
)

# Add executables (Suites)
add_executable(MemoryTestSuite MemoryTestSuite.cpp ${MEMORY_UTS})
target_link_libraries(MemoryTestSuite PRIVATE Catch2::Catch2 mem_library debug_lib)

# Add Unit Tests
add_test(NAME MemoryTestSuite COMMAND MemoryTestSuite)

