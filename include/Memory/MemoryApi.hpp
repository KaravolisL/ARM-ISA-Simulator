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
/// METHOD NAME: Memory::MemoryApi::ReadHalfWord
///
/// @brief Reads a halfword from the given address
///
/// @param[in] address      Address from which to read
/// @return Halfword of data at that address
////////////////////////////////
uint16_t ReadHalfWord(uint32_t address);

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
/// METHOD NAME: Memory::MemoryApi::Write
///
/// @copydoc Memory::MemoryManager::WriteByte
////////////////////////////////
void WriteByte(uint32_t address, int8_t data);

////////////////////////////////
/// METHOD NAME: Memory::MemoryApi::WriteHalfWord
///
/// @brief Writes a halfword to the given address
///
/// @param[in] address      Address at which to write
/// @param[in] data         Data to write
////////////////////////////////
void WriteHalfWord(uint32_t address, uint16_t data);

} // MemoryApi

} // Memory

#endif