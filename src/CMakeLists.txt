cmake_minimum_required(VERSION 3.16)

# Set compiler flags
add_compile_options(-Wall -Weffc++ -pedantic -std=c++0x)
set(CMAKE_CXX_STANDARD 17)

# Set include directory
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("../include/Io")

# Set source files
set(SOURCES
    Process.cpp
    Logger.cpp
    Main.cpp
    Io/FileParser.cpp
)

# Make library
add_library(src_library STATIC ${SOURCES})

# Add executable
add_executable(ARM-ISA-SIMULATOR ${SOURCES})