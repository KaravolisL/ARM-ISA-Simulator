/////////////////////////////////
/// @file ArithAndLogicInstructionBuilder.cpp
///
/// @brief Implementation for ArithAndLogicInstructionBuilder
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "ArithAndLogicInstructionBuilder.hpp" // Header for class
#include "ArithAndLogicInstruction.hpp" // For ArithAndLogicInstruction
#include "InvalidSyntaxException.hpp" // For InvalidSyntaxException
#include "Process.hpp" // For Process
#include "SLList.hpp" // For SLList
#include "LineParser.hpp" // For Io::LineParser
#include "Assert.hpp" // For ASSERT
#include "Logger.hpp" // For LOB_DEBUG

////////////////////////////////
/// METHOD NAME: ArithAndLogicInstructionBuilder::BuildInstruction 
////////////////////////////////
InstructionBase* ArithAndLogicInstructionBuilder::BuildInstruction(std::string& rInstruction, Process* pProcess)
{
    ArithAndLogicInstruction* pInstruction = new ArithAndLogicInstruction();

    // Check for the S flag
    std::string keyword = rInstruction.substr(0, rInstruction.find_first_of(' '));
    if (CheckSFlag(keyword)) 
    {
        pInstruction->SetSFlag();
    }

    // Create a line parser to retrieve the remaining arguments
    Io::LineParser lineParser(&rInstruction);
    SLList<std::string> arguments;
    lineParser.GetArguments(arguments);

    // Parse the destination
    Register* pDestination = ParseDestination(arguments[0], pProcess);
    pInstruction->SetDestination(pDestination);

    // Parse the first argument


    // Parse the second argument if applicable


    // Add the actual operation based on the opcode

    LOG_DEBUG("m_opCode = %d", m_opCode);

    switch (m_opCode)
    {
    case OpCode::ADD:
        pInstruction->SetOperation([](Register a, Register b) { return a + b; });
        break;
    
    default:
        break;
    }


    return nullptr;
}

////////////////////////////////
/// METHOD NAME: ArithAndLogicInstructionBuilder::CheckSFlag 
////////////////////////////////
bool ArithAndLogicInstructionBuilder::CheckSFlag(std::string& rKeyword) const
{
    if (rKeyword.length() > 1 && rKeyword[0] == 'S')
    {
        LOG_DEBUG("Instruction will set the flags");
        rKeyword = rKeyword.substr(1);
        return true;
    }
    else
    {
        return false;
    }
}

////////////////////////////////
/// METHOD NAME: ArithAndLogicInstructionBuilder::ParseDestination 
////////////////////////////////
Register* ArithAndLogicInstructionBuilder::ParseDestination(std::string& rDestStr, Process* pProcess) const
{
    LOG_DEBUG("rDestStr = %s", rDestStr.c_str());

    if (rDestStr[0] != 'R' && rDestStr[0] != 'r')
    {
        // TODO: Throw SyntaxException
    }

    // Convert string to register number 
    uint8_t regNumber = atoi(rDestStr.substr(1).c_str());

    return &pProcess->GetProcessRegisters().genRegs[regNumber];
}
