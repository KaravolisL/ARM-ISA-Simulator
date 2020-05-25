cmake_minimum_required(VERSION 3.16)

# Add include path
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions")
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions/Arithmetic")

# Add executables (Unit tests)
add_executable(AddUT AddUT.cpp)
target_link_libraries(AddUT PRIVATE instr_lib io_library keyword_dict)

add_executable(SubUT SubUT.cpp)
target_link_libraries(SubUT PRIVATE instr_lib io_library keyword_dict)

add_executable(MovUT MovUT.cpp)
target_link_libraries(MovUT PRIVATE instr_lib io_library keyword_dict)

# Add Unit Tests
add_test(NAME AddUT COMMAND AddUT)
add_test(NAME SubUT COMMAND SubUT)
add_test(NAME MovUT COMMAND MovUT)