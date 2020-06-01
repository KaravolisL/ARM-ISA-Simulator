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
#include <iomanip>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "MemoryManager.hpp" // Header for class
#include "MemoryConstants.hpp" // For GLOBAL_LOWER_BOUND
#include "Logger.hpp" // For LOG_INFO

namespace Memory
{

////////////////////////////////
/// METHOD NAME: Memory::MemoryManager::Initialize
////////////////////////////////
void MemoryManager::Initialize()
{
    for (uint32_t i = GLOBAL_LOWER_BOUND; i <= GLOBAL_UPPER_BOUND; i += sizeof(uint32_t))
    {
        // Memory address at the beginning of each line
        if (i % (WORDS_PER_ROW*sizeof(uint32_t)) == 0)
        {
            m_memoryFile << "0x" << std::hex << i << ": ";
        }

        m_memoryFile << std::setfill('0') << std::setw(8) << std::hex << 0 << ' ';

        // Max of 16 words per row
        if (i % (WORDS_PER_ROW*sizeof(uint32_t)) == 0x3c)
        {
            m_memoryFile << '\n';
        }
    }

    // Seek to GLOBAL_LOWER_BOUND. Account for 0x and :_ at each end of the address 
    m_memoryFile.seekg(0, std::fstream::beg);

    LOG_INFO("MemoryManager Initialized");
}

////////////////////////////////
/// METHOD NAME: Memory::MemoryManager::GoToAddress
////////////////////////////////
void MemoryManager::GoToAddress(uint32_t address)
{
    ValidateAddress(address);

    // lineNumber is zero indexed
    uint32_t lineNumber = ((address - GLOBAL_LOWER_BOUND)/(0x40));
    uint32_t offset = (((address - GLOBAL_LOWER_BOUND) % (0x40))/sizeof(uint32_t));

    LOG_DEBUG("LineNumber = %d, offset = %d", lineNumber, offset);

    // Seek to the line first
    m_memoryFile.seekg(lineNumber * CHARACTERS_PER_LINE, std::fstream::beg);

    // Seek past address label
    m_memoryFile.seekg(2 + CHARACTERS_PER_WORD + 2, std::fstream::cur);

    // Seek to the given address using the offset
    m_memoryFile.seekg((offset * (CHARACTERS_PER_WORD + 1)), std::fstream::cur);
}

////////////////////////////////
/// METHOD NAME: Memory::MemoryManager::ReadWord
////////////////////////////////
uint32_t MemoryManager::ReadWord(uint32_t address)
{
    GoToAddress(address);

    char buffer[CHARACTERS_PER_WORD + 1];

    m_memoryFile.read(buffer, CHARACTERS_PER_WORD);
    buffer[CHARACTERS_PER_WORD] = '\0';

    LOG_DEBUG("Read %s from the address %d", buffer, address);

    uint32_t data = std::stoul(buffer, nullptr, 16);
    return data;
}

////////////////////////////////
/// METHOD NAME: Memory::MemoryManager::WriteWord
////////////////////////////////
void MemoryManager::WriteWord(uint32_t address, uint32_t data)
{
    GoToAddress(address);

    LOG_DEBUG("Writing %d to the address %d", data, address);

    m_memoryFile << std::setfill('0') << std::setw(8) << std::hex << data;
}

////////////////////////////////
/// METHOD NAME: Memory::MemoryManager::ValidateAddress
////////////////////////////////
void MemoryManager::ValidateAddress(uint32_t address)
{
    if (address < GLOBAL_LOWER_BOUND || address > GLOBAL_UPPER_BOUND)
    {
        LOG_ERROR("Address %d is outside of bounds", address);
        throw MemoryException();
    }

    if (address % sizeof(uint32_t) != 0)
    {
        LOG_ERROR("Address %d is not byte addressable", address);
        throw MemoryException();
    }
}

} // Memory