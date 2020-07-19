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
)

# Add executables (Unit tests)
add_executable(SubUT SubUT.cpp)
target_link_libraries(SubUT PRIVATE instr_lib io_library keyword_dict)

add_executable(OrrUT OrrUT.cpp)
target_link_libraries(OrrUT PRIVATE instr_lib io_library keyword_dict)

add_executable(EorUT EorUT.cpp)
target_link_libraries(EorUT PRIVATE instr_lib io_library keyword_dict)

add_executable(LslUT LslUT.cpp)
target_link_libraries(LslUT PRIVATE instr_lib io_library keyword_dict)

add_executable(LsrUT LsrUT.cpp)
target_link_libraries(LsrUT PRIVATE instr_lib io_library keyword_dict)

add_executable(MovUT MovUT.cpp)
target_link_libraries(MovUT PRIVATE instr_lib io_library keyword_dict)

add_executable(ArithAndLogicTestSuite ArithAndLogicTestSuite.cpp ${UNITTESTS})
target_link_libraries(ArithAndLogicTestSuite PRIVATE instr_lib io_library keyword_dict)

# Add Unit Tests
add_test(NAME SubUT COMMAND SubUT)
add_test(NAME OrrUT COMMAND OrrUT)
add_test(NAME EorUT COMMAND EorUT)
add_test(NAME LslUT COMMAND LslUT)
add_test(NAME LsrUT COMMAND LsrUT)
add_test(NAME MovUT COMMAND MovUT)
add_test(NAME ArithAndLogicTestSuite COMMAND ArithAndLogicTestSuite)
