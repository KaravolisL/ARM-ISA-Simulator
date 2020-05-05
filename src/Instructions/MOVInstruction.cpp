/////////////////////////////////
/// @file MOVInstruction.cpp
///
/// @brief Implementation for MOVInstruction
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <string>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "MOVInstruction.hpp" // Header for class
#include "InvalidSyntaxException.hpp" // For InvalidSyntaxException
#include "SLList.hpp" // For SLList
#include "Process.hpp" // For Process
#include "FileIterator.hpp" // For Io::FileIterator

////////////////////////////////
/// METHOD NAME: MOVInstruction::Execute 
////////////////////////////////
void MOVInstruction::Execute(const SLList<std::string>& rArguments, Process& rProcess, bool flagged)
{
    if (rArguments.GetLength() > 2) throw InvalidSyntaxException("Invalid Arguments",
                                                                 rProcess.GetFileIterator()->GetCurrentLine(),
                                                                 rProcess.GetFileIterator()->GetLineNumber());

    // Get destination from arguments
    std::string destString = rArguments.Get(0);
    Register destination = atoi(destString.substr(1).c_str());

    // Get source from arguments
    uint32_t source = ParseArgument(rArguments.Get(1), rProcess);

    // Perform the move
    Registers& regs =  rProcess.GetProcessRegisters();
    regs.genRegs[destination] = source;

    if (flagged)
    {
        (regs.genRegs[destination] & 0x80000000) != 0 ? regs.SetNegativeFlag() : regs.ClearNegativeFlag();
         regs.genRegs[destination] == 0 ? regs.SetZeroFlag() : regs.ClearZeroFlag();
    }
}