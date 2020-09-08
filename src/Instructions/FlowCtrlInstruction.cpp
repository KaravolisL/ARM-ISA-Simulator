/////////////////////////////////
/// @file FlowCtrlInstruction.cpp
///
/// @brief Implementation of FlowCtrlInstruction class
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "FlowCtrlInstruction.hpp" // Header for class
#include "Logger.hpp"
#include "Assert.hpp"

////////////////////////////////
/// METHOD NAME: FlowCtrlInstruction::Execute
////////////////////////////////
void FlowCtrlInstruction::Execute(Registers& rProcessRegisters)
{
    if (m_linkFlag)
    {
        // Set the LR to the current PC + 1
        rProcessRegisters.LR = rProcessRegisters.PC + 1;
        LOG_INSTRUCTION("LR set to %d", rProcessRegisters.LR);
    }

    // Set the new PC
    rProcessRegisters.PC = m_newPC;
}