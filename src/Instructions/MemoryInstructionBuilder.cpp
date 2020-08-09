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
#include "MemoryInstruction.hpp" // For MemoryInstruction
#include "InvalidSyntaxException.hpp" // For InvalidSyntaxException
#include "LineParser.hpp" // For Io::LineParser
#include "FileIterator.hpp" // For Io::FileIterator
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
    MemoryInstruction* pMemoryInstruction = new MemoryInstruction(m_opCode);

    List<std::string> tokens;
    Io::LineParser lineParser(&rInstruction);
    lineParser.Tokenize(tokens, " ,!");

    std::string memoryTranserTypeStr = tokens.Remove(0);
    if (memoryTranserTypeStr == "B")
    {
        pMemoryInstruction->SetTransferType(MemoryTransferType::UNSIGNED_BYTE);
    }
    else if (memoryTranserTypeStr == "SB")
    {
        pMemoryInstruction->SetTransferType(MemoryTransferType::SIGNED_BYTE);
        if (m_opCode != OpCode::LDR)
        {
            throw InvalidSyntaxException("Invalid instruction",
                                         pProcess->GetFileIterator()->GetCurrentLine(),
                                         pProcess->GetFileIterator()->GetLineNumber());
        }
    }
    else if (memoryTranserTypeStr == "H")
    {
        pMemoryInstruction->SetTransferType(MemoryTransferType::UNSIGNED_HALFWORD);
    }
    else if (memoryTranserTypeStr == "SH")
    {
        pMemoryInstruction->SetTransferType(MemoryTransferType::SIGNED_HALFWORD);
        if (m_opCode != OpCode::LDR)
        {
            throw InvalidSyntaxException("Invalid instruction",
                                         pProcess->GetFileIterator()->GetCurrentLine(),
                                         pProcess->GetFileIterator()->GetLineNumber());
        }
    }
    else
    {
        // Transfer type was defaulted. Add back the token
        tokens.Insert(0, memoryTranserTypeStr);
    }
    LOG_DEBUG("Memory transfer type %d", pMemoryInstruction->GetTransferType());
    
    // Remove address register from tokens once parsing it
    Register* pDestOrSrcRegister = ParseRegister(tokens[0], pProcess);
    pMemoryInstruction->SetDestOrSrcRegister(pDestOrSrcRegister);
    tokens.Remove(0);

    // Check if the next token's a label
    if (tokens[0][0] != '[' || tokens[0][0] == '=')
    {
        // Throw away the =
        if (tokens[0][0] == '=') tokens[0].erase(0, 1);
        LOG_DEBUG("Address is stored as label %s", tokens[0].c_str());

        // In this case, we'll get the address from the constants dictionary
        // and store it in the offset field of the instruction
        pMemoryInstruction->SetOffset(pProcess->GetConstantsDictionary().Get(tokens[0]));
        pMemoryInstruction->SetAddressRegisterToOffset();
        return pMemoryInstruction;
    }
    else
    {
        // Remove the open bracket
        if (tokens[0].erase(0, 1) != "[")
        {
            // TODO: Throw exception
        }
    }

    if (tokens[0].back() == ']')
    {
        // Remove the closing bracket
        tokens[0].pop_back();

        // If there is still an argument, it's postindexed
        if (tokens.GetLength() > 1)
        {
            LOG_DEBUG("Postindexed memory instruction");
            pMemoryInstruction->SetOffsetType(OffsetType::POSTINDEXED);
        }
    }

    // Parse the address register and remove it
    Register* pAddressRegister = ParseRegister(tokens[0], pProcess);
    pMemoryInstruction->SetAddressRegister(pAddressRegister);
    tokens.Remove(0);

    if (!tokens.IsEmpty())
    {
        if (tokens[0].back() == ']')
        {
            tokens[0].pop_back();
            LOG_DEBUG("Preindexed memory instruction");
            pMemoryInstruction->SetOffsetType(OffsetType::PREINDEXED);
        }

        pMemoryInstruction->SetOffset(ParseFlexOffset(tokens[0], pProcess));
    }

    if (rInstruction.find('!') != std::string::npos)
    {
        LOG_DEBUG("Preindexed memory instruction with update");
        pMemoryInstruction->SetOffsetType(OffsetType::PREINDEXED_WITH_UPDATE);
    }
    
    return pMemoryInstruction;
}

////////////////////////////////
/// METHOD NAME: MemoryInstructionBuilder::BuildMultipleMemoryInstruction 
////////////////////////////////
MultipleMemoryInstruction* MemoryInstructionBuilder::BuildMultipleMemoryInstruction(std::string& rInstruction, Process* pProcess)
{
    MultipleMemoryInstruction* pMultipleMemoryInstruction = new MultipleMemoryInstruction(m_opCode);
    List<Register*>& rRegList = pMultipleMemoryInstruction->GetRegisterList();

    LOG_DEBUG("rInstruction: %s", rInstruction.c_str());

    List<std::string> tokens;
    Io::LineParser lineParser(&rInstruction);
    lineParser.Tokenize(tokens, " ,{}!");

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
        // Addressing mode determination
        std::string addressingModeStr = tokens.Remove(0);
        if (addressingModeStr == "IB")
        {
            pMultipleMemoryInstruction->SetAddressingMode(AddressingMode::IB);
        }
        else if (addressingModeStr == "IA")
        {
            // Addressing mode is defaulted to IA
        }
        else if (addressingModeStr == "DB")
        {
            pMultipleMemoryInstruction->SetAddressingMode(AddressingMode::DB);
        }
        else if (addressingModeStr == "DA")
        {
            pMultipleMemoryInstruction->SetAddressingMode(AddressingMode::DA);
        }
        else
        {
            // The address mode was not present, so return the string to the instruction
            tokens.Insert(0, addressingModeStr);
        }

        // Remove address register from tokens once parsing it
        Register* pAddressRegister = ParseRegister(tokens[0], pProcess);
        pMultipleMemoryInstruction->SetAddressRegister(pAddressRegister);
        tokens.Remove(0);

        if (rInstruction.find('!') != std::string::npos)
        {
            pMultipleMemoryInstruction->SetUpdateFlag();
        }
    }

    // For every token...
    for (uint8_t i = 0; i < tokens.GetLength(); i++)
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
        case OpCode::STM:
            rRegList.Sort([](Register*& a, Register*& b) { return a < b; });
            break;
        case OpCode::POP:
        case OpCode::LDM:
            rRegList.Sort([](Register*& a, Register*& b) { return a > b; });
            break;
        default:
            ASSERT(false, "Invalid opcode %d", m_opCode);
    }

    return pMultipleMemoryInstruction;
}

////////////////////////////////
/// METHOD NAME: MemoryInstructionBuilder::ParseFlexOffset
////////////////////////////////
int32_t MemoryInstructionBuilder::ParseFlexOffset(const std::string& rToken, const Process* pProcess)
{
    LOG_DEBUG("Parsing %s as a flex offset", rToken.c_str());
    int32_t offset = 0;
    if (rToken[0] == '#')
    {
        // Offset should only be a 12 bit signed number
        uint32_t fullOffset = static_cast<uint32_t>(std::stoul(rToken.substr(1).c_str(), nullptr, 0));
        fullOffset &= ~(0xFFFFF000);
        offset = static_cast<int32_t>(fullOffset);
    }
    else
    {
        // TODO: Parse register as offset
    }
    LOG_DEBUG("Offset parsed to be %d", offset);
    return offset;
}