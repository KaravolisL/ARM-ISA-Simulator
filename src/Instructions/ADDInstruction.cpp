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
#include "InvalidSyntaxException.hpp" // For InvalidSyntaxException
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

    // Get source from arguments
    uint32_t source1 = this->ParseArgument(rArguments.Get(1), rProcess);

    if (rArguments.GetLength() == 2)
    {
        // Add source to destination
        rProcess.GetProcessRegisters().genRegs[destination] += source1;
    }
    else
    {
        // Set the destination to the sum of the sources
        uint32_t source2 = this->ParseArgument(rArguments.Get(2), rProcess);
        rProcess.GetProcessRegisters().genRegs[destination] = source1 + source2;
    }
}