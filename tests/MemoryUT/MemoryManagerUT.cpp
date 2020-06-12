/////////////////////////////////
/// @file MemoryManagerUT.cpp
///
/// @brief Unit Test for MemoryManager
///
/// @author <Author Name>
/////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "MemoryManager.hpp"  // Test class

////////////////////////////////
/// Test Objects
////////////////////////////////
Memory::MemoryManager& memManager = Memory::MemoryManager::GetInstance();
uint32_t address = 0x20000000;

////////////////////////////////
/// Setup Function
////////////////////////////////
void setup()
{
    memManager.Initialize();
}

////////////////////////////////
/// WriteTest Function
////////////////////////////////
void WriteTest()
{
    memManager.WriteWord(0x2000013c, 8362);
    
    memManager.WriteWord(0x20000000, 111);

    memManager.WriteWord(0x20004000, 0xFFFFFFFF);

    try
    {
        memManager.WriteWord(0x50000000, 123);
        assert(false);
    }
    catch(const Memory::MemoryManager::MemoryException& e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        memManager.WriteWord(0x20001002, 8);
        assert(false);
    }
    catch(const Memory::MemoryManager::MemoryException& e)
    {
        std::cerr << e.what() << '\n';
    }
}

////////////////////////////////
/// ReadTest Function
////////////////////////////////
void ReadTest()
{
    uint32_t data;

    data = memManager.ReadWord(0x2000013c);
    assert(data == 8362);

    data = memManager.ReadWord(0x20000000);
    assert(data == 111);

    data = memManager.ReadWord(0x20004000);
    assert(data == 0xFFFFFFFF);
}

////////////////////////////////
/// UnsignedByteTest Function
////////////////////////////////
void UnsignedByteTest()
{
    uint32_t data;

    memManager.WriteWord(address, 0xFFFF);
    memManager.WriteUnsignedByte(address, 0x55);

    data = memManager.ReadWord(address);
    assert(data == 0x0000FF55);

    memManager.WriteUnsignedByte(address, 0x1);
    
    data = memManager.ReadWord(address);
    assert(data == 0x0000FF01);

    data = memManager.ReadUnsignedByte(address);
    assert(data == 0x00000001);
}


////////////////////////////////
/// Teardown Function
////////////////////////////////
void teardown()
{

}

////////////////////////////////
/// Main Function
////////////////////////////////
int main(int argc, char* argv[])
{
    setup();

    WriteTest();
    ReadTest();

    UnsignedByteTest();

    teardown();

    std::cout << "MemoryManager Unit Test Complete: SUCCESS";
    return 0;
}