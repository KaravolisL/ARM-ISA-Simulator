/////////////////////////////////
/// @file BXInstruction.cpp
///
/// @brief Implementation for BXInstruction
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <string>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "BXInstruction.hpp" // Header for class
#include "InvalidSyntaxException.hpp" // For InvalidSyntaxException
#include "SLList.hpp" // For SLList
#include "Process.hpp" // For Process
#include "FileIterator.hpp" // For FileIterator

////////////////////////////////
/// METHOD NAME: BXInstruction::Execute 
////////////////////////////////
void BXInstruction::Execute(const SLList<std::string>& rArguments, Process& rProcess)
{
    if (rArguments.GetLength() > 2) throw InvalidSyntaxException("Invalid Arguments",
                                                                 rProcess.GetFileIterator()->GetCurrentLine(),
                                                                 rProcess.GetFileIterator()->GetLineNumber());

    // Get register from arguments
    std::string regString = rArguments.Get(0);
    uint32_t newPC;
    
    if (regString[0] == 'R' || regString[0] == 'r')
    {
        newPC = ParseArgument(regString, rProcess);
    }
    else if (regString == "LR" || regString == "lr")
    {
        newPC = rProcess.GetProcessRegisters().LR;
    }
    else
    {
        throw InvalidSyntaxException("Invalid register",
                                     rProcess.GetFileIterator()->GetCurrentLine(),
                                     rProcess.GetFileIterator()->GetLineNumber());
    }
    
    
    // Set the new PC and "jump" to that location
    rProcess.GetProcessRegisters().PC = newPC;

    rProcess.GetFileIterator()->GoToLine(newPC);
}