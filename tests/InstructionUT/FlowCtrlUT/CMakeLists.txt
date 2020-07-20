cmake_minimum_required(VERSION 3.16)

# Add include path
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions")

include_directories("${PROJECT_SOURCE_DIR}/tests/support")
include_directories("${PROJECT_SOURCE_DIR}/tests/Framework")

# Individual Unit Tests
set(UNITTESTS
    BlUT.cpp
    BlxUT.cpp
    BranchUT.cpp
    BxUT.cpp
)

# Add executable
add_executable(FlowCtrlTestSuite FlowCtrlTestSuite.cpp ${UNITTESTS})
target_link_libraries(FlowCtrlTestSuite PRIVATE instr_lib support io_library keyword_dict)

# Add Unit Tests
add_test(NAME FlowCtrlTestSuite COMMAND FlowCtrlTestSuite)