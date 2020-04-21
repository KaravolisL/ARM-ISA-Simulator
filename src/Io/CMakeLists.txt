cmake_minimum_required(VERSION 3.16)

# Set compiler flags
add_compile_options(-Wall -Weffc++ -pedantic -std=c++0x)
set(CMAKE_CXX_STANDARD 17)

# Set include directory
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/include/Io")

# Set source files
set(SOURCES
    LineParser.cpp
    FileIterator.cpp
)

# Make libraries
add_library(io_library STATIC ${SOURCES})