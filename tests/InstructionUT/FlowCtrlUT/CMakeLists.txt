cmake_minimum_required(VERSION 3.16)

# Add include path
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/include/Debug")
include_directories("${PROJECT_SOURCE_DIR}/include/Exceptions")
include_directories("${PROJECT_SOURCE_DIR}/include/Io")
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions")
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions/FlowCtrl")

include_directories("${PROJECT_SOURCE_DIR}/tests/support")

# Add executables (Unit tests)
add_executable(BranchUT BranchUT.cpp)
target_link_libraries(BranchUT PRIVATE instr_lib support io_library keyword_dict)

add_executable(BlUT BlUT.cpp)
target_link_libraries(BlUT PRIVATE instr_lib support io_library keyword_dict)

add_executable(BxUT BxUT.cpp)
target_link_libraries(BxUT PRIVATE instr_lib support io_library keyword_dict)

add_executable(BlxUT BlxUT.cpp)
target_link_libraries(BlxUT PRIVATE instr_lib support)

# Add Unit Tests
add_test(NAME BranchUT COMMAND BranchUT)
add_test(NAME BlUT COMMAND BlUT)
add_test(NAME BxUT COMMAND BxUT)
add_test(NAME BlxUT COMMAND BlxUT)