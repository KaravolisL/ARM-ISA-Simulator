cmake_minimum_required(VERSION 3.16)

# Set include directory
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions")

# Set source files
set(SOURCES
    InstructionRepository.cpp
    MOVInstruction.cpp
)

# Make libraries
add_library(instr_lib STATIC ${SOURCES})

# Link in libraries
target_link_libraries(instr_lib
                      PRIVATE debug_lib
)