cmake_minimum_required(VERSION 3.16)

# Add include path
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions")
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions/Logic")
include_directories("${PROJECT_SOURCE_DIR}/tests/Framework")

# Individual unit tests
set(UNITTESTS
    AddUT.cpp
    AndUT.cpp
    BicUT.cpp
    CmnUT.cpp
    CmpUT.cpp
    EorUT.cpp
    LslUT.cpp
    LsrUT.cpp
    MovUT.cpp
    OrrUT.cpp
    SubUT.cpp
)

# Add executables (Unit tests)
add_executable(ArithAndLogicTestSuite ArithAndLogicTestSuite.cpp ${UNITTESTS})
target_link_libraries(ArithAndLogicTestSuite PRIVATE instr_lib io_library keyword_dict)

# Add Unit Test Suite
add_test(NAME ArithAndLogicTestSuite COMMAND ArithAndLogicTestSuite)
