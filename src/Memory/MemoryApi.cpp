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
/// FUNCTION NAME: Memory::MemoryApi::Close
////////////////////////////////
void Close()
{
    memManager.Close();
}

////////////////////////////////
/// FUNCTION NAME: Memory::MemoryApi::ReadWord
////////////////////////////////
uint32_t ReadWord(uint32_t address)
{
    uint32_t data = memManager.Read<uint32_t>(address);
    return data;
}

////////////////////////////////
/// FUNCTION NAME: Memory::MemoryApi::ReadUnsignedByte
////////////////////////////////
uint32_t ReadUnsignedByte(uint32_t address)
{
    uint32_t data = memManager.Read<uint8_t>(address);
    return data;
}

////////////////////////////////
/// FUNCTION NAME: Memory::MemoryApi::ReadSignedByte
////////////////////////////////
uint32_t ReadSignedByte(uint32_t address)
{
    uint32_t data = memManager.Read<int8_t>(address);
    return data;
}

////////////////////////////////
/// FUNCTION NAME: Memory::MemoryApi::ReadUnsignedHalfword
////////////////////////////////
uint32_t ReadUnsignedHalfword(uint32_t address)
{
    uint32_t data = memManager.Read<uint16_t>(address);
    return data;
}

////////////////////////////////
/// FUNCTION NAME: Memory::MemoryApi::ReadSignedHalfword
////////////////////////////////
uint32_t ReadSignedHalfword(uint32_t address)
{
    uint32_t data = memManager.Read<int16_t>(address);
    return data;
}

////////////////////////////////
/// FUNCTION NAME: Memory::MemoryApi::WriteWord
////////////////////////////////
void WriteWord(uint32_t address, uint32_t data)
{
    memManager.Write<uint32_t>(address, data);
}

////////////////////////////////
/// FUNCTION NAME: Memory::MemoryApi::WriteUnsignedByte
////////////////////////////////
void WriteUnsignedByte(uint32_t address, uint8_t data)
{
    memManager.Write<uint8_t>(address, data);
}

////////////////////////////////
/// FUNCTION NAME: Memory::MemoryApi::WriteUnsignedHalfword
////////////////////////////////
void WriteUnsignedHalfword(uint32_t address, uint16_t data)
{
    memManager.Write<uint16_t>(address, data);
}

} // MemoryApi

} // Memory