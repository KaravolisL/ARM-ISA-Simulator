/////////////////////////////////
/// @file MemoryApi.hpp
///
/// @brief API declarations for the memory subsystem
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef MEMORY_API_HPP
#define MEMORY_API_HPP

// SYSTEM INCLUDES
#include <stdint.h>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
// (None)

// FORWARD DECLARATIONS
// (None)

namespace Memory
{
namespace MemoryApi
{

////////////////////////////////
/// METHOD NAME: Memory::MemoryApi::Initialize
///
/// @brief Initializes the memory subsystem
////////////////////////////////
void Initialize();

////////////////////////////////
/// METHOD NAME: Memory::MemoryApi::ReadWord
///
/// @brief Reads a word from the given address
///
/// @param[in] address      Address from which to read
/// @return Word of data at that address
////////////////////////////////
uint32_t ReadWord(uint32_t address);

////////////////////////////////
/// METHOD NAME: Memory::MemoryApi::ReadUnsignedByte
///
/// @copydoc Memory::MemoryManager::ReadUnsignedByte
////////////////////////////////
uint32_t ReadUnsignedByte(uint32_t address);

////////////////////////////////
/// METHOD NAME: Memory::MemoryApi::ReadSignedByte
///
/// @copydoc Memory::MemoryManager::ReadSignedByte
////////////////////////////////
uint32_t ReadSignedByte(uint32_t address);

////////////////////////////////
/// METHOD NAME: Memory::MemoryApi::ReadUnsignedHalfword
///
/// @copydoc Memory::MemoryManager::ReadUnsignedHalfword
////////////////////////////////
uint32_t ReadUnsignedHalfword(uint32_t address);

////////////////////////////////
/// METHOD NAME: Memory::MemoryApi::ReadSignedHalfword
///
/// @copydoc Memory::MemoryManager::ReadSignedHalfword
////////////////////////////////
uint32_t ReadSignedHalfword(uint32_t address);

////////////////////////////////
/// METHOD NAME: Memory::MemoryApi::WriteWord
///
/// @brief Writes the given data to the given address.
/// overloaded to allow for different types of writes
///
/// @param[in] address      Address at which to write
/// @param[in] data         Data to write
////////////////////////////////
void WriteWord(uint32_t address, uint32_t data);

////////////////////////////////
/// METHOD NAME: Memory::MemoryApi::WriteUnsignedByte
///
/// @copydoc Memory::MemoryManager::WriteUnsignedByte
////////////////////////////////
void WriteUnsignedByte(uint32_t address, uint8_t data);

////////////////////////////////
/// METHOD NAME: Memory::MemoryApi::WriteUnsignedHalfword
///
/// @copydoc Memory::MemoryManager::WriteUnsignedHalfword
////////////////////////////////
void WriteUnsignedHalfword(uint32_t address, int16_t data);

} // MemoryApi

} // Memory

#endif