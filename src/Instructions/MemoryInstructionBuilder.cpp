/////////////////////////////////
/// @file MemoryInstructionBuilder.cpp
///
/// @brief Implementation for MemoryInstructionBuilder
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "MemoryInstructionBuilder.hpp" // Header for class
#include "MemoryInstruction.hpp" // For MemoryInstruction
#include "MultipleMemoryInstruction.hpp" // For MultipleMemoryInstruction
#include "LineParser.hpp" // For Io::LineParser
#include "Process.hpp" // Fpr Process
#include "Assert.hpp" // For ASSERT
#include "Logger.hpp" // For LOG_DEBUG

////////////////////////////////
/// METHOD NAME: MemoryInstructionBuilder::BuildInstruction 
////////////////////////////////
InstructionBase* MemoryInstructionBuilder::BuildInstruction(std::string& rInstruction, Process* pProcess)
{
    InstructionBase* pInstruction = nullptr;

    LOG_DEBUG("m_opCode = %d", m_opCode);
    switch (m_opCode)
    {
        case OpCode::PUSH:
        case OpCode::POP:
        case OpCode::LDM:
        case OpCode::STM:
            pInstruction = BuildMultipleMemoryInstruction(rInstruction, pProcess);
            break;
        case OpCode::LDR:
        case OpCode::STR:
            pInstruction = BuildMemoryInstruction(rInstruction, pProcess);
            break;
        default:
            ASSERT(false, "Invalid opcode %d", m_opCode);
    }
    
    ASSERT(pInstruction != nullptr);
    return pInstruction;
}

////////////////////////////////
/// METHOD NAME: MemoryInstructionBuilder::BuildMemoryInstruction 
////////////////////////////////
MemoryInstruction* MemoryInstructionBuilder::BuildMemoryInstruction(std::string& rInstruction, Process* pProcess)
{
    ASSERT(false, "Feature not implemented");
    return nullptr;
}

////////////////////////////////
/// METHOD NAME: MemoryInstructionBuilder::BuildMultipleMemoryInstruction 
////////////////////////////////
MultipleMemoryInstruction* MemoryInstructionBuilder::BuildMultipleMemoryInstruction(std::string& rInstruction, Process* pProcess)
{
    MultipleMemoryInstruction* pMultipleMemoryInstruction = new MultipleMemoryInstruction(m_opCode);
    List<Register*>& rRegList = pMultipleMemoryInstruction->GetRegisterList();

    LOG_DEBUG("rInstruction: %s", rInstruction.c_str());

    if (m_opCode == OpCode::PUSH)
    {
        pMultipleMemoryInstruction->SetAddressingMode(AddressingMode::DB);
        pMultipleMemoryInstruction->SetAddressRegister(&pProcess->GetProcessRegisters().SP);
        pMultipleMemoryInstruction->SetUpdateFlag();
    }
    else if (m_opCode == OpCode::POP)
    {
        // AddressingMode defaults to IB
        pMultipleMemoryInstruction->SetAddressRegister(&pProcess->GetProcessRegisters().SP);
        pMultipleMemoryInstruction->SetUpdateFlag();
    }
    else
    {
        // Mode, address register, update flag
    }

    List<std::string> tokens;
    Io::LineParser lineParser(&rInstruction);
    lineParser.Tokenize(tokens, " ,{}");

    // For every token...
    for (int i = 0; i < tokens.GetLength(); i++)
    {
        LOG_DEBUG("Current argument = %s", tokens[i].c_str());
        // Determine whether it's a range or not
        if (tokens[i].find('-') == std::string::npos)
        {
            Register* pReg;
            // Argument should either be LR or a register
            if (tokens[i].find('l') == std::string::npos && tokens[i].find('L') == std::string::npos)
            {
                uint32_t regNumber = static_cast<uint32_t>(std::stoul(tokens[i].substr(1).c_str(), nullptr, 0));
                pReg = &pProcess->GetProcessRegisters().genRegs[regNumber];
            }
            else
            {
                pReg = &pProcess->GetProcessRegisters().LR;
            }
            rRegList.Append(pReg);
        }
        else
        {
            std::string beginStr = tokens[i].substr(1, tokens[i].find('-') - 1);
            uint32_t begin = static_cast<uint32_t>(std::stoul(beginStr.c_str(), nullptr, 0));

            std::string endStr = tokens[i].substr(tokens[i].find('-') + 2);
            uint32_t end = static_cast<uint32_t>(std::stoul(endStr.c_str(), nullptr, 0));

            for (uint8_t i = begin; i <= end; i++)
            {
                rRegList.Append(&pProcess->GetProcessRegisters().genRegs[i]);
            }
        }
    }

    switch (m_opCode)
    {
        case OpCode::PUSH:
            rRegList.Sort([](Register*& a, Register*& b) { return a < b; });
            break;
        case OpCode::POP:
            rRegList.Sort([](Register*& a, Register*& b) { return a > b; });
            break;
        default:
            ASSERT(false, "Invalid opcode %d", m_opCode);
    }

    for (int i = 0; i < rRegList.GetLength(); i++)
    {
        if (m_opCode == OpCode::PUSH)
        {
            pProcess->GetProcessStack().Push(*(rRegList[i]));
        }
        else
        {
            *(rRegList[i]) = pProcess->GetProcessStack().Pop();
        }
    }

    return pMultipleMemoryInstruction;
}