cmake_minimum_required(VERSION 3.16)

# Add include path
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions")
include_directories("${PROJECT_SOURCE_DIR}/include/Memory")

# Individual unit tests
set(ARITH_AND_LOGIC_UTS
    ArithAndLogicUT/AddUT.cpp
    ArithAndLogicUT/AndUT.cpp
    ArithAndLogicUT/BicUT.cpp
    ArithAndLogicUT/CmnUT.cpp
    ArithAndLogicUT/CmpUT.cpp
    ArithAndLogicUT/EorUT.cpp
    ArithAndLogicUT/LslUT.cpp
    ArithAndLogicUT/LsrUT.cpp
    ArithAndLogicUT/MovUT.cpp
    ArithAndLogicUT/OrrUT.cpp
    ArithAndLogicUT/SubUT.cpp
    ArithAndLogicUT/TstUT.cpp
)

set(FLOW_CTRL_UTS
    FlowCtrlUT/BlUT.cpp
    FlowCtrlUT/BlxUT.cpp
    FlowCtrlUT/BranchUT.cpp
    FlowCtrlUT/BxUT.cpp
)

set(MEMORY_UTS
    MemoryUT/LdmAndStmUT.cpp
    MemoryUT/PushAndPopUT.cpp
    MemoryUT/LdrAndStrUT.cpp
)

# Add executables (Suites)
add_executable(ArithAndLogicTestSuite ArithAndLogicUT/ArithAndLogicTestSuite.cpp ${ARITH_AND_LOGIC_UTS})
target_link_libraries(ArithAndLogicTestSuite PRIVATE Catch2::Catch2 instr_lib support io_library keyword_dict)

add_executable(FlowCtrlTestSuite FlowCtrlUT/FlowCtrlTestSuite.cpp ${FLOW_CTRL_UTS})
target_link_libraries(FlowCtrlTestSuite PRIVATE Catch2::Catch2 instr_lib support io_library keyword_dict)

add_executable(MemoryInstructionTestSuite MemoryUT/MemoryInstructionTestSuite.cpp ${MEMORY_UTS})
target_link_libraries(MemoryInstructionTestSuite PRIVATE Catch2::Catch2 instr_lib support io_library keyword_dict)

# Add Unit Test Suite
add_test(NAME ArithAndLogicTestSuite COMMAND ArithAndLogicTestSuite)
add_test(NAME FlowCtrlTestSuite COMMAND FlowCtrlTestSuite)
add_test(NAME MemoryInstructionTestSuite COMMAND MemoryInstructionTestSuite)
