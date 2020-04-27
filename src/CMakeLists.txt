cmake_minimum_required(VERSION 3.16)

# Set compiler flags
add_compile_options(-Wall -Weffc++ -pedantic -std=c++0x)
set(CMAKE_CXX_STANDARD 17)

# Set include directory
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/include/Io")
include_directories("${PROJECT_SOURCE_DIR}/include/Debug")

# Set source files
set(SOURCES
    Process.cpp
    Main.cpp
)

# Make library
add_library(src_library STATIC ${SOURCES})

# Add subdirectoy
add_subdirectory(Io)
add_subdirectory(Debug)

# Make libraries
add_library(keyword_dict STATIC KeywordDict.cpp)

# Add executable
add_executable(ARM-ISA-SIMULATOR ${SOURCES})

# Link in libraries
target_link_libraries(ARM-ISA-SIMULATOR
                      PRIVATE debug_lib
                      PRIVATE io_library
                      PRIVATE keyword_dict
)
