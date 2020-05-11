/////////////////////////////////
/// @file POPInstruction.cpp
///
/// @brief Implementation for POPInstruction
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <string>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "POPInstruction.hpp" // Header for class
#include "Assert.hpp" // for ASSERT
#include "SLList.hpp" // For SLList
#include "Process.hpp" // For Process
#include "FileIterator.hpp" // For Io::FileIterator
#include "Logger.hpp"
#include "InvalidSyntaxException.hpp" // For InvalidSyntaxException

////////////////////////////////
/// METHOD NAME: POPInstruction::Execute 
////////////////////////////////
void POPInstruction::Execute(const SLList<std::string>& rArguments, Process& rProcess)
{
    // For every token...
    for (SLList<std::string>::SLListIterator it = rArguments.GetBegin(); it != rArguments.GetEnd(); it++)
    {
        // Determine whether it's a range or not
        if ((*it).find('-') == std::string::npos)
        {
            Register* pReg;
            // Argument should either be LR or a register
            if ((*it).find('l') == std::string::npos && (*it).find('L') == std::string::npos)
            {
                uint32_t regNumber = static_cast<uint32_t>(std::stoul((*it).substr(1).c_str(), nullptr, 0));
                pReg = &rProcess.GetProcessRegisters().genRegs[regNumber];
            }
            else
            {
                pReg = &rProcess.GetProcessRegisters().LR;
            }
            *pReg = rProcess.GetProcessStack().Pop();
            LOG_DEBUG("Just popped %d from stack", *pReg);
        }
        else
        {
            ASSERT(false, "Unsupported feature");
        }   
    }
}