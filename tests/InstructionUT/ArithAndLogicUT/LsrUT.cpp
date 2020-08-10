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

TEST_CASE("LSR Instruction", "[instruction][ArithAndLogic]")
{
    Process myProc = Process();
    InstructionBuilder& builder = InstructionBuilder::GetInstance();
    InstructionBase* pInstruction = nullptr;
    std::string instructionStr;

    uint32_t a = GENERATE(take(5, random(INT32_MIN, INT32_MAX)));
    uint32_t b = GENERATE(take(5, random(0, 32)));

    SECTION("Shift register by another register")
    {
        instructionStr = "LSR R0, R1, R2";

        myProc.GetProcessRegisters().genRegs[1] = a;
        myProc.GetProcessRegisters().genRegs[2] = b;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[0] == (a >> b));
        delete pInstruction;
    }

    SECTION("Shift register with another register")
    {
        instructionStr = "LSR R2, R3";

        myProc.GetProcessRegisters().genRegs[2] = a;
        myProc.GetProcessRegisters().genRegs[3] = b;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[2] == (a >> b));
        delete pInstruction;
    }

    SECTION("Shift register by literal")
    {
        instructionStr = "LSR R0, R1, #" + std::to_string(b);

        myProc.GetProcessRegisters().genRegs[1] = a;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[0] == (a >> b));
        delete pInstruction;
    }

    SECTION("Shift register with literal")
    {
        instructionStr = "LSR R0, #" + std::to_string(b);

        myProc.GetProcessRegisters().genRegs[0] = a;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[0] == (a >> b));
        delete pInstruction;
    }

    SECTION("LSRS Test")
    {
        myProc.GetProcessRegisters().genRegs[0] = 0;
        myProc.GetProcessRegisters().genRegs[1] = 1;
        myProc.GetProcessRegisters().genRegs[7] = 7;

        instructionStr = "LSRS R0, R1";

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().GetZeroFlag());
        REQUIRE(!myProc.GetProcessRegisters().GetNegativeFlag());
        REQUIRE(!myProc.GetProcessRegisters().GetCarryFlag());
        delete pInstruction;

        instructionStr = "LSRS R7, #2";

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(!myProc.GetProcessRegisters().GetZeroFlag());
        REQUIRE(!myProc.GetProcessRegisters().GetNegativeFlag());
        REQUIRE(myProc.GetProcessRegisters().GetCarryFlag());
        delete pInstruction;
    }
}
