/////////////////////////////////
/// @file MemoryInstructionBuilder.cpp
///
/// @brief Implementation for MemoryInstructionBuilder
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "MemoryInstructionBuilder.hpp" // Header for class
#include "MemoryInstruction.hpp" // For MemoryInstruction
#include "MultipleMemoryInstruction.hpp" // For MultipleMemoryInstruction
#include "Assert.hpp" // For ASSERT
#include "Logger.hpp" // For LOG_DEBUG

////////////////////////////////
/// METHOD NAME: MemoryInstructionBuilder::BuildInstruction 
////////////////////////////////
InstructionBase* MemoryInstructionBuilder::BuildInstruction(std::string& rInstruction, Process* pProcess)
{
    InstructionBase* pInstruction = nullptr;

    LOG_DEBUG("m_opCode = %d", m_opCode);
    switch (m_opCode)
    {
        case OpCode::PUSH:
        case OpCode::POP:
        case OpCode::LDM:
        case OpCode::STM:
            pInstruction = BuildMultipleMemoryInstruction(rInstruction, pProcess);
            break;
        case OpCode::LDR:
        case OpCode::STR:
            pInstruction = BuildMemoryInstruction(rInstruction, pProcess);
            break;
        default:
            ASSERT(false, "Invalid opcode %d", m_opCode);
    }
    
    ASSERT(pInstruction != nullptr);
    return pInstruction;
}

////////////////////////////////
/// METHOD NAME: MemoryInstructionBuilder::BuildMemoryInstruction 
////////////////////////////////
MemoryInstruction* MemoryInstructionBuilder::BuildMemoryInstruction(std::string& rInstruction, Process* pProcess)
{
    return nullptr;
}

////////////////////////////////
/// METHOD NAME: MemoryInstructionBuilder::BuildMultipleMemoryInstruction 
////////////////////////////////
MultipleMemoryInstruction* MemoryInstructionBuilder::BuildMultipleMemoryInstruction(std::string& rInstruction, Process* pProcess)
{
    return nullptr;
}