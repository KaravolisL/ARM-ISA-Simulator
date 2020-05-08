/////////////////////////////////
/// @file BLInstruction.cpp
///
/// @brief Implementation for BLInstruction
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <string>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "BLInstruction.hpp" // Header for class
#include "InvalidSyntaxException.hpp" // For InvalidSyntaxException
#include "SLList.hpp" // For SLList
#include "Process.hpp" // For Process
#include "FileIterator.hpp" // For FileIterator

////////////////////////////////
/// METHOD NAME: BLInstruction::Execute 
////////////////////////////////
void BLInstruction::Execute(const SLList<std::string>& rArguments, Process& rProcess)
{
    if (rArguments.GetLength() > 2) throw InvalidSyntaxException("Invalid Arguments",
                                                                 rProcess.GetFileIterator()->GetCurrentLine(),
                                                                 rProcess.GetFileIterator()->GetLineNumber());

    // Get label from arguments
    std::string labelString = rArguments.Get(0);
    uint32_t newPC;
    try
    {
        newPC = rProcess.GetLabelDictionary().Get(labelString);
    }
    catch(const DLB<uint32_t>::KeyNotFoundException& e)
    {
        throw InvalidSyntaxException("Label Not Found",
                                     rProcess.GetFileIterator()->GetCurrentLine(),
                                     rProcess.GetFileIterator()->GetLineNumber());
    }

    // Set the LR to the current PC + 1
    rProcess.GetProcessRegisters().LR = rProcess.GetProcessRegisters().PC + 1;
    
    // Set the new PC and "jump" to that location
    rProcess.GetProcessRegisters().PC = newPC;

    rProcess.GetFileIterator()->GoToLine(newPC);
}