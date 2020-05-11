/////////////////////////////////
/// @file PUSHInstruction.cpp
///
/// @brief Implementation for PUSHInstruction
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <string>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "PUSHInstruction.hpp" // Header for class
#include "Assert.hpp" // for ASSERT
#include "SLList.hpp" // For SLList
#include "Process.hpp" // For Process
#include "FileIterator.hpp" // For Io::FileIterator
#include "InvalidSyntaxException.hpp" // For InvalidSyntaxException
#include "Logger.hpp"

////////////////////////////////
/// METHOD NAME: PUSHInstruction::Execute 
////////////////////////////////
void PUSHInstruction::Execute(const SLList<std::string>& rArguments, Process& rProcess)
{
    // For every token...
    for (SLList<std::string>::SLListIterator it = rArguments.GetBegin(); it != rArguments.GetEnd(); it++)
    {
        LOG_DEBUG("Current argument = %s", (*it).c_str());
        // Determine whether it's a range or not
        if ((*it).find('-') == std::string::npos)
        {
            Register reg;
            // Argument should either be LR or a register
            if ((*it).find('l') == std::string::npos && (*it).find('L') == std::string::npos)
            {
                uint32_t regNumber = static_cast<uint32_t>(std::stoul((*it).substr(1).c_str(), nullptr, 0));
                reg = rProcess.GetProcessRegisters().genRegs[regNumber];
            }
            else
            {
                reg = rProcess.GetProcessRegisters().LR;
            }
            LOG_DEBUG("Just pushed %d onto stack", reg);
            rProcess.GetProcessStack().Push(reg);
        }
        else
        {
            ASSERT(false, "Unsupported feature");
        }   
    }
}