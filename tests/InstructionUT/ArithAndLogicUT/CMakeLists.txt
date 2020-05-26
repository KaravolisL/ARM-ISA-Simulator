cmake_minimum_required(VERSION 3.16)

# Add include path
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions")
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions/Logic")

# Add executables (Unit tests)
add_executable(AddUT AddUT.cpp)
target_link_libraries(AddUT PRIVATE instr_lib io_library keyword_dict)

add_executable(SubUT SubUT.cpp)
target_link_libraries(SubUT PRIVATE instr_lib io_library keyword_dict)

add_executable(AndUT AndUT.cpp)
target_link_libraries(AndUT PRIVATE instr_lib io_library keyword_dict)

add_executable(OrrUT OrrUT.cpp)
target_link_libraries(OrrUT PRIVATE instr_lib io_library keyword_dict)

add_executable(EorUT EorUT.cpp)
target_link_libraries(EorUT PRIVATE instr_lib)

add_executable(BicUT BicUT.cpp)
target_link_libraries(BicUT PRIVATE instr_lib)

add_executable(MovUT MovUT.cpp)
target_link_libraries(MovUT PRIVATE instr_lib io_library keyword_dict)

# Add Unit Tests
add_test(NAME AddUT COMMAND AddUT)
add_test(NAME SubUT COMMAND SubUT)
add_test(NAME AndUT COMMAND AndUT)
add_test(NAME OrrUT COMMAND OrrUT)
add_test(NAME EorUT COMMAND EorUT)
add_test(NAME BicUT COMMAND BicUT)
add_test(NAME MovUT COMMAND MovUT)