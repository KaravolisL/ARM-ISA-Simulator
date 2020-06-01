cmake_minimum_required(VERSION 3.16)

# Add include path
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/include/Debug")
include_directories("${PROJECT_SOURCE_DIR}/include/Io")
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions")

# Set stub files
set(STUBS
    AssertMock.cpp
    FileIteratorMock.cpp
    LoggerMock.cpp
)

# Create library
add_library(support STATIC ${STUBS})