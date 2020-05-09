cmake_minimum_required(VERSION 3.16)

# Add include path
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions")
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions/Logic")

# Add executables (Unit tests)
add_executable(AndUT AndUT.cpp)
target_link_libraries(AndUT PRIVATE instr_lib)

add_executable(OrrUT OrrUT.cpp)
target_link_libraries(OrrUT PRIVATE instr_lib)

add_executable(EorUT EorUT.cpp)
target_link_libraries(EorUT PRIVATE instr_lib)

add_executable(BicUT BicUT.cpp)
target_link_libraries(BicUT PRIVATE instr_lib)

# Add Unit Tests
add_test(NAME AndUT COMMAND AndUT)
add_test(NAME OrrUT COMMAND OrrUT)
add_test(NAME EorUT COMMAND EorUT)
add_test(NAME BicUT COMMAND BicUT)