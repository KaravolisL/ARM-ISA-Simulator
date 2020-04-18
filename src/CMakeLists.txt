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
    Main.cpp
)

# Add subdirectoy
add_subdirectory(Io)

# Make libraries
add_library(logger_library STATIC Logger.cpp)

# Add executable
add_executable(ARM-ISA-SIMULATOR ${SOURCES})

# Link in libraries
target_link_libraries(ARM-ISA-SIMULATOR 
                      PRIVATE logger_library
                      PRIVATE io_library                      
)
