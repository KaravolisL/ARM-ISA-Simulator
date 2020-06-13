/////////////////////////////////
/// @file MemoryInstruction.cpp
///
/// @brief Implementation of MemoryInstruction class
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "MemoryInstruction.hpp" // Header for class
#include "MemoryApi.hpp" // For MemoryApi
#include "Logger.hpp"
#include "Assert.hpp"

////////////////////////////////
/// METHOD NAME: MemoryInstruction::Execute
////////////////////////////////
void MemoryInstruction::Execute(Registers& rProcessRegisters)
{   
    ASSERT(m_pAddressRegister != nullptr);
    ASSERT(m_pDestOrSrcRegister != nullptr);

    // If we're not updating the address register, modify a temporary register
    Register addressPlaceholder;
    if (m_offsetType == OffsetType::ZERO || m_offsetType == OffsetType::PREINDEXED)
    {
        addressPlaceholder = *m_pAddressRegister;
        m_pAddressRegister = &addressPlaceholder;
    }

    if (m_offsetType == OffsetType::PREINDEXED || m_offsetType == OffsetType::PREINDEXED_WITH_UPDATE)
    {
        *m_pAddressRegister += m_offset;
    }

    if (m_opCode == OpCode::STR)
    {
        switch (m_transferType)
        {
            case MemoryTransferType::WORD:
                Memory::MemoryApi::WriteWord(*m_pAddressRegister, *m_pDestOrSrcRegister);
                break;
            case MemoryTransferType::UNSIGNED_BYTE:
                Memory::MemoryApi::WriteUnsignedByte(*m_pAddressRegister, static_cast<uint8_t>(*m_pDestOrSrcRegister));
                break;
            case MemoryTransferType::UNSIGNED_HALFWORD:
                // Memory::MemoryApi::WriteUnsignedHalfWord(*m_pAddressRegister, static_cast<uint16_t>(*m_pDestOrSrcRegister));
                break;
            case MemoryTransferType::SIGNED_HALFWORD:
            case MemoryTransferType::SIGNED_BYTE:
            default:
                ASSERT(false, "Invalid transfer type %d", m_transferType);
        }
    }
    else
    {
        switch (m_transferType)
        {
            case MemoryTransferType::WORD:
                *m_pDestOrSrcRegister = Memory::MemoryApi::ReadWord(*m_pAddressRegister);
                break;
            case MemoryTransferType::UNSIGNED_BYTE:
                *m_pDestOrSrcRegister = Memory::MemoryApi::ReadUnsignedByte(*m_pAddressRegister);
                break;
            case MemoryTransferType::SIGNED_BYTE:
                *m_pDestOrSrcRegister = Memory::MemoryApi::ReadSignedByte(*m_pAddressRegister);
                break;
            case MemoryTransferType::UNSIGNED_HALFWORD:
                break;
            case MemoryTransferType::SIGNED_HALFWORD:
                break;
            default:
                ASSERT(false, "Invalid transfer type %d", m_transferType);
        }
    }

    if (m_offsetType == OffsetType::POSTINDEXED)
    {
        *m_pAddressRegister += m_offset;
    }
}