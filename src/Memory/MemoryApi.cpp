/////////////////////////////////
/// @file MemoryApi.cpp
///
/// @brief API implementations for the memory subsystem
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "MemoryApi.hpp" // Header for functions
#include "MemoryManager.hpp" // For Memory::MemoryManager

// FORWARD DECLARATIONS
// (None)

namespace Memory
{
namespace MemoryApi
{

static MemoryManager& memManager = MemoryManager::GetInstance();

////////////////////////////////
/// FUNCTION NAME: Memory::MemoryApi::Initialize
////////////////////////////////
void Initialize()
{
    memManager.Initialize();
}

////////////////////////////////
/// FUNCTION NAME: Memory::MemoryApi::ReadWord
////////////////////////////////
uint32_t ReadWord(uint32_t address)
{
    uint32_t data = memManager.ReadWord(address);
    return data;
}

////////////////////////////////
/// FUNCTION NAME: Memory::MemoryApi::ReadUnsignedByte
////////////////////////////////
uint32_t ReadUnsignedByte(uint32_t address)
{
    uint32_t data = memManager.ReadUnsignedByte(address);
    return data;
}

////////////////////////////////
/// FUNCTION NAME: Memory::MemoryApi::ReadSignedByte
////////////////////////////////
uint32_t ReadSignedByte(uint32_t address)
{
    uint32_t data = memManager.ReadSignedByte(address);
    return data;
}

////////////////////////////////
/// FUNCTION NAME: Memory::MemoryApi::ReadHalfWord
////////////////////////////////
uint16_t ReadHalfWord(uint32_t address)
{
    // TODO
    return 0;
}

////////////////////////////////
/// FUNCTION NAME: Memory::MemoryApi::WriteWord
////////////////////////////////
void WriteWord(uint32_t address, uint32_t data)
{
    memManager.WriteWord(address, data);
}

////////////////////////////////
/// FUNCTION NAME: Memory::MemoryApi::WriteUnsignedByte
////////////////////////////////
void WriteUnsignedByte(uint32_t address, uint8_t data)
{
    memManager.WriteUnsignedByte(address, data);
}

////////////////////////////////
/// FUNCTION NAME: Memory::MemoryApi::WriteHalfWord
////////////////////////////////
void WriteHalfWord(uint32_t address, uint16_t data)
{
    // TODO
}

} // MemoryApi

} // Memory