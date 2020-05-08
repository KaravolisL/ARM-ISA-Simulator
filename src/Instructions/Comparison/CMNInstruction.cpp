/////////////////////////////////
/// @file CMNInstruction.cpp
///
/// @brief Implementation for CMNInstruction
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <string>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "CMNInstruction.hpp" // Header for class
#include "InvalidSyntaxException.hpp" // For InvalidSyntaxException
#include "SLList.hpp" // For SLList
#include "Process.hpp" // For Process
#include "FileIterator.hpp" // For Io::FileIterator

////////////////////////////////
/// METHOD NAME: CMNInstruction::Execute 
////////////////////////////////
void CMNInstruction::Execute(const SLList<std::string>& rArguments, Process& rProcess)
{
    if (rArguments.GetLength() > 2) throw InvalidSyntaxException("Invalid Arguments",
                                                                 rProcess.GetFileIterator()->GetCurrentLine(),
                                                                 rProcess.GetFileIterator()->GetLineNumber());

    Registers& regs = rProcess.GetProcessRegisters();

    // Get first register from arguments
    std::string arg1Str = rArguments.Get(0);
    uint32_t arg1 = ParseArgument(arg1Str, rProcess);

    // Second argument can be register or literal
    std::string arg2Str = rArguments.Get(1);
    uint32_t arg2 = ParseArgument(arg2Str, rProcess);

    uint32_t result = arg1 + arg2;

    (result & 0x80000000) != 0 ? regs.SetNegativeFlag() : regs.ClearNegativeFlag();
    result == 0 ? regs.SetZeroFlag() : regs.ClearZeroFlag();

    // Overflow can only occur if the numbers are the same sign
    if ((arg1 & 0x80000000) == (arg2 & 0x80000000))
    {
        // Overflow occurs if the sign of the arguments differ from the sum's sign
        if ((arg1 & 0x80000000) != (result & 0x80000000))
        {
            regs.SetOverflowFlag();
        }
        else
        {
            regs.ClearOverflowFlag();
        }
    }

    if (result < arg1 || result < arg2)
    {
        regs.SetCarryFlag();
    }
    else
    {
        regs.ClearCarryFlag();
    }
}