cmake_minimum_required(VERSION 3.16)

# Add include path
include_directories("${PROJECT_SOURCE_DIR}/tests/Framework")

# Individual unit tests
set(DATA_STRUCTURE_UTS
    HashMapUT.cpp
    StackUT.cpp
)

# Add executables (Suites)
add_executable(DataStructureTestSuite DataStructureTestSuite.cpp ${DATA_STRUCTURE_UTS})

# Add Unit Test Suite
add_test(NAME DataStructureTestSuite COMMAND DataStructureTestSuite)
