/////////////////////////////////
/// @file MemoryManagerUT.cpp
///
/// @brief Unit Test for MemoryManager
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include <catch2/catch.hpp>
#include "MemoryConstants.hpp"
#include "MemoryManager.hpp"  // Test class

TEMPLATE_TEST_CASE("Memory Manager General Functionality", "[MemoryManager]", uint32_t, int32_t, uint16_t,
                                                                              int16_t, uint8_t, int8_t)
{
    Memory::MemoryManager& memManager = Memory::MemoryManager::GetInstance();

    uint32_t address = GENERATE(take(5, random(Memory::GLOBAL_LOWER_BOUND, Memory::GLOBAL_UPPER_BOUND)));

    SECTION("Write and read back")
    {
        TestType data = GENERATE(take(5, random(INT32_MIN, INT32_MAX)));

        memManager.Write<TestType>(address, data);
        TestType readData = memManager.Read<TestType>(address);

    	REQUIRE(data == readData);
    }
}

TEST_CASE("Memory Manager Specific Functionality")
{
    Memory::MemoryManager& memManager = Memory::MemoryManager::GetInstance();

    SECTION("Memory exceptions")
    {
        REQUIRE_THROWS_AS(memManager.Write<uint32_t>(0, 0), Memory::MemoryManager::MemoryException);
    }

    SECTION("Manipulate same word")
    {
        uint32_t const address = Memory::GLOBAL_LOWER_BOUND;

        memManager.Write<uint32_t>(address, 0x12345678);
        uint32_t readWord = memManager.Read<uint32_t>(address);
    	REQUIRE(readWord == 0x12345678);

        memManager.Write<uint8_t>(address, 0xFF);
        readWord = memManager.Read<uint32_t>(address);
        REQUIRE(readWord == 0x123456FF);

        uint8_t readByte = memManager.Read<uint8_t>(address);
        REQUIRE(readByte == 0xFF);
        readByte = memManager.Read<uint8_t>(address + 1);
        REQUIRE(readByte == 0x56);
        readByte = memManager.Read<uint8_t>(address + 2);
        REQUIRE(readByte == 0x34);
        readByte = memManager.Read<uint8_t>(address + 3);
        REQUIRE(readByte == 0x12);

        memManager.Write<uint16_t>(address + 4, 0xABCD);
        uint16_t readHalfword = memManager.Read<uint16_t>(address + 4);
        REQUIRE(readHalfword == 0xABCD);

        readHalfword = memManager.Read<uint16_t>(address);
        REQUIRE(readHalfword == 0x56FF);
        readHalfword = memManager.Read<uint16_t>(address + 1);
        REQUIRE(readHalfword == 0x3456);
        readHalfword = memManager.Read<uint16_t>(address + 2);
        REQUIRE(readHalfword == 0x1234);
        readHalfword = memManager.Read<uint16_t>(address + 3);
        REQUIRE(readHalfword == 0xCD12);

        readWord = memManager.Read<uint32_t>(address + 2);
        REQUIRE(readWord == 0xABCD1234);
    }
}
