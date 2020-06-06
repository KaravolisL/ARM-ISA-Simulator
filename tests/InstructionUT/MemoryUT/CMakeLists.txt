cmake_minimum_required(VERSION 3.16)

# Add include path
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions")
include_directories("${PROJECT_SOURCE_DIR}/include/Memory")

# Add executables (Unit tests)
add_executable(PushAndPopUT PushAndPopUT.cpp)
target_link_libraries(PushAndPopUT PRIVATE instr_lib io_library keyword_dict)

add_executable(LdmAndStmUT LdmAndStmUT.cpp)
target_link_libraries(LdmAndStmUT PRIVATE instr_lib io_library keyword_dict)

# Add Unit Tests
add_test(NAME PushAndPopUT COMMAND PushAndPopUT)
add_test(NAME LdmAndStmUT COMMAND LdmAndStmUT)