/////////////////////////////////
/// @file FlowCtrlInstructionBuilder.cpp
///
/// @brief Implementation for FlowCtrlInstructionBuilder
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "FlowCtrlInstructionBuilder.hpp" // Header for class
#include "FlowCtrlInstruction.hpp" // For FlowCtrlInstruction
#include "InvalidSyntaxException.hpp" // For InvalidSyntaxException
#include "LineParser.hpp" // For Io::LineParser
#include "FileIterator.hpp" // For Io::FileIterator
#include "Logger.hpp" // For LOG_DEBUG
#include "Process.hpp" // For Process

////////////////////////////////
/// METHOD NAME: FlowCtrlInstructionBuilder::BuildInstruction 
////////////////////////////////
InstructionBase* FlowCtrlInstructionBuilder::BuildInstruction(std::string& rInstruction, Process* pProcess)
{
    FlowCtrlInstruction* pInstruction = new FlowCtrlInstruction(m_opCode);

    LOG_DEBUG("rInstruction = %s", rInstruction.c_str());

    // TODO: Change GetArguments into Tokenize
    // Add a character as a placeholder to the keyword
    rInstruction.insert(rInstruction.find_first_of(' '), "|");

    // Create a line parser to retrieve the remaining arguments
    Io::LineParser lineParser(&rInstruction);
    SLList<std::string> arguments;
    lineParser.GetArguments(arguments);

    std::string arg = arguments[0];
    Register newPC;
    try
    {
        newPC = pProcess->GetLabelDictionary().Get(arg);
        if (m_opCode == OpCode::BX)
        {
            throw InvalidSyntaxException("Invalid argument",
                                        pProcess->GetFileIterator()->GetCurrentLine(),
                                        pProcess->GetFileIterator()->GetLineNumber());
        }
    }
    catch(const DLB<uint32_t>::KeyNotFoundException& e)
    {
        // BLX and BX allow a register as an argument
        if (m_opCode == OpCode::BLX || m_opCode == OpCode::BX)
        {
            newPC = *(ParseRegister(arg, pProcess));
        }
        else
        {
            LOG_DEBUG("Label %s not found", arg.c_str());
            throw InvalidSyntaxException("Label Not Found",
                                        pProcess->GetFileIterator()->GetCurrentLine(),
                                        pProcess->GetFileIterator()->GetLineNumber());
        }
    }

    pInstruction->SetNewPC(newPC);

    if (m_opCode == OpCode::BLX || m_opCode == OpCode::BL)
    {
        pInstruction->SetLinkFlag();
    }

    return pInstruction;
}

