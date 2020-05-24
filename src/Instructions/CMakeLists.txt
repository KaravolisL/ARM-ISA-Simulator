cmake_minimum_required(VERSION 3.16)

# Set include directory
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions")
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions/Arithmetic")
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions/Comparison")
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions/FlowCtrl")
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions/Logic")
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions/Memory")
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions/Other")

# Set source files
set(SOURCES
    Arithmetic/ADDInstruction.cpp
    Arithmetic/SUBInstruction.cpp
    Comparison/CMNInstruction.cpp
    Comparison/CMPInstruction.cpp
    FlowCtrl/BInstruction.cpp
    FlowCtrl/BLInstruction.cpp
    FlowCtrl/BLXInstruction.cpp
    FlowCtrl/BXInstruction.cpp
    Logic/ANDInstruction.cpp
    Logic/BICInstruction.cpp
    Logic/EORInstruction.cpp
    Logic/ORRInstruction.cpp
    Memory/POPInstruction.cpp
    Memory/PUSHInstruction.cpp
    InstructionBase.cpp
    InstructionBuilder.cpp
    ArithAndLogicInstructionBuilder.cpp
    ArithAndLogicInstruction.cpp
    InstructionBuilderRepository.cpp
    InstructionRepository.cpp
    Other/MOVInstruction.cpp
)

# Make libraries
add_library(instr_lib STATIC ${SOURCES})

# Link in libraries
target_link_libraries(instr_lib
                      PRIVATE debug_lib
)