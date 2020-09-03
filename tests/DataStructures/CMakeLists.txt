cmake_minimum_required(VERSION 3.16)

# Individual unit tests
set(DATA_STRUCTURE_UTS
    DLBUT.cpp
    HashMapUT.cpp
    ListUT.cpp
    LListUT.cpp
    QueueUT.cpp
    StackUT.cpp
)

# Add executables (Suites)
add_executable(DataStructureTestSuite DataStructureTestSuite.cpp ${DATA_STRUCTURE_UTS})
target_link_libraries(DataStructureTestSuite Catch2::Catch2)

# Add Unit Test Suite
add_test(NAME DataStructureTestSuite COMMAND DataStructureTestSuite)
