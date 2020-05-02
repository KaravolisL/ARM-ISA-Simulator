/////////////////////////////////
/// @file CMPInstruction.cpp
///
/// @brief Implementation for CMPInstruction
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <string>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "CMPInstruction.hpp" // Header for class
#include "InvalidSyntaxException.hpp" // For InvalidSyntaxException
#include "SLList.hpp" // For SLList
#include "Process.hpp" // For Process
#include "FileIterator.hpp" // For FileIterator

////////////////////////////////
/// METHOD NAME: CMPInstruction::Execute 
////////////////////////////////
void CMPInstruction::Execute(const SLList<std::string>& rArguments, Process& rProcess)
{
    if (rArguments.GetLength() > 2) throw InvalidSyntaxException("Invalid Arguments",
                                                                 rProcess.GetFileIterator()->GetCurrentLine(),
                                                                 rProcess.GetFileIterator()->GetLineNumber());

    Registers& rProcRegs = rProcess.GetProcessRegisters();

    // Get first register from arguments
    std::string arg1Str = rArguments.Get(0);
    int32_t arg1 = rProcRegs.genRegs[atoi(arg1Str.substr(1).c_str())];

    // Second argument can be register or literal
    std::string arg2Str = rArguments.Get(1);
    int32_t arg2;
    switch (arg2Str[0])
    {
        case '#':
            arg2 = static_cast<uint32_t>(std::stoul(arg2Str.substr(1).c_str(), nullptr, 0));
            break;
        case 'r':
        case 'R':
        {
            // Get the value in the register
            int sourceReg = atoi(arg2Str.substr(1).c_str());
            arg2 = rProcRegs.genRegs[sourceReg];
            break;
        }
        default:
            throw InvalidSyntaxException(rProcess.GetFileIterator()->GetCurrentLine(),
                                         rProcRegs.PC);
            break;
    }

    int32_t signedResult = arg1 - arg2;
    uint32_t unsignedResult = static_cast<uint32_t>(arg1) - static_cast<uint32_t>(arg2);

    signedResult < 0 ? rProcRegs.SetNegativeFlag() : rProcRegs.ClearNegativeFlag();
    signedResult == 0 ? rProcRegs.SetZeroFlag() : rProcRegs.ClearZeroFlag();

    // Overflow can only occur if the numbers are different signs
    if ((arg1 & 0x80000000) != (arg2 & 0x80000000))
    {
        // Overflow occurs if the sign of the second argument is the same as the result
        if ((arg2 & 0x80000000) == (signedResult & 0x80000000))
        {
            rProcRegs.SetOverflowFlag();
        }
        else
        {
            rProcRegs.ClearOverflowFlag();
        }
    }

    if (unsignedResult > static_cast<uint32_t>(arg1) || unsignedResult > static_cast<uint32_t>(arg2))
    {
        // Clearing flag indicates a borrow occured
        rProcRegs.ClearCarryFlag();
    }
    else
    {
        rProcRegs.SetCarryFlag();
    }
    
}