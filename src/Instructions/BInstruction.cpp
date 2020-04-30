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
#include "SLList.hpp" // For SLList
#include "Process.hpp" // For Process
#include "FileIterator.hpp" // For FileIterator

////////////////////////////////
/// METHOD NAME: BInstruction::Execute 
////////////////////////////////
void BInstruction::Execute(const SLList<std::string>& rArguments, Process& rProcess)
{
    // TODO: Enable when InvalidArgumentsException is created
    // if (rArguments.GetLength() > 2) throw InvalidArgumentsException()

    // Get label from arguments
    std::string labelString = rArguments.Get(0);
    uint32_t newPC;
    try
    {
        newPC = rProcess.GetLabelDictionary().Get(labelString);
    }
    catch(const DLB<uint32_t>::KeyNotFoundException& e)
    {
        // TODO: Enable when compiler exceptions are created
        // throw LabelNotFoundException();
    }
    
    // Set the new PC and "jump" to that location
    rProcess.GetProcessRegisters().PC = newPC;

    rProcess.GetFileIterator()->GoToLine(newPC);
}