/////////////////////////////////
/// @file ArithAndLogicInstructionBuilder.cpp
///
/// @brief Implementation for ArithAndLogicInstructionBuilder
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "ArithAndLogicInstructionBuilder.hpp" // Header for class
#include "InstructionBase.hpp" // For InstructionBase
#include "InvalidSyntaxException.hpp" // For InvalidSyntaxException
#include "Process.hpp" // For Process
#include "Assert.hpp" // For ASSERT
#include "Logger.hpp" // For LOB_DEBUG

////////////////////////////////
/// METHOD NAME: ArithAndLogicInstructionBuilder::BuildInstruction 
////////////////////////////////
InstructionBase* BuildInstruction(std::string& rInstruction, Process* pProcess)
{
    return nullptr;
}

////////////////////////////////
/// METHOD NAME: ArithAndLogicInstructionBuilder::CheckSFlag 
////////////////////////////////
bool ArithAndLogicInstructionBuilder::CheckSFlag(std::string& rKeyword) const
{
    if (rKeyword.length() > 1 && rKeyword[0] == 'S')
    {
        LOG_DEBUG("Instruction will set the flags");
        rKeyword = rKeyword.substr(1);
        return true;
    }
    else
    {
        return false;
    }
}
