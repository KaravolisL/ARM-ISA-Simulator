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
#include "SLList.hpp" // For SLList
#include "Process.hpp" // For Process

////////////////////////////////
/// METHOD NAME: MOVInstruction::Execute 
////////////////////////////////
void MOVInstruction::Execute(SLList<std::string>& rArguments, Process& rProcess)
{
    // Get destination from arguments
    std::string destString = rArguments.Get(0);
    Register destination = atoi(destString.substr(1).c_str());

    // Get source from arguments
    std::string srcString = rArguments.Get(1);
    uint32_t source;
    switch (srcString[0])
    {
        case '#':
            source = static_cast<uint32_t>(std::stoul(srcString.substr(1).c_str(), nullptr, 0));
            break;
        case '=':
            // Get the constant from the dictionary
            source = rProcess.GetConstantsDictionary().Get(srcString.substr(1));
            break;
        case 'r':
        case 'R':
        {
            // Get the value in the register
            int sourceReg = atoi(srcString.substr(1).c_str());
            source = rProcess.GetProcessRegisters().genRegs[sourceReg];
            break;
        }
        default:
            // TODO: "Compiler" exception
            break;
    }

    // Perform the move
    rProcess.GetProcessRegisters().genRegs[destination] = source;
}