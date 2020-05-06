cmake_minimum_required(VERSION 3.16)

# Set include directory
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions")

# Set source files
set(SOURCES
    ADDInstruction.cpp
    ANDInstruction.cpp
    BInstruction.cpp
    BICInstruction.cpp
    CMNInstruction.cpp
    CMPInstruction.cpp
    EORInstruction.cpp
    InstructionBase.cpp
    InstructionRepository.cpp
    MOVInstruction.cpp
    ORRInstruction.cpp
)

# Make libraries
add_library(instr_lib STATIC ${SOURCES})

# Link in libraries
target_link_libraries(instr_lib
                      PRIVATE debug_lib
)