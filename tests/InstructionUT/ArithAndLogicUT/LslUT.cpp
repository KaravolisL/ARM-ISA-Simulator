/////////////////////////////////
/// @file LslUT.cpp
///
/// @brief Unit Test for LSL Instruction
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include <catch2/catch.hpp>
#include "InstructionBase.hpp"
#include "InstructionBuilder.hpp"
#include "Process.hpp"

TEST_CASE("LSL Instruction", "[instruction][ArithAndLogic]")
{
    Process myProc = Process();
    InstructionBuilder& builder = InstructionBuilder::GetInstance();
    InstructionBase* pInstruction = nullptr;
    std::string instructionStr;

    uint32_t a = GENERATE(take(5, random(INT32_MIN, INT32_MAX)));
    uint32_t b = GENERATE(take(5, random(0, 32)));

    SECTION("Shift register by another register")
    {
        instructionStr = "LSL R0, R1, R2";

        myProc.GetProcessRegisters().genRegs[1] = a;
        myProc.GetProcessRegisters().genRegs[2] = b;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[0] == (a << b));
        delete pInstruction;
    }

    SECTION("Shift register with another register")
    {
        instructionStr = "LSL R2, R3";

        myProc.GetProcessRegisters().genRegs[2] = a;
        myProc.GetProcessRegisters().genRegs[3] = b;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[2] == (a << b));
        delete pInstruction;
    }

    SECTION("Shift register by literal")
    {
        instructionStr = "LSL R0, R1, #" + std::to_string(b);

        myProc.GetProcessRegisters().genRegs[1] = a;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[0] == (a << b));
        delete pInstruction;
    }

    SECTION("Shift register with literal")
    {
        instructionStr = "LSL R0, #" + std::to_string(b);

        myProc.GetProcessRegisters().genRegs[0] = a;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[0] == (a << b));
        delete pInstruction;
    }

    SECTION("LSLS Test")
    {
        myProc.GetProcessRegisters().genRegs[0] = 0;
        myProc.GetProcessRegisters().genRegs[1] = 1;

        instructionStr = "LSLS R0, R1";

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().GetZeroFlag());
        REQUIRE(!myProc.GetProcessRegisters().GetNegativeFlag());
        REQUIRE(!myProc.GetProcessRegisters().GetCarryFlag());
        delete pInstruction;

        // "MOV" R2, #0x40000000
        myProc.GetProcessRegisters().genRegs[2] = 0xC0000000;

        instructionStr = "LSLS R2, #1";

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(!myProc.GetProcessRegisters().GetZeroFlag());
        REQUIRE(myProc.GetProcessRegisters().GetNegativeFlag());
        REQUIRE(myProc.GetProcessRegisters().GetCarryFlag());
        delete pInstruction;
    }
}
