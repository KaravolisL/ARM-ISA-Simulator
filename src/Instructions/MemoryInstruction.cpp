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
    if (m_opCode == OpCode::STR)
    {
        Memory::MemoryApi::WriteWord(*m_pAddressRegister, *m_pDestOrSrcRegister);
    }
    else
    {
        *m_pDestOrSrcRegister = Memory::MemoryApi::ReadWord(*m_pAddressRegister);
    }
}