/////////////////////////////////
/// @file InstructionRepository.cpp
///
/// @brief Implementation for InstructionRepository
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "Assert.hpp" // For ASSERT
#include "InstructionRepository.hpp" // Header for class
#include "MOVInstruction.hpp" // For MOV
#include "ADDInstruction.hpp" // For ADD
#include "BInstruction.hpp" // For B
#include "Logger.hpp" // For Logger

static MOVInstruction f_MOV = MOVInstruction();
static ADDInstruction f_ADD = ADDInstruction();
static BInstruction f_B = BInstruction();

////////////////////////////////
/// METHOD NAME: InstructionRepository::Initialize 
////////////////////////////////
void InstructionRepository::Initialize()
{
    m_instructionDict.Insert("MOV", &f_MOV);
    m_instructionDict.Insert("ADD", &f_ADD);
    m_instructionDict.Insert("B", &f_B);

    LOG_INFO("Instruction Repository Initialized");
}

////////////////////////////////
/// METHOD NAME: InstructionRepository::GetInstruction 
////////////////////////////////
InstructionIface* InstructionRepository::GetInstruction(const std::string& rInstruction)
{
    InstructionIface* pInstructionIface;
    try
    {
        pInstructionIface = m_instructionDict.Get(rInstruction);
    }
    catch(const DLB<InstructionIface*>::KeyNotFoundException& e)
    {
        // TODO: Instruction not supported error
    }

    ASSERT(pInstructionIface != nullptr);
    
    return pInstructionIface;
}