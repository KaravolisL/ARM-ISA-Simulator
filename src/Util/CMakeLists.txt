cmake_minimum_required(VERSION 3.16)

# Set compiler flags
add_compile_options(-Wall -Weffc++ -pedantic -std=c++0x)
set(CMAKE_CXX_STANDARD 17)

# Set include directory
include_directories("${PROJECT_SOURCE_DIR}/include/Util")

# Set source files
set(SOURCES
    Assert.cpp
)

# Make library
add_library(util_lib STATIC ${SOURCES})

target_link_libraries(util_lib
                      PRIVATE logger_library
)   
