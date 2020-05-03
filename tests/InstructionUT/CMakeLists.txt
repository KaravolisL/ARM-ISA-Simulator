cmake_minimum_required(VERSION 3.16)

# Add include path
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/include/Debug")
include_directories("${PROJECT_SOURCE_DIR}/include/Exceptions")
include_directories("${PROJECT_SOURCE_DIR}/include/Io")
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions")

include_directories("${PROJECT_SOURCE_DIR}/tests/support")

# Add executables (Unit tests)
add_executable(AddUT AddUT.cpp)
target_link_libraries(AddUT PRIVATE instr_lib)

add_executable(MovUT MovUT.cpp)
target_link_libraries(MovUT PRIVATE instr_lib)

add_executable(BranchUT BranchUT.cpp)
target_link_libraries(BranchUT PRIVATE instr_lib support)

add_executable(CmpUT CmpUT.cpp)
target_link_libraries(CmpUT PRIVATE instr_lib)

add_executable(AndUT AndUT.cpp)
target_link_libraries(AndUT PRIVATE instr_lib)

add_executable(OrrUT OrrUT.cpp)
target_link_libraries(OrrUT PRIVATE instr_lib)

add_executable(EorUT EorUT.cpp)
target_link_libraries(EorUT PRIVATE instr_lib)

# Add Unit Tests
add_test(NAME AddUT COMMAND AddUT)
add_test(NAME MovUT COMMAND MovUT)
add_test(NAME BranchUT COMMAND BranchUT)
add_test(NAME CmpUT COMMAND CmpUT)
add_test(NAME AndUT COMMAND AndUT)
add_test(NAME OrrUT COMMAND OrrUT)
add_test(NAME EorUT COMMAND EorUT)