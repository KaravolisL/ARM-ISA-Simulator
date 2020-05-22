/////////////////////////////////
/// @file InstructionBuilder.cpp
///
/// @brief Implementation for InstructionBuilder
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <string>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "InstructionBuilder.hpp" // Header for class
#include "InstructionBase.hpp" // For InstructionBase
#include "Process.hpp" // For Process

////////////////////////////////
/// METHOD NAME: InstructionBuilder::BuildInstruction 
////////////////////////////////
InstructionBase* InstructionBuilder::BuildInstruction(std::string& rInstruction, Process* pProcess)
{

    InstructionBase* pInstruction = new InstructionBase();

    std::string keyword = rInstruction.substr(0, rInstruction.find_first_of(' '));
    OpCode opCode = DetermineOpCode(keyword);

    switch (opCode)
    {
        case OpCode::ADD:
        case OpCode::SUB:

            break;

        case OpCode::AND:
            break;

        case OpCode::B:
            break;

        case OpCode::LDR:
        case OpCode::STR:
            MemoryInstructionBuilder::BuildInstruction(opCode)
            break;

        case OpCode::MOV:
            break;

        default:


    }


    return pInstruction;
}


