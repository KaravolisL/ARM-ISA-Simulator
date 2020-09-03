cmake_minimum_required(VERSION 3.16)

# Individual unit tests
set(DEBUG_UTS
    LoggerUT.cpp
)

# Add executables (Suites)
add_executable(DebugTestSuite DebugTestSuite.cpp ${DEBUG_UTS})
target_link_libraries(DebugTestSuite Catch2::Catch2 debug_lib)

# Add Unit Test Suite
add_test(NAME DebugTestSuite COMMAND DebugTestSuite)
