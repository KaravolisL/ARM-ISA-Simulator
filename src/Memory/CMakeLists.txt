cmake_minimum_required(VERSION 3.16)

# Set compiler flags
add_compile_options(-Wall -Weffc++ -pedantic -std=c++0x)
set(CMAKE_CXX_STANDARD 17)

# Set include directory
include_directories("${PROJECT_SOURCE_DIR}/include/Memory")
include_directories("${PROJECT_SOURCE_DIR}/include/Debug")

# Set source files
set(SOURCES
    MemoryManager.cpp
)

# Make libraries
add_library(mem_library STATIC ${SOURCES})