/////////////////////////////////
/// @file ORRInstruction.cpp
///
/// @brief Implementation for ORRInstruction
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <string>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "ORRInstruction.hpp" // Header for class
#include "SLList.hpp" // For SLList
#include "Process.hpp" // For Process
#include "FileIterator.hpp" // For Io::FileIterator

////////////////////////////////
/// METHOD NAME: ORRInstruction::Execute 
////////////////////////////////
void ORRInstruction::Execute(const SLList<std::string>& rArguments, Process& rProcess)
{
    // Get destination from arguments
    std::string destString = rArguments.Get(0);
    Register destination = atoi(destString.substr(1).c_str());

    // Get source from arguments
    uint32_t source1 = this->ParseArgument(rArguments.Get(1), rProcess);

    if (rArguments.GetLength() == 2)
    {
        // And the source with the destination
        rProcess.GetProcessRegisters().genRegs[destination] |= source1;
    }
    else
    {
        // And the sources and overwrite the destination
        uint32_t source2 = this->ParseArgument(rArguments.Get(2), rProcess);
        rProcess.GetProcessRegisters().genRegs[destination] = source1 | source2;
    }
}