/////////////////////////////////
/// @file OrrUT.cpp
///
/// @brief Unit Test for ORR Instruction
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

TEST_CASE("ORR Instruction", "[instruction][ArithAndLogic]")
{
    Process myProc = Process();
    InstructionBuilder& builder = InstructionBuilder::GetInstance();
    InstructionBase* pInstruction = nullptr;
    std::string instructionStr;

    uint32_t a = GENERATE(take(5, random(INT32_MIN, INT32_MAX)));
    uint32_t b = GENERATE(take(5, random(0, 32)));

    SECTION("Or two registers")
    {
        instructionStr = "ORR R0, R1, R2";

        myProc.GetProcessRegisters().genRegs[1] = a;
        myProc.GetProcessRegisters().genRegs[2] = b;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[0] == (a | b));
        delete pInstruction;
    }

    SECTION("Or with a register")
    {
        instructionStr = "ORR R0, R1";

        myProc.GetProcessRegisters().genRegs[0] = a;
        myProc.GetProcessRegisters().genRegs[1] = b;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[0] == (a | b));
        delete pInstruction;
    }

    SECTION("Or register and a literal")
    {
        instructionStr = "ORR R0, R5, #" + std::to_string(a);

        myProc.GetProcessRegisters().genRegs[5] = b;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[0] == (a | b));
        delete pInstruction;
    }

    SECTION("Or register with a literal")
    {
        instructionStr = "ORR R0, #" + std::to_string(a);

        myProc.GetProcessRegisters().genRegs[0] = b;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[0] == (a | b));
        delete pInstruction;
    }

    SECTION("ORRS Test")
    {
        myProc.GetProcessRegisters().genRegs[0] = 0;
        myProc.GetProcessRegisters().genRegs[1] = 1;
        myProc.GetProcessRegisters().genRegs[2] = 2;

        instructionStr = "ORRS R1, R2, #0x80000000";

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().GetNegativeFlag());
        delete pInstruction;

        instructionStr = "ORRS R0, #0";

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().GetZeroFlag());
        REQUIRE(!myProc.GetProcessRegisters().GetNegativeFlag());
        delete pInstruction;
    }
}
