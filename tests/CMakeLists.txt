cmake_minimum_required(VERSION 3.16)

# Add include path
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/include/Io")

# Add executables (Unit tests)
add_executable(SLListUT SLListUT.cpp)
add_executable(StackUT StackUT.cpp)
add_executable(QueueUT QueueUT.cpp)
add_executable(DLBUT DLBUT.cpp)

add_executable(LoggerUT LoggerUT.cpp)
target_link_libraries(LoggerUT PRIVATE logger_library)

add_executable(FileIteratorUT FileIteratorUT.cpp)
add_executable(LineParserUT LineParserUT.cpp)
target_link_libraries(FileIteratorUT PRIVATE io_library)
target_link_libraries(LineParserUT PRIVATE io_library)

# Add Unit Tests
add_test(NAME SLListUT COMMAND SLListUT)
add_test(NAME StackUT COMMAND StackUT)
add_test(NAME QueueUT COMMAND QueueUT)
add_test(NAME DLBUT COMMAND DLBUT)

add_test(NAME LoggerUT COMMAND LoggerUT)

add_test(NAME FileIteratorUT COMMAND FileIteratorUT)
add_test(NAME LineParserUT COMMAND LineParserUT)
