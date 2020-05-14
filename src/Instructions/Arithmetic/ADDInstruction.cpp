/////////////////////////////////
/// @file ADDInstruction.cpp
///
/// @brief Implementation for ADDInstruction
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <string>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "ADDInstruction.hpp" // Header for class
#include "SLList.hpp" // For SLList
#include "Process.hpp" // For Process
#include "FileIterator.hpp" // For Io::FileIterator

////////////////////////////////
/// METHOD NAME: ADDInstruction::Execute 
////////////////////////////////
void ADDInstruction::Execute(const SLList<std::string>& rArguments, Process& rProcess)
{
    // Get destination from arguments
    std::string destString = rArguments.Get(0);
    Register destination = atoi(destString.substr(1).c_str());

    Registers& regs = rProcess.GetProcessRegisters();

    // Get source from arguments
    uint32_t source1 = this->ParseArgument(rArguments.Get(1), rProcess);
    uint32_t source2 = regs.genRegs[destination];

    if (rArguments.GetLength() == 2)
    {
        // Add source to destination
        regs.genRegs[destination] += source1;
    }
    else
    {
        // Set the destination to the sum of the sources
        source2 = this->ParseArgument(rArguments.Get(2), rProcess);
        regs.genRegs[destination] = source1 + source2;
    }

    if (m_flagged)
    {
        (regs.genRegs[destination] & 0x80000000) != 0 ? regs.SetNegativeFlag() : regs.ClearNegativeFlag();
        regs.genRegs[destination] == 0 ? regs.SetZeroFlag() : regs.ClearZeroFlag();

        // Overflow can only occur if the numbers are the same sign
        if ((source1 & 0x80000000) == (source2 & 0x80000000))
        {
            // Overflow occurs if the sign of the arguments differ from the sum's sign
            if ((source1 & 0x80000000) != (regs.genRegs[destination] & 0x80000000))
            {
                regs.SetOverflowFlag();
            }
            else
            {
                regs.ClearOverflowFlag();
            }
        }

        if (regs.genRegs[destination] < source1 || regs.genRegs[destination] < source2)
        {
            regs.SetCarryFlag();
        }
        else
        {
            regs.ClearCarryFlag();
        }
    }
}