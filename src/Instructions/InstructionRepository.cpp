/////////////////////////////////
/// @file InstructionRepository.cpp
///
/// @brief Implementation for InstructionRepository
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "Assert.hpp" // For ASSERT
#include "InstructionRepository.hpp" // Header for class
#include "InvalidSyntaxException.hpp" // For InvalidSyntaxException
#include "MOVInstruction.hpp" // For MOV
#include "ADDInstruction.hpp" // For ADD
#include "SUBInstruction.hpp" // For SUB
#include "ANDInstruction.hpp" // For AND
#include "BICInstruction.hpp" // For BIC
#include "EORInstruction.hpp" // For EOR
#include "ORRInstruction.hpp" // For ORR
#include "BInstruction.hpp" // For B
#include "BLInstruction.hpp" // For BL
#include "BXInstruction.hpp" // For BX
#include "BLXInstruction.hpp" // For BLX
#include "CMPInstruction.hpp" // For CMP
#include "CMNInstruction.hpp" // For CMN
#include "NOPInstruction.hpp" // For NOP
#include "PUSHInstruction.hpp" // For PUSH
#include "POPInstruction.hpp" // For POP
#include "Registers.hpp" // For Registers
#include "Process.hpp" // For Process
#include "Logger.hpp" // For Logger

static ADDInstruction f_ADD = ADDInstruction();
static SUBInstruction f_SUB = SUBInstruction();

static CMPInstruction f_CMP = CMPInstruction();
static CMNInstruction f_CMN = CMNInstruction();

static BInstruction f_B = BInstruction();
static BLInstruction f_BL = BLInstruction();
static BXInstruction f_BX = BXInstruction();
static BLXInstruction f_BLX = BLXInstruction();

static ANDInstruction f_AND = ANDInstruction();
static BICInstruction f_BIC = BICInstruction();
static EORInstruction f_EOR = EORInstruction();
static ORRInstruction f_ORR = ORRInstruction();

static PUSHInstruction f_PUSH = PUSHInstruction();
static POPInstruction f_POP = POPInstruction();

static MOVInstruction f_MOV = MOVInstruction();
static NOPInstruction f_NOP = NOPInstruction();

////////////////////////////////
/// METHOD NAME: InstructionRepository::Initialize 
////////////////////////////////
void InstructionRepository::Initialize()
{
    // Instruction dictionary
    m_instructionDict.Insert("ADD", &f_ADD);
    m_instructionDict.Insert("SUB", &f_SUB);

    m_instructionDict.Insert("CMP", &f_CMP);
    m_instructionDict.Insert("CMN", &f_CMN);

    m_instructionDict.Insert("B", &f_B);
    m_instructionDict.Insert("BL", &f_BL);
    m_instructionDict.Insert("BX", &f_BX);
    m_instructionDict.Insert("BLX", &f_BLX);

    m_instructionDict.Insert("AND", &f_AND);
    m_instructionDict.Insert("BIC", &f_BIC);
    m_instructionDict.Insert("EOR", &f_EOR);
    m_instructionDict.Insert("ORR", &f_ORR);

    m_instructionDict.Insert("PUSH", &f_PUSH);
    m_instructionDict.Insert("POP", &f_POP);

    m_instructionDict.Insert("MOV", &f_MOV);
    m_instructionDict.Insert("NOP", &f_NOP);

    // Conditional codes dictionary
    m_conditionalCodeDict.Insert("EQ", ConditionalCode::EQ);
    m_conditionalCodeDict.Insert("NE", ConditionalCode::NE);
    m_conditionalCodeDict.Insert("GT", ConditionalCode::GT);
    m_conditionalCodeDict.Insert("LT", ConditionalCode::LT);
    m_conditionalCodeDict.Insert("GE", ConditionalCode::GE);
    m_conditionalCodeDict.Insert("LE", ConditionalCode::LE);
    m_conditionalCodeDict.Insert("CS", ConditionalCode::CS);
    m_conditionalCodeDict.Insert("HS", ConditionalCode::CS);
    m_conditionalCodeDict.Insert("CC", ConditionalCode::CC);
    m_conditionalCodeDict.Insert("LO", ConditionalCode::CC);
    m_conditionalCodeDict.Insert("MI", ConditionalCode::MI);
    m_conditionalCodeDict.Insert("PL", ConditionalCode::PL);
    m_conditionalCodeDict.Insert("AL", ConditionalCode::AL);
    m_conditionalCodeDict.Insert("NV", ConditionalCode::NV);
    m_conditionalCodeDict.Insert("VS", ConditionalCode::VS);
    m_conditionalCodeDict.Insert("VC", ConditionalCode::VC);
    m_conditionalCodeDict.Insert("HI", ConditionalCode::HI);
    m_conditionalCodeDict.Insert("LS", ConditionalCode::LS);

    LOG_INFO("Instruction Repository Initialized");
}

////////////////////////////////
/// METHOD NAME: InstructionRepository::GetInstruction 
////////////////////////////////
InstructionBase* InstructionRepository::GetInstruction(std::string& rInstruction, Process& rProcess)
{
    if (CheckConditionalCode(rInstruction, rProcess.GetProcessRegisters()) == false)
    {
        LOG_DEBUG("Do not execute this instruction");
        return &f_NOP;
    }

    // Determine if the instruction needs to set the flags
    bool flagged = false;
    if (rInstruction.at(rInstruction.length() - 1) == 'S')
    {
        flagged = true;
        rInstruction.pop_back();
    }

    InstructionBase* pInstructionBase;
    try
    {
        pInstructionBase = m_instructionDict.Get(rInstruction);
    }
    catch(const HashMap<InstructionBase*>::KeyNotFoundException& e)
    {
        throw InvalidSyntaxException("Instruction not supported", rInstruction);
    }

    // Configure instruction
    flagged ? pInstructionBase->SetFlagged() : pInstructionBase->ClearFlagged();

    ASSERT(pInstructionBase != nullptr);
    
    return pInstructionBase;
}

////////////////////////////////
/// METHOD NAME: InstructionRepository::CheckConditionalCode 
////////////////////////////////
bool InstructionRepository::CheckConditionalCode(std::string& rInstruction, const Registers& rRegisters)
{
    std::string codeStr;
    // This mess of logic ensures that only instructions with valid conditional codes
    // proceed through the function. If the instruction is longer than 4 characters,
    // the last two characters are checked against condition codes. Otherwise, if 
    // the instruction starts with a B, and it's long enough to have a condition code
    // then it's last two characters are checked
    if (rInstruction.length() >= 5)
    {
        codeStr = rInstruction.substr(rInstruction.length() - 2);
        if (!m_conditionalCodeDict.Contains(codeStr)) return true;
    }
    else
    {
        if (rInstruction[0] == 'B' && rInstruction.length() >= 3)
        {
            codeStr = rInstruction.substr(rInstruction.length() - 2);
            if (!m_conditionalCodeDict.Contains(codeStr)) return true;
        }
        else
        {
            return true;
        }
    }

    bool execute = false;
    ConditionalCode code = m_conditionalCodeDict.Get(codeStr);

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
        ASSERT("Invalid conditional code: %d", code);
        break;
    }

    // Strip the instruction of the conditional code
    rInstruction = rInstruction.substr(0, rInstruction.length() - 2);

    return execute;
}