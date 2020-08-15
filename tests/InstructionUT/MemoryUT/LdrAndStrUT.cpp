/////////////////////////////////
/// @file LdrAndStrUT.cpp
///
/// @brief Unit Test for STR and LDR Instructions
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include <catch2/catch.hpp>
#include "Process.hpp"
#include "InstructionBuilder.hpp"
#include "InstructionBase.hpp"
#include "MemoryApi.hpp"
#include "MemoryConstants.hpp"

TEST_CASE("LDR and STR Instructions", "[instruction][Memory]")
{
    Process myProc = Process();
    InstructionBuilder& builder = InstructionBuilder::GetInstance();
    InstructionBase* pInstruction = nullptr;
    std::string instructionStr;
    const uint32_t memAddress = 0x20000000;

    myProc.GetLabelDictionary().Insert("str", memAddress);
    myProc.GetProcessRegisters().genRegs[0] = memAddress;


    SECTION("STR Instruction")
    {
        uint32_t a = GENERATE(take(5, random(INT32_MIN, INT32_MAX)));
        myProc.GetProcessRegisters().genRegs[2] = a;

        SECTION("Regular Store")
        {
            instructionStr = "STR R2, [R0]";

            pInstruction = builder.BuildInstruction(instructionStr, &myProc);
            pInstruction->Execute(myProc.GetProcessRegisters());
            REQUIRE(Memory::MemoryApi::ReadWord(memAddress) == a);
            delete pInstruction;
        }

        SECTION("Pre-indexing no update store")
        {
            instructionStr = "STR R2, [R0, #4]";

            pInstruction = builder.BuildInstruction(instructionStr, &myProc);
            pInstruction->Execute(myProc.GetProcessRegisters());
            REQUIRE(Memory::MemoryApi::ReadWord(memAddress + 4) == a);
            REQUIRE(myProc.GetProcessRegisters().genRegs[0] == memAddress);
            delete pInstruction;
        }

        SECTION("Pre-indexing with update store")
        {
            instructionStr = "STR R2, [R0, #8]!";

            pInstruction = builder.BuildInstruction(instructionStr, &myProc);
            pInstruction->Execute(myProc.GetProcessRegisters());
            REQUIRE(Memory::MemoryApi::ReadWord(memAddress + 8) == a);
            REQUIRE(myProc.GetProcessRegisters().genRegs[0] == memAddress + 8);
            delete pInstruction;
        }

        SECTION("Post-indexing store")
        {
            myProc.GetProcessRegisters().genRegs[0] = memAddress + 12;
            instructionStr = "STR R2, [R0], #4";

            pInstruction = builder.BuildInstruction(instructionStr, &myProc);
            pInstruction->Execute(myProc.GetProcessRegisters());
            REQUIRE(Memory::MemoryApi::ReadWord(memAddress + 12) == a);
            REQUIRE(myProc.GetProcessRegisters().genRegs[0] == memAddress + 16);
            delete pInstruction;
        }
    }

    SECTION("LDR Instruction")
    {
        uint32_t a = GENERATE(take(5, random(INT32_MIN, INT32_MAX)));
        for (uint32_t i = memAddress; i < memAddress + 20; i += 4)
        {
            Memory::MemoryApi::WriteWord(i, a + (i - memAddress));
        }

        SECTION("Load constant")
        {
            instructionStr = "LDR R2, =str";

            pInstruction = builder.BuildInstruction(instructionStr, &myProc);
            pInstruction->Execute(myProc.GetProcessRegisters());
            REQUIRE(myProc.GetProcessRegisters().genRegs[2] == memAddress);
            delete pInstruction;
        }

        SECTION("Load from register")
        {
            instructionStr = "LDR R6, [R0]";

            pInstruction = builder.BuildInstruction(instructionStr, &myProc);
            pInstruction->Execute(myProc.GetProcessRegisters());
            REQUIRE(myProc.GetProcessRegisters().genRegs[6] == a);
            REQUIRE(myProc.GetProcessRegisters().genRegs[0] == memAddress);
            delete pInstruction;
        }

        SECTION("Pre-indexing with no update load")
        {
            instructionStr = "LDR R3, [R0, #4]";

            pInstruction = builder.BuildInstruction(instructionStr, &myProc);
            pInstruction->Execute(myProc.GetProcessRegisters());
            REQUIRE(myProc.GetProcessRegisters().genRegs[3] == (a + 4));
            REQUIRE(myProc.GetProcessRegisters().genRegs[0] == memAddress);
            delete pInstruction;
        }

        SECTION("Pre-indexing with update load")
        {
            instructionStr = "LDR R4, [R0, #8]!";

            pInstruction = builder.BuildInstruction(instructionStr, &myProc);
            pInstruction->Execute(myProc.GetProcessRegisters());
            REQUIRE(myProc.GetProcessRegisters().genRegs[4] == (a + 8));
            REQUIRE(myProc.GetProcessRegisters().genRegs[0] == memAddress + 8);
            delete pInstruction;
        }

        SECTION("Post-indexing load")
        {
            myProc.GetProcessRegisters().genRegs[0] = memAddress + 12;
            instructionStr = "LDR R5, [R0], #4";

            pInstruction = builder.BuildInstruction(instructionStr, &myProc);
            pInstruction->Execute(myProc.GetProcessRegisters());
            REQUIRE(myProc.GetProcessRegisters().genRegs[5] == (a + 12));
            REQUIRE(myProc.GetProcessRegisters().genRegs[0] == memAddress + 16);
            delete pInstruction;
        }
    }
}
