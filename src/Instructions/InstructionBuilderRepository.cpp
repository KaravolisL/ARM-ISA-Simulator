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
#include "Logger.hpp" // For Logger
#include "Assert.hpp" // For ASSERT

static ArithAndLogicInstructionBuilder f_arithAndLogicInstructionBuilder;
// static FlowCtrlInstructionBuilder f_flowCtrlInstructionBuilder;
// static MemoryInstructionBuilder f_memoryInstructionBuilder;

////////////////////////////////
/// METHOD NAME: InstructionBuilderRepository::GetInstructionBuilder 
////////////////////////////////
InstructionBuilder* InstructionBuilderRepository::GetInstructionBuilder(const OpCode opCode)
{
    InstructionBuilder* pInstructionBuilder = nullptr;

    LOG_DEBUG("opCode = %d", opCode);

    switch(opCode)
    {
        case OpCode::ADD:
        case OpCode::SUB:
        case OpCode::BIC:
        case OpCode::AND:
        case OpCode::ORR:
        case OpCode::EOR:
            pInstructionBuilder = &f_arithAndLogicInstructionBuilder;
            break;

        default:
            ASSERT("Invalid opCode %d", opCode);
    }

    return pInstructionBuilder;
}