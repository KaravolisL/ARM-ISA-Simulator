/////////////////////////////////
/// @file ArithAndLogicInstruction.cpp
///
/// @brief Implementation of ArithAndLogicInstruction class
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "ArithAndLogicInstruction.hpp" // Header for class
#include "Logger.hpp"
#include "Assert.hpp"

////////////////////////////////
/// METHOD NAME: ArithAndLogicInstruction::Execute
////////////////////////////////
void ArithAndLogicInstruction::Execute()
{
    ASSERT(m_pOperation != nullptr);

    LOG_DEBUG("Argument 1: %d", m_argument1);
    LOG_DEBUG("Argument 2: %d", m_argument2);

    Register result = m_pOperation(m_argument1, m_argument2);

    *m_pDestination = result;

    LOG_DEBUG("Result = %d", result);

    // TODO: Set flags if the instruction is flagged
}