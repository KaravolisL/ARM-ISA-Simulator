/////////////////////////////////
/// @file MemoryManager.cpp
///
/// @brief Implementation of MemoryManager class
///
/// @copydetail MemoryManager
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "MemoryManager.hpp" // Header for class
#include "MemoryConstants.hpp" // For GLOBAL_LOWER_BOUND

namespace Memory
{

////////////////////////////////
/// METHOD NAME: Memory::MemoryManager::Initialize
////////////////////////////////
void MemoryManager::Initialize()
{
    uint32_t zero = 0;
    for (uint32_t i = GLOBAL_LOWER_BOUND; i <= GLOBAL_UPPER_BOUND; i += sizeof(uint32_t))
    {
        m_memoryFile.write(reinterpret_cast<char*>(&zero), sizeof(zero));
    }

    m_memoryFile.seekg(0, std::fstream::beg);

    LOG_INFO("MemoryManager Initialized");
}

////////////////////////////////
/// METHOD NAME: Memory::MemoryManager::GoToAddress
////////////////////////////////
void MemoryManager::GoToAddress(uint32_t address)
{
    ValidateAddress(address);

    m_memoryFile.seekg((address - GLOBAL_LOWER_BOUND), std::fstream::beg);
}

////////////////////////////////
/// METHOD NAME: Memory::MemoryManager::ValidateAddress
////////////////////////////////
void MemoryManager::ValidateAddress(uint32_t address)
{
    if (address < GLOBAL_LOWER_BOUND || address > GLOBAL_UPPER_BOUND)
    {
        LOG_ERROR("Address 0x%x is outside of bounds", address);
        throw MemoryException();
    }

    if (address % sizeof(uint32_t) != 0)
    {
        LOG_ERROR("Address 0x%x is not byte addressable", address);
        throw MemoryException();
    }
}

} // Memory