/////////////////////////////////
/// @file AddUT.cpp
///
/// @brief Unit Test for ADD Instruction
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

TEST_CASE("ADD Instruction", "[instruction][ArithAndLogic]")
{
    Process myProc = Process();
    InstructionBuilder& builder = InstructionBuilder::GetInstance();
    InstructionBase* pInstruction = nullptr;

    for (int i = 0; i < 13; i++)
    {
        myProc.GetProcessRegisters().genRegs[i] = i;
    }

    SECTION("Add registers")
    {
        std::string instructionStr = "ADD R0, R1, R2";
        int a = GENERATE(take(5, random(INT32_MIN, INT32_MAX)));
        int b = GENERATE(take(5, random(INT32_MIN, INT32_MAX)));

        myProc.GetProcessRegisters().genRegs[1] = a;
        myProc.GetProcessRegisters().genRegs[2] = b;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[0] == static_cast<uint32_t>((a + b)));
        delete pInstruction;
    }

    SECTION("Add to a register")
    {
        std::string instructionStr = "ADD R0, R1";
        int a = GENERATE(take(5, random(INT32_MIN, INT32_MAX)));
        int b = GENERATE(take(5, random(INT32_MIN, INT32_MAX)));

        myProc.GetProcessRegisters().genRegs[0] = a;
        myProc.GetProcessRegisters().genRegs[1] = b;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[0] == static_cast<uint32_t>((a + b)));
        delete pInstruction;
    }

    SECTION("Add literal with a register")
    {
        int literal = GENERATE(take(5, random(INT32_MIN, INT32_MAX)));
        std::string baseInstructionStr = "ADD R0, R1, #";
        std::string instructionStr = baseInstructionStr + std::to_string(literal);
        myProc.GetProcessRegisters().genRegs[1] = 1;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[0] == static_cast<uint32_t>(1 + literal));
        delete pInstruction;
    }

    SECTION("Add literal to a register")
    {
        int literal = GENERATE(take(5, random(INT32_MIN, INT32_MAX)));
        std::string baseInstructionStr = "ADD R1, #";
        std::string instructionStr = baseInstructionStr + std::to_string(literal);
        myProc.GetProcessRegisters().genRegs[1] = 1;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[1] == static_cast<uint32_t>(1 + literal));
        delete pInstruction;
    }

    SECTION("ADDS test")
    {
        std::string instructionStr = "ADDS R0, R0";

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().GetZeroFlag());
        REQUIRE(!myProc.GetProcessRegisters().GetNegativeFlag());
        REQUIRE(!myProc.GetProcessRegisters().GetCarryFlag());
        REQUIRE(!myProc.GetProcessRegisters().GetOverflowFlag());
        delete pInstruction;

        instructionStr = "ADDS R0, #-2";

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(!myProc.GetProcessRegisters().GetZeroFlag());
        REQUIRE(myProc.GetProcessRegisters().GetNegativeFlag());
        REQUIRE(!myProc.GetProcessRegisters().GetCarryFlag());
        REQUIRE(!myProc.GetProcessRegisters().GetOverflowFlag());
        delete pInstruction;

        instructionStr = "ADDS R10, #0xFFFFFFFF";

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(!myProc.GetProcessRegisters().GetZeroFlag());
        REQUIRE(!myProc.GetProcessRegisters().GetNegativeFlag());
        REQUIRE(myProc.GetProcessRegisters().GetCarryFlag());
        REQUIRE(!myProc.GetProcessRegisters().GetOverflowFlag());
        delete pInstruction;

        // "MOV" R1, #0x40000000
        myProc.GetProcessRegisters().genRegs[1] = 0x40000000;

        instructionStr = "ADDS R1, #0x40000000";

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(!myProc.GetProcessRegisters().GetZeroFlag());
        REQUIRE(myProc.GetProcessRegisters().GetNegativeFlag());
        REQUIRE(!myProc.GetProcessRegisters().GetCarryFlag());
        REQUIRE(myProc.GetProcessRegisters().GetOverflowFlag());
        delete pInstruction;
    }
}
