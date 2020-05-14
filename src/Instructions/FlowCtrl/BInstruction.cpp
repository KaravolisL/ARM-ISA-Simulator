/////////////////////////////////
/// @file BInstruction.cpp
///
/// @brief Implementation for BInstruction
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <string>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "BInstruction.hpp" // Header for class
#include "InvalidSyntaxException.hpp" // For InvalidSyntaxException
#include "SLList.hpp" // For SLList
#include "Process.hpp" // For Process
#include "FileIterator.hpp" // For FileIterator
#include "Logger.hpp" // For LOG_DEBUG

////////////////////////////////
/// METHOD NAME: BInstruction::Execute 
////////////////////////////////
void BInstruction::Execute(const SLList<std::string>& rArguments, Process& rProcess)
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
        LOG_DEBUG("Label %s not found", labelString.c_str());
        throw InvalidSyntaxException("Label Not Found",
                                     rProcess.GetFileIterator()->GetCurrentLine(),
                                     rProcess.GetFileIterator()->GetLineNumber());
    }
    
    // Set the new PC and "jump" to that location
    rProcess.GetProcessRegisters().PC = newPC;
}