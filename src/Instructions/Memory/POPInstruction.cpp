/////////////////////////////////
/// @file POPInstruction.cpp
///
/// @brief Implementation for POPInstruction
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <string>
#include <list>

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
    std::list<Register*> regList = std::list<Register*>();


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
            regList.push_back(pReg);
        }
        else
        {
            std::string beginStr = (*it).substr(1, (*it).find('-') - 1);
            uint32_t begin = static_cast<uint32_t>(std::stoul(beginStr.c_str(), nullptr, 0));

            std::string endStr = (*it).substr((*it).find('-') + 2);
            uint32_t end = static_cast<uint32_t>(std::stoul(endStr.c_str(), nullptr, 0));

            for (uint8_t i = begin; i <= end; i++)
            {
                regList.push_back(&rProcess.GetProcessRegisters().genRegs[i]);
            }
        }   
    }

    // Sort the list in ascending order based on pointer values
    regList.sort();

    // Traverse the list in reverse and pop
    for (std::reverse_iterator it = regList.rbegin();
         it != regList.rend(); it++)
    {
        LOG_DEBUG("Popping %d from the stack", rProcess.GetProcessStack().Peek());
        *(*it) = rProcess.GetProcessStack().Pop();
    }
}