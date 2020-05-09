/////////////////////////////////
/// @file BLXInstruction.cpp
///
/// @brief Implementation for BLXInstruction
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <string>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "BLXInstruction.hpp" // Header for class
#include "InvalidSyntaxException.hpp" // For InvalidSyntaxException
#include "SLList.hpp" // For SLList
#include "Process.hpp" // For Process
#include "FileIterator.hpp" // For FileIterator

////////////////////////////////
/// METHOD NAME: BLXInstruction::Execute 
////////////////////////////////
void BLXInstruction::Execute(const SLList<std::string>& rArguments, Process& rProcess)
{
    if (rArguments.GetLength() > 2) throw InvalidSyntaxException("Invalid Arguments",
                                                                 rProcess.GetFileIterator()->GetCurrentLine(),
                                                                 rProcess.GetFileIterator()->GetLineNumber());

    // Get register from arguments
    std::string arg = rArguments.Get(0);
    uint32_t newPC;

    // The argument can either be a label or a register
    try
    {
        newPC = rProcess.GetLabelDictionary().Get(arg);
    }
    catch (const DLB<uint32_t>::KeyNotFoundException& e)
    {
        if (arg[0] == 'R' || arg[0] == 'r')
        {
            newPC = ParseArgument(arg, rProcess);
        }
        else if (arg == "LR" || arg == "lr")
        {
            newPC = rProcess.GetProcessRegisters().LR;
        }
        else
        {
            throw InvalidSyntaxException("Invalid register",
                                        rProcess.GetFileIterator()->GetCurrentLine(),
                                        rProcess.GetFileIterator()->GetLineNumber());
        }
    }
    
    // Set the LR to the current PC + 1
    rProcess.GetProcessRegisters().LR = rProcess.GetProcessRegisters().PC + 1;
    
    // Set the new PC and "jump" to that location
    rProcess.GetProcessRegisters().PC = newPC;

    rProcess.GetFileIterator()->GoToLine(newPC);
}