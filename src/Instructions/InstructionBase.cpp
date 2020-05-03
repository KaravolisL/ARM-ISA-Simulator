/////////////////////////////////
/// @file InstructionBase.cpp
///
/// @brief Implementation of InstructionBase class
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "InstructionBase.hpp" // Header for class
#include "Process.hpp" // For Process
#include "InvalidSyntaxException.hpp" // For InvalidSyntaxException
#include "FileIterator.hpp" // For Io::FileIterator

////////////////////////////////
/// METHOD NAME: InstructionBase::ParseArgument
////////////////////////////////
uint32_t InstructionBase::ParseArgument(const std::string& rArgument, Process& rProcess)
{
    uint32_t arg = 0;
    switch (rArgument[0])
    {
        case '#':
            arg = static_cast<uint32_t>(std::stoul(rArgument.substr(1).c_str(), nullptr, 0));
            break;
        case '=':
            arg = rProcess.GetConstantsDictionary().Get(rArgument.substr(1));
            break;
        case 'r':
        case 'R':
        {
            // Get the value in the register
            int sourceReg = atoi(rArgument.substr(1).c_str());
            arg = rProcess.GetProcessRegisters().genRegs[sourceReg];
            break;
        }
        default:
            throw InvalidSyntaxException(rProcess.GetFileIterator()->GetCurrentLine(),
                                         rProcess.GetProcessRegisters().PC);
    }
    return arg;
}