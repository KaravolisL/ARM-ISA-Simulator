/////////////////////////////////
/// @file LdmAndStmUT.cpp
///
/// @brief Unit Test for STM and LDM Instructions
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

TEST_CASE("LDM and STM Instructions", "[instruction][Memory]")
{
    Process myProc = Process();
    InstructionBuilder& builder = InstructionBuilder::GetInstance();
    InstructionBase* pInstruction = nullptr;
    std::string instructionStr;
    const uint32_t memAddress = 0x20000000;

    for (int i = 0; i < 13; i++)
    {
        myProc.GetProcessRegisters().genRegs[i] = i;
    }

    myProc.GetProcessRegisters().SP = Memory::STACK_LOWER_BOUND;

    SECTION("Push and Pop like instructions")
    {
        instructionStr = "STMDB SP! {R0, R2}";

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(Memory::MemoryApi::ReadWord(myProc.GetProcessRegisters().SP) == 2);
        delete pInstruction;

        instructionStr = "LDM SP! {R1, R3}";

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[1] == 0);
        REQUIRE(myProc.GetProcessRegisters().genRegs[3] == 2);
        delete pInstruction;
    }

    SECTION("IB and DA")
    {
        instructionStr = "STMIB R5, {R1, R6-R9}";

        myProc.GetProcessRegisters().genRegs[5] = memAddress;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(Memory::MemoryApi::ReadWord(memAddress + 4) == 1);
        REQUIRE(Memory::MemoryApi::ReadWord(memAddress + 8) == 6);
        REQUIRE(Memory::MemoryApi::ReadWord(memAddress + 12) == 7);
        REQUIRE(Memory::MemoryApi::ReadWord(memAddress + 16) == 8);
        REQUIRE(Memory::MemoryApi::ReadWord(memAddress + 20) == 9);
        REQUIRE(myProc.GetProcessRegisters().genRegs[5] == memAddress);
        delete pInstruction;

        myProc.GetProcessRegisters().genRegs[5] = memAddress + sizeof(uint32_t) * 5;

        instructionStr = "LDMDA R5! {R2, R7-R10}";

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[2] == 1);
        REQUIRE(myProc.GetProcessRegisters().genRegs[7] == 6);
        REQUIRE(myProc.GetProcessRegisters().genRegs[8] == 7);
        REQUIRE(myProc.GetProcessRegisters().genRegs[9] == 8);
        REQUIRE(myProc.GetProcessRegisters().genRegs[10] == 9);
        delete pInstruction;

        REQUIRE(myProc.GetProcessRegisters().genRegs[5] == memAddress);
    }
}
