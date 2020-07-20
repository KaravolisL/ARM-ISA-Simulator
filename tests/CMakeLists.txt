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
add_subdirectory(InstructionUT)
add_subdirectory(MemoryUT)

# Add executables (Unit tests)
add_executable(SLListUT SLListUT.cpp)
add_executable(DLListUT DLListUT.cpp)
add_executable(ListUT ListUT.cpp)
add_executable(StackUT StackUT.cpp)
add_executable(QueueUT QueueUT.cpp)
add_executable(DLBUT DLBUT.cpp)
add_executable(HashMapUT HashMapUT.cpp)

add_executable(LoggerUT LoggerUT.cpp)
target_link_libraries(LoggerUT PRIVATE debug_lib)

add_executable(FileIteratorUT FileIteratorUT.cpp)
target_link_libraries(FileIteratorUT PRIVATE io_library)

add_executable(LineParserUT LineParserUT.cpp)
target_link_libraries(LineParserUT PRIVATE io_library keyword_dict support)

# Add Unit Tests
add_test(NAME SLListUT COMMAND SLListUT)
add_test(NAME DLListUT COMMAND DLListUT)
add_test(NAME ListUT COMMAND ListUT)
add_test(NAME StackUT COMMAND StackUT)
add_test(NAME QueueUT COMMAND QueueUT)
add_test(NAME DLBUT COMMAND DLBUT)
add_test(NAME HashMapUT COMMAND HashMapUT)

add_test(NAME LoggerUT COMMAND LoggerUT)

add_test(NAME FileIteratorUT COMMAND FileIteratorUT)
add_test(NAME LineParserUT COMMAND LineParserUT)

include(FindPythonInterp)
add_test(NAME simple_program_test COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/IntegrationTests/simple_program_test.py)
add_test(NAME conditional_program_test COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/IntegrationTests/conditional_program_test.py)
add_test(NAME function_program_test COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/IntegrationTests/function_program_test.py)