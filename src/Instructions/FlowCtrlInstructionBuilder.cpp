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
#include "List.hpp" // For List
#include "LineParser.hpp" // For Io::LineParser
#include "FileIterator.hpp" // For Io::FileIterator
#include "Logger.hpp" // For LOG_INSTRUCTION
#include "Process.hpp" // For Process

////////////////////////////////
/// METHOD NAME: FlowCtrlInstructionBuilder::BuildInstruction 
////////////////////////////////
InstructionBase* FlowCtrlInstructionBuilder::BuildInstruction(std::string& rInstruction, Process* pProcess)
{
    FlowCtrlInstruction* pInstruction = new FlowCtrlInstruction(m_opCode);

    LOG_INSTRUCTION("rInstruction = %s", rInstruction.c_str());

    Io::LineParser lineParser(&rInstruction);
    List<std::string> arguments;
    lineParser.Tokenize(arguments);

    std::string arg = arguments[0];
    Register newPC;
    try
    {
        newPC = pProcess->GetLabelDictionary().Get(arg);
        if (m_opCode == OpCode::BX)
        {
            LOG_ERROR("BX does not accept a label as an argument");
            throw InvalidSyntaxException("Invalid argument",
                                        pProcess->GetFileIterator()->GetCurrentLine(),
                                        pProcess->GetFileIterator()->GetLineNumber());
        }

        if (m_opCode == OpCode::BL)
        {
            // Add to the call stack
            pProcess->GetMetadata().GetCallStack().Push(arg);
        }
    }
    catch(const DLB<uint32_t>::KeyNotFoundException& e)
    {
        // BLX and BX allow a register as an argument
        if (m_opCode == OpCode::BLX || m_opCode == OpCode::BX)
        {
            newPC = *(ParseRegister(arg, pProcess));

            // Pop from the call stack
            pProcess->GetMetadata().GetCallStack().Pop();
        }
        else
        {
            LOG_INSTRUCTION("Label %s not found", arg.c_str());
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

