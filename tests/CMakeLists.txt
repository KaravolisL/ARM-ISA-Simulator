cmake_minimum_required(VERSION 3.16)

# Add include path
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/include/Debug")
include_directories("${PROJECT_SOURCE_DIR}/include/Exceptions")
include_directories("${PROJECT_SOURCE_DIR}/include/Io")
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions")

include_directories("${PROJECT_SOURCE_DIR}/tests/support")

# Add subdirectory
add_subdirectory(support)

# Add executables (Unit tests)
add_executable(SLListUT SLListUT.cpp)
add_executable(ArrayListUT ArrayListUT.cpp)
add_executable(StackUT StackUT.cpp)
add_executable(QueueUT QueueUT.cpp)
add_executable(DLBUT DLBUT.cpp)

add_executable(LoggerUT LoggerUT.cpp)
target_link_libraries(LoggerUT PRIVATE debug_lib)

add_executable(FileIteratorUT FileIteratorUT.cpp)
target_link_libraries(FileIteratorUT PRIVATE io_library)

add_executable(LineParserUT LineParserUT.cpp)
target_link_libraries(LineParserUT PRIVATE io_library keyword_dict debug_lib)

add_executable(AddUT InstructionUT/AddUT.cpp)
target_link_libraries(AddUT PRIVATE instr_lib)

add_executable(MovUT InstructionUT/MovUT.cpp)
target_link_libraries(MovUT PRIVATE instr_lib)

add_executable(BranchUT InstructionUT/BranchUT.cpp)
target_link_libraries(BranchUT PRIVATE instr_lib support)

# Add Unit Tests
add_test(NAME SLListUT COMMAND SLListUT)
add_test(NAME ArrayListUT COMMAND ArrayListUT)
add_test(NAME StackUT COMMAND StackUT)
add_test(NAME QueueUT COMMAND QueueUT)
add_test(NAME DLBUT COMMAND DLBUT)

add_test(NAME LoggerUT COMMAND LoggerUT)

add_test(NAME FileIteratorUT COMMAND FileIteratorUT)
add_test(NAME LineParserUT COMMAND LineParserUT)

add_test(NAME AddUT COMMAND AddUT)
add_test(NAME MovUT COMMAND MovUT)
add_test(NAME BranchUT COMMAND BranchUT)

include(FindPythonInterp)
add_test(NAME test COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/IntegrationTests/test.py)
