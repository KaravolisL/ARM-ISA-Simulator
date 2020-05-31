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

        // N and Z flags will be set the same way for all instructions
        (result & 0x80000000) != 0 ? rProcessRegisters.SetNegativeFlag() : rProcessRegisters.ClearNegativeFlag();
        result == 0 ? rProcessRegisters.SetZeroFlag() : rProcessRegisters.ClearZeroFlag();

        // Individual instructions handle the C and V flags differently
        switch (m_opCode)
        {
            case OpCode::ADD:
            case OpCode::CMN:
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
                break;
            case OpCode::SUB:
            case OpCode::CMP:
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
                break;
            case OpCode::LSL:
            {
                // C flag will be equal to the last bit shifted out
                static const int BITS_IN_REGISTER = 32;
                uint8_t lastBit = (m_argument1 >> (BITS_IN_REGISTER - m_argument2)) & 0x1;
                if (lastBit) rProcessRegisters.SetCarryFlag();
                break;
            }
            default:
                LOG_DEBUG("No additional flag operations for opcode %d", m_opCode);
        }
    }
}