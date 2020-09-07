/////////////////////////////////
/// @file InstructionBuilderRepository.cpp
///
/// @brief Implementation for InstructionBuilderRepository
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "InstructionBuilderRepository.hpp" // Header for class
#include "ArithAndLogicInstructionBuilder.hpp" // For ArithAndLogicInstructionBuilder
#include "FlowCtrlInstructionBuilder.hpp" // For FlowCtrlInstructionBuilder
#include "MemoryInstructionBuilder.hpp" // For MemoryInstructionBuilder
#include "Logger.hpp" // For LOG_INSTRUCTION
#include "Assert.hpp" // For ASSERT

static ArithAndLogicInstructionBuilder f_arithAndLogicInstructionBuilder;
static FlowCtrlInstructionBuilder f_flowCtrlInstructionBuilder;
static MemoryInstructionBuilder f_memoryInstructionBuilder;

////////////////////////////////
/// METHOD NAME: InstructionBuilderRepository::GetInstructionBuilder 
////////////////////////////////
InstructionBuilder* InstructionBuilderRepository::GetInstructionBuilder(const OpCode opCode)
{
    InstructionBuilder* pInstructionBuilder = nullptr;

    LOG_INSTRUCTION("opCode = %d", opCode);

    switch(opCode)
    {
        case OpCode::ADD:
        case OpCode::SUB:
        case OpCode::BIC:
        case OpCode::AND:
        case OpCode::ORR:
        case OpCode::EOR:
        case OpCode::CMP:
        case OpCode::CMN:
        case OpCode::TEQ:
        case OpCode::TST:
        case OpCode::MOV:
        case OpCode::LSL:
        case OpCode::LSR:
            pInstructionBuilder = &f_arithAndLogicInstructionBuilder;
            break;
        case OpCode::B:
        case OpCode::BL:
        case OpCode::BX:
        case OpCode::BLX:
            pInstructionBuilder = &f_flowCtrlInstructionBuilder;
            break;
        case OpCode::PUSH:
        case OpCode::POP:
        case OpCode::LDM:
        case OpCode::STM:
        case OpCode::LDR:
        case OpCode::STR:
            pInstructionBuilder = &f_memoryInstructionBuilder;
            break;
        case OpCode::NOP:
            ASSERT(false, "Instruction should not be built for NOP");
            break;
        default:
            ASSERT(false, "Invalid opCode %d", opCode);
    }

    return pInstructionBuilder;
}