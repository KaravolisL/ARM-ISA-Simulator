cmake_minimum_required(VERSION 3.16)
# Add include path
include_directories("${PROJECT_SOURCE_DIR}/tests/Framework")

# Find Catch2 package
find_package(Catch2 REQUIRED)

# Individual unit tests
set(DATA_STRUCTURE_UTS
    # HashMapUT.cpp
    ListUT.cpp
    StackUT.cpp
)

# Add executables (Suites)
add_executable(DataStructureTestSuite DataStructureTestSuite.cpp ${DATA_STRUCTURE_UTS})
target_link_libraries(DataStructureTestSuite Catch2::Catch2)

# Add Unit Test Suite
add_test(NAME DataStructureTestSuite COMMAND DataStructureTestSuite)
