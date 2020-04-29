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
#include "InstructionRepository.hpp" // Header for class
#include "MOVInstruction.hpp" // For MOV

static MOVInstruction f_MOV = MOVInstruction();

////////////////////////////////
/// METHOD NAME: InstructionRepository::GetInstruction 
////////////////////////////////
InstructionIface* InstructionRepository::GetInstruction(const std::string& rInstruction)
{
    InstructionIface* pInstructionIface = nullptr;
    if (rInstruction == "MOV")
    {
        pInstructionIface = &f_MOV;
    }

    return pInstructionIface;
}