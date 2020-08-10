/////////////////////////////////
/// @file MultipleMemoryInstruction.cpp
///
/// @brief Implementation of MultipleMemoryInstruction class
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "MultipleMemoryInstruction.hpp" // Header for class
#include "MemoryApi.hpp" // For MemoryApi
#include "Logger.hpp"
#include "Assert.hpp"

////////////////////////////////
/// METHOD NAME: MultipleMemoryInstruction::Execute
////////////////////////////////
void MultipleMemoryInstruction::Execute(Registers& rProcessRegisters)
{   
    // If we're not updating the address register, modify a temporary register
    Register addressPlaceholder;
    if (!m_updateFlag)
    {
        addressPlaceholder = *m_pAddressRegister;
        m_pAddressRegister = &addressPlaceholder;
    }

    // For every register in the list...
    for (uint8_t i = 0; i < m_registerList.GetLength(); i++)
    {
        // Handle IB and DB
        if (m_addressingMode == AddressingMode::IB)
        {
            (*m_pAddressRegister) += sizeof(uint32_t);
        }
        else if ( m_addressingMode == AddressingMode:: DB)
        {
            (*m_pAddressRegister) -= sizeof(uint32_t);
        }

        switch (m_opCode)
        {
        case OpCode::PUSH:
        case OpCode::STM:
            Memory::MemoryApi::WriteWord((*m_pAddressRegister), *(m_registerList[i]));
            break;
        case OpCode::POP:
        case OpCode::LDM:
            *(m_registerList[i]) = Memory::MemoryApi::ReadWord((*m_pAddressRegister));
            break;
        default:
            ASSERT(false, "Invalid opcode %d", m_opCode);
            break;
        }

        // Handle IA and DA
        if (m_addressingMode == AddressingMode::IA)
        {
            (*m_pAddressRegister) += sizeof(uint32_t);
        }
        else if ( m_addressingMode == AddressingMode:: DA)
        {
            (*m_pAddressRegister) -= sizeof(uint32_t);
        }
    }
}