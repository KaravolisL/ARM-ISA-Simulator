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
void ArithAndLogicInstruction::Execute(Registers& rProcessRegisters)
{
    ASSERT(m_pOperation != nullptr);

    LOG_DEBUG("Argument 1: %d", m_argument1);
    LOG_DEBUG("Argument 2: %d", m_argument2);

    Register result = m_pOperation(m_argument1, m_argument2);

    *m_pDestination = result;

    LOG_DEBUG("Result = %d", result);

    // Set flags if necessary
    if (m_sFlag)
    {
        LOG_DEBUG("Setting flags");
        (result & 0x80000000) != 0 ? rProcessRegisters.SetNegativeFlag() : rProcessRegisters.ClearNegativeFlag();
        result == 0 ? rProcessRegisters.SetZeroFlag() : rProcessRegisters.ClearZeroFlag();

        // Only subtraction and addition instructions should mess with the C and V flags
        if (m_opCode == OpCode::ADD)
            {
            // Overflow can only occur if the numbers are the same sign
            if ((m_argument1 & 0x80000000) == (m_argument2 & 0x80000000))
            {
                // Overflow occurs if the sign of the arguments differ from the sum's sign
                if ((m_argument1 & 0x80000000) != (result & 0x80000000))
                {
                    rProcessRegisters.SetOverflowFlag();
                }
                else
                {
                    rProcessRegisters.ClearOverflowFlag();
                }
            }

            if (result < m_argument1 || result < m_argument2)
            {
                rProcessRegisters.SetCarryFlag();
            }
            else
            {
                rProcessRegisters.ClearCarryFlag();
            }
        }
        else if (m_opCode == OpCode::SUB)
        {
            // Overflow can only occur if the numbers are different signs
            if ((m_argument1 & 0x80000000) != (m_argument2 & 0x80000000))
            {
                // Overflow occurs if the sign of the second argument is the same as the result
                if ((m_argument2 & 0x80000000) == (result & 0x80000000))
                {
                    rProcessRegisters.SetOverflowFlag();
                }
                else
                {
                    rProcessRegisters.ClearOverflowFlag();
                }
            }

            if (result > m_argument1 || result > m_argument2)
            {
                // Clearing flag indicates a borrow occured
                rProcessRegisters.ClearCarryFlag();
            }
            else
            {
                rProcessRegisters.SetCarryFlag();
            }
        }
    }
}