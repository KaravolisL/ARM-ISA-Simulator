/////////////////////////////////
/// @file InstructionBuilder.cpp
///
/// @brief Implementation for InstructionBuilder
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "InstructionBuilder.hpp" // Header for class
#include "InstructionBase.hpp" // For InstructionBase
#include "InstructionBuilderRepository.hpp" // For InstructionBuilderRepository
#include "NOPInstruction.hpp" // For NOPInstruction
#include "InvalidSyntaxException.hpp" // For InvalidSyntaxException
#include "Process.hpp" // For Process
#include "Assert.hpp" // For ASSERT
#include "Logger.hpp" // For LOB_DEBUG
#include "KeywordDict.hpp" // For KeywordDict

////////////////////////////////
/// METHOD NAME: InstructionBuilder::BuildInstruction 
////////////////////////////////
InstructionBase* InstructionBuilder::BuildInstruction(std::string& rInstruction, Process* pProcess)
{
    std::string keyword = rInstruction.substr(0, rInstruction.find_first_of(' '));
    LOG_DEBUG("Full keyword: %s", keyword.c_str());

    // Determine the operation of the instruction
    OpCode opCode = DetermineOpCode(keyword);

    // Determine whether instruction should be executed based on conditional code
    if (CheckConditionalCode(keyword, pProcess->GetProcessRegisters()) == false || opCode == OpCode::NOP)
    {
        LOG_DEBUG("Instruction will not be executed");
        return new NOPInstruction();
    }

    // Update the instruction based on how it has been modified
    uint8_t numCharsToRemove = rInstruction.substr(0, rInstruction.find_first_of(' ')).length() - keyword.length();
    rInstruction.erase(0, numCharsToRemove);

    LOG_DEBUG("New Instruction: %s", rInstruction.c_str());

    // Obtain a specific builder based on the opcode
    InstructionBuilder* pInstructionSpecificBuilder = InstructionBuilderRepository::GetInstructionBuilder(opCode);
    pInstructionSpecificBuilder->m_opCode = opCode;

    // Actually build the instruction using the arguments
    InstructionBase* pInstruction = pInstructionSpecificBuilder->BuildInstruction(rInstruction, pProcess);

    ASSERT(pInstruction != nullptr);
    return pInstruction;
}

////////////////////////////////
/// METHOD NAME: InstructionBuilder::DetermineOpCode 
////////////////////////////////
OpCode InstructionBuilder::DetermineOpCode(std::string& rKeyword) const
{
    ASSERT(rKeyword.length() != 0);

    OpCode opCode = OpCode::INVALID;
    std::string baseInstruction;

    // Instructions that start with B need special handling, since
    // they could have similar compositions and be less than three characters
    if (rKeyword[0] == 'B')
    {
        if (rKeyword.find("BIC") != std::string::npos)
        {
            baseInstruction = "BIC";
        }
        else if (rKeyword.find("BLX") != std::string::npos)
        {
            baseInstruction = "BLX";
        }
        else if (rKeyword.find("BX") != std::string::npos)
        {
            baseInstruction = "BX";
        }
        else
        {
            // BL will always have an even number of characters
            // B will always have an odd number of characters
            if (rKeyword.length() % 2 == 0)
            {
                baseInstruction = "BL";
            }
            else
            {
                baseInstruction = "B";
            }
        }
    }
    else
    {
        baseInstruction = rKeyword.substr(0, 3);
        if (baseInstruction == "PUS") baseInstruction = "PUSH";
    }

    LOG_DEBUG("Base Instruction: %s", baseInstruction.c_str());
    
    try
    {
        opCode = KeywordDict::GetInstance().GetInstructionDict().Get(baseInstruction);
    }
    catch(const HashMap<OpCode>::KeyNotFoundException& e)
    {
        throw InvalidSyntaxException("Instruction not supported", rKeyword);
    }

    ASSERT(opCode != OpCode::INVALID);

    LOG_DEBUG("OpCode: %d", opCode);

    // Strip the opcode from the keyword
    rKeyword = rKeyword.substr(baseInstruction.length());

    LOG_DEBUG("New Keyword: %s", rKeyword.c_str());

    return opCode;   
}

////////////////////////////////
/// METHOD NAME: InstructionBuilder::CheckConditionalCode 
////////////////////////////////
bool InstructionBuilder::CheckConditionalCode(std::string& rKeyword, const Registers& rRegisters) const
{
    LOG_DEBUG("rKeyword: %s", rKeyword.c_str());

    // If the instruction is too short to contain a conditional code, it should be executed
    if (rKeyword.length() < 2) return true;

    std::string codeStr = rKeyword.substr(0, 2);
    LOG_DEBUG("codeStr = %s", codeStr.c_str());

    // If the conditional code is not in the dictionary, it should be executed
    if (!KeywordDict::GetInstance().GetConditionalCodeDict().Contains(codeStr)) return true;

    bool execute = false;
    ConditionalCode code = KeywordDict::GetInstance().GetConditionalCodeDict().Get(codeStr);

    LOG_DEBUG("Checking flags : CPSR = %d", rRegisters.CPSR);

    // Determine whether the instruction should be executed or not
    switch (code)
    {
    case ConditionalCode::EQ:
        if (rRegisters.GetZeroFlag()) execute = true;
        break;
    case ConditionalCode::NE:
        if (!rRegisters.GetZeroFlag()) execute = true;
        break;
    case ConditionalCode::GT:
        if (!rRegisters.GetZeroFlag() && (rRegisters.GetNegativeFlag() == rRegisters.GetOverflowFlag())) execute = true;
        break;
    case ConditionalCode::LT:
        if (rRegisters.GetNegativeFlag() != rRegisters.GetOverflowFlag()) execute = true;
        break;
    case ConditionalCode::GE:
        if (rRegisters.GetNegativeFlag() == rRegisters.GetOverflowFlag()) execute = true;
        break;
    case ConditionalCode::LE:
        if ((rRegisters.GetNegativeFlag() != rRegisters.GetOverflowFlag()) || rRegisters.GetZeroFlag()) execute = true;
        break;
    case ConditionalCode::CS:
        if (rRegisters.GetCarryFlag()) execute = true;
        break;
    case ConditionalCode::CC:
        if (!rRegisters.GetCarryFlag()) execute = true;
        break;
    case ConditionalCode::MI:
        if (rRegisters.GetNegativeFlag()) execute = true;
        break;
    case ConditionalCode::PL:
        if (!rRegisters.GetNegativeFlag()) execute = true;
        break;
    case ConditionalCode::AL:
        execute = true;
        break;
    case ConditionalCode::NV:
        break;
    case ConditionalCode::VS:
        if (rRegisters.GetOverflowFlag()) execute = true;
        break;
    case ConditionalCode::VC:
        if (!rRegisters.GetOverflowFlag()) execute = true;
        break;
    case ConditionalCode::HI:
        if (rRegisters.GetCarryFlag() && !rRegisters.GetZeroFlag()) execute = true;
        break;
    case ConditionalCode::LS:
        if (!rRegisters.GetCarryFlag() || !rRegisters.GetZeroFlag()) execute = true;
        break;
    
    default:
        ASSERT(false, "Invalid conditional code: %d", code);
        break;
    }

    // Strip the instruction of the conditional code
    rKeyword = rKeyword.substr(2);

    return execute;
}

////////////////////////////////
/// METHOD NAME: InstructionBuilder::ParseRegister 
////////////////////////////////
Register* InstructionBuilder::ParseRegister(const std::string& rRegStr, Process* pProcess) const
{
    LOG_DEBUG("InstructionBuilder::ParseRegister: Parsing %s", rRegStr.c_str());

    if (rRegStr[0] != 'R' && rRegStr[0] != 'r')
    {
        if (rRegStr == "LR")
        {
            return &pProcess->GetProcessRegisters().LR;
        }
        else if (rRegStr == "SP")
        {
            return &pProcess->GetProcessRegisters().SP;
        }
        else
        {
            throw InvalidSyntaxException("Invalid argument", rRegStr);
        }
    }
    else
    {
        try
        {
            // Convert string to register number 
            uint8_t regNumber = atoi(rRegStr.substr(1).c_str());
            return &pProcess->GetProcessRegisters().genRegs[regNumber];
        }
        catch(const std::exception& e)
        {
            throw InvalidSyntaxException("Invalid argument", rRegStr);
        }
    }
}
