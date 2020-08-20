cmake_minimum_required(VERSION 3.16)

# Set compiler flags
add_compile_options(-Wall -Weffc++ -pedantic -std=c++0x)
set(CMAKE_CXX_STANDARD 17)

# Find packages
find_package(CLI11 REQUIRED)

# Set include directory
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/include/Io")
include_directories("${PROJECT_SOURCE_DIR}/include/Debug")
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions")
include_directories("${PROJECT_SOURCE_DIR}/include/Exceptions")
include_directories("${PROJECT_SOURCE_DIR}/include/Memory")

# Set source files
set(SOURCES
    Process.cpp
    ProcessInitializer.cpp
    Main.cpp
)

# Add subdirectoy
add_subdirectory(Io)
add_subdirectory(Debug)
add_subdirectory(Instructions)
add_subdirectory(Memory)

# Make libraries
add_library(keyword_dict STATIC KeywordDict.cpp)

# Add executable
add_executable(ARM-ISA-SIMULATOR ${SOURCES})

# Link in libraries
target_link_libraries(ARM-ISA-SIMULATOR
                      PRIVATE CLI11::CLI11
                      PRIVATE debug_lib
                      PRIVATE io_library
                      PRIVATE keyword_dict
                      PRIVATE instr_lib
)
