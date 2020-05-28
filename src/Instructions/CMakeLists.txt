cmake_minimum_required(VERSION 3.16)

# Set include directory
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions")
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions/Memory")

# Set source files
set(SOURCES
    Memory/POPInstruction.cpp
    Memory/PUSHInstruction.cpp
    InstructionBase.cpp
    InstructionBuilder.cpp
    ArithAndLogicInstructionBuilder.cpp
    ArithAndLogicInstruction.cpp
    FlowCtrlInstructionBuilder.cpp
    MemoryInstructionBuilder.cpp
    FlowCtrlInstruction.cpp
    InstructionBuilderRepository.cpp
    InstructionRepository.cpp
)

# Make libraries
add_library(instr_lib STATIC ${SOURCES})

# Link in libraries
target_link_libraries(instr_lib
                      PRIVATE debug_lib
)