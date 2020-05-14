/////////////////////////////////
/// @file EORInstruction.cpp
///
/// @brief Implementation for EORInstruction
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <string>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "EORInstruction.hpp" // Header for class
#include "SLList.hpp" // For SLList
#include "Process.hpp" // For Process
#include "FileIterator.hpp" // For Io::FileIterator

////////////////////////////////
/// METHOD NAME: EORInstruction::Execute 
////////////////////////////////
void EORInstruction::Execute(const SLList<std::string>& rArguments, Process& rProcess)
{
    // Get destination from arguments
    std::string destString = rArguments.Get(0);
    Register destination = atoi(destString.substr(1).c_str());

    // Get source from arguments
    uint32_t source1 = this->ParseArgument(rArguments.Get(1), rProcess);

    Registers& regs = rProcess.GetProcessRegisters();

    if (rArguments.GetLength() == 2)
    {
        // And the source with the destination
        regs.genRegs[destination] ^= source1;
    }
    else
    {
        // And the sources and overwrite the destination
        uint32_t source2 = this->ParseArgument(rArguments.Get(2), rProcess);
        regs.genRegs[destination] = source1 ^ source2;
    }

    if (m_flagged)
    {
        (regs.genRegs[destination] & 0x80000000) != 0 ? regs.SetNegativeFlag() : regs.ClearNegativeFlag();
        regs.genRegs[destination] == 0 ? regs.SetZeroFlag() : regs.ClearZeroFlag();
    }
}