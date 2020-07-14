cmake_minimum_required(VERSION 3.16)

# Add include path
include_directories("${PROJECT_SOURCE_DIR}/include")

# Set source files
set(SOURCES
    UnitTestRunner.cpp
)

# Make libraries
add_library(util_library STATIC ${SOURCES})