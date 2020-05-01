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
    uint32_t source1 = this->GetSource(rArguments.Get(1), rProcess);

    if (rArguments.GetLength() == 2)
    {
        // Add source to destination
        rProcess.GetProcessRegisters().genRegs[destination] += source1;
    }
    else
    {
        // Set the destination to the sum of the sources
        uint32_t source2 = this->GetSource(rArguments.Get(2), rProcess);
        rProcess.GetProcessRegisters().genRegs[destination] = source1 + source2;
    }
}

////////////////////////////////
/// METHOD NAME: ADDInstruction::GetSource 
////////////////////////////////
uint32_t ADDInstruction::GetSource(const std::string& rSrcString, Process& rProcess)
{
    uint32_t source = 0;
    switch (rSrcString[0])
    {
        case '#':
            source = static_cast<uint32_t>(std::stoul(rSrcString.substr(1).c_str(), nullptr, 0));
            break;
        case '=':
            // Get the constant from the dictionary
            source = rProcess.GetConstantsDictionary().Get(rSrcString.substr(1));
            break;
        case 'r':
        case 'R':
        {
            // Get the value in the register
            int sourceReg = atoi(rSrcString.substr(1).c_str());
            source = rProcess.GetProcessRegisters().genRegs[sourceReg];
            break;
        }
        default:
            throw InvalidSyntaxException(rProcess.GetFileIterator()->GetCurrentLine(),
                                         rProcess.GetProcessRegisters().PC);
    }
    return source;
}