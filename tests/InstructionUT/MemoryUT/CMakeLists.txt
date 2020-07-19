cmake_minimum_required(VERSION 3.16)

# Add include path
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions")
include_directories("${PROJECT_SOURCE_DIR}/include/Memory")
include_directories("${PROJECT_SOURCE_DIR}/tests/Framework")

# Set Unit Tests
set(UNITTESTS
    LdmAndStmUT.cpp
    PushAndPopUT.cpp
    LdrAndStrUT.cpp
)

# Add executable (Test Suite)
add_executable(MemoryInstructionTestSuite MemoryInstructionTestSuite.cpp ${UNITTESTS})
target_link_libraries(MemoryInstructionTestSuite PRIVATE instr_lib io_library keyword_dict)

# Add Unit Tests
add_test(NAME MemoryInstructionTestSuite COMMAND MemoryInstructionTestSuite)