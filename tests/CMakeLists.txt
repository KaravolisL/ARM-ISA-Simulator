cmake_minimum_required(VERSION 3.16)

# Find packages
find_package(Catch2 REQUIRED)

# Add include path
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/include/Debug")
include_directories("${PROJECT_SOURCE_DIR}/include/Exceptions")
include_directories("${PROJECT_SOURCE_DIR}/include/Io")
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions")

include_directories("${PROJECT_SOURCE_DIR}/tests/support")

# Set preprocessor definition
add_compile_definitions(BUILD_UNIT_TEST)

# Add subdirectory
add_subdirectory(support)
add_subdirectory(DataStructures)
add_subdirectory(DebugUT)
add_subdirectory(InstructionUT)
add_subdirectory(MemoryUT)

# Add executables (Unit tests)
add_executable(FileIteratorUT FileIteratorUT.cpp)
target_link_libraries(FileIteratorUT PRIVATE io_library)

add_executable(LineParserUT LineParserUT.cpp)
target_link_libraries(LineParserUT PRIVATE io_library keyword_dict debug_lib)

# Add Unit Tests
add_test(NAME FileIteratorUT COMMAND FileIteratorUT)
add_test(NAME LineParserUT COMMAND LineParserUT)

include(FindPythonInterp)
add_test(NAME simple_program_test COMMAND pytest --timeout=5 ${CMAKE_CURRENT_SOURCE_DIR}/IntegrationTests/simple_program_test.py)
add_test(NAME conditional_program_test COMMAND pytest --timeout=5 ${CMAKE_CURRENT_SOURCE_DIR}/IntegrationTests/conditional_program_test.py)
add_test(NAME function_program_test COMMAND pytest --timeout=5 ${CMAKE_CURRENT_SOURCE_DIR}/IntegrationTests/function_program_test.py)
add_test(NAME memory_program_test COMMAND pytest --timeout=5 ${CMAKE_CURRENT_SOURCE_DIR}/IntegrationTests/memory_program_test.py)
add_test(NAME user_interaction_test COMMAND pytest --timeout=60 ${CMAKE_CURRENT_SOURCE_DIR}/IntegrationTests/user_interaction_test.py)