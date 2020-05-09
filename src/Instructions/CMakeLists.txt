cmake_minimum_required(VERSION 3.16)

# Set include directory
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions")
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions/Arithmetic")
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions/Comparison")
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions/FlowCtrl")
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions/Logic")
include_directories("${PROJECT_SOURCE_DIR}/include/Instructions/Other")

# Set source files
set(SOURCES
    Arithmetic/ADDInstruction.cpp
    Logic/ANDInstruction.cpp
    FlowCtrl/BInstruction.cpp
    FlowCtrl/BLInstruction.cpp
    FlowCtrl/BLXInstruction.cpp
    FlowCtrl/BXInstruction.cpp
    Logic/BICInstruction.cpp
    Comparison/CMNInstruction.cpp
    Comparison/CMPInstruction.cpp
    Logic/EORInstruction.cpp
    InstructionBase.cpp
    InstructionRepository.cpp
    Other/MOVInstruction.cpp
    Logic/ORRInstruction.cpp
)

# Make libraries
add_library(instr_lib STATIC ${SOURCES})

# Link in libraries
target_link_libraries(instr_lib
                      PRIVATE debug_lib
)