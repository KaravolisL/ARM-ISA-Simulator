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
#include "ANDInstruction.hpp" // For AND
#include "BICInstruction.hpp" // For BIC
#include "EORInstruction.hpp" // For EOR
#include "ORRInstruction.hpp" // For ORR
#include "BInstruction.hpp" // For B
#include "CMPInstruction.hpp" // For CMP
#include "Logger.hpp" // For Logger

static MOVInstruction f_MOV = MOVInstruction();

static ADDInstruction f_ADD = ADDInstruction();
static ANDInstruction f_AND = ANDInstruction();
static BICInstruction f_BIC = BICInstruction();
static EORInstruction f_EOR = EORInstruction();
static ORRInstruction f_ORR = ORRInstruction();

static CMPInstruction f_CMP = CMPInstruction();
static BInstruction f_B = BInstruction();

////////////////////////////////
/// METHOD NAME: InstructionRepository::Initialize 
////////////////////////////////
void InstructionRepository::Initialize()
{
    m_instructionDict.Insert("MOV", &f_MOV);

    m_instructionDict.Insert("ADD", &f_ADD);
    m_instructionDict.Insert("AND", &f_AND);
    m_instructionDict.Insert("BIC", &f_BIC);
    m_instructionDict.Insert("EOR", &f_EOR);
    m_instructionDict.Insert("ORR", &f_ORR);

    m_instructionDict.Insert("CMP", &f_CMP);
    m_instructionDict.Insert("B", &f_B);

    LOG_INFO("Instruction Repository Initialized");
}

////////////////////////////////
/// METHOD NAME: InstructionRepository::GetInstruction 
////////////////////////////////
InstructionBase* InstructionRepository::GetInstruction(std::string& rInstruction)
{
    // Determine if the instruction needs to set the flags
    bool flagged = false;
    if (rInstruction.at(rInstruction.length() - 1) == 's')
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