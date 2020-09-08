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
/// @copydoc Memory::MemoryManager::Initialize()
////////////////////////////////
void Initialize();

////////////////////////////////
/// @copydoc Memory::MemoryManager::Close()
////////////////////////////////
void Close();

////////////////////////////////
/// @copydoc Memory::MemoryManager::Read()
////////////////////////////////
uint32_t ReadWord(uint32_t address);

////////////////////////////////
/// @copydoc Memory::MemoryManager::Read()
////////////////////////////////
uint32_t ReadUnsignedByte(uint32_t address);

////////////////////////////////
/// @copydoc Memory::MemoryManager::Read()
////////////////////////////////
uint32_t ReadSignedByte(uint32_t address);

////////////////////////////////
/// @copydoc Memory::MemoryManager::Read()
////////////////////////////////
uint32_t ReadUnsignedHalfword(uint32_t address);

////////////////////////////////
/// @copydoc Memory::MemoryManager::Read()
////////////////////////////////
uint32_t ReadSignedHalfword(uint32_t address);

////////////////////////////////
/// @copydoc Memory::MemoryManager::Write()
////////////////////////////////
void WriteWord(uint32_t address, uint32_t data);

////////////////////////////////
/// @copydoc Memory::MemoryManager::Write()
////////////////////////////////
void WriteUnsignedByte(uint32_t address, uint8_t data);

////////////////////////////////
/// @copydoc Memory::MemoryManager::Write()
////////////////////////////////
void WriteUnsignedHalfword(uint32_t address, uint16_t data);

} // MemoryApi

} // Memory

#endif