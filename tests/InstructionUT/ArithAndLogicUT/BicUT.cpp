/////////////////////////////////
/// @file BicUT.cpp
///
/// @brief Unit Test for BIC Instruction
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include <catch2/catch.hpp>
#include "UnitTest.hpp"
#include "InstructionBase.hpp"
#include "InstructionBuilder.hpp"
#include "Process.hpp"

TEST_CASE("BIC Instruction", "[instruction][ArithAndLogic]")
{
    Process myProc = Process();
    InstructionBuilder& builder = InstructionBuilder::GetInstance();
    InstructionBase* pInstruction = nullptr;

    for (int i = 0; i < 13; i++)
    {
        myProc.GetProcessRegisters().genRegs[i] = i;
    }

    SECTION("BIC two registers together")
    {
        std::string instructionStr = "BIC R0, R1, R2";
        int a = GENERATE(take(5, random(INT32_MIN, INT32_MAX)));
        int b = GENERATE(take(5, random(INT32_MIN, INT32_MAX)));

        myProc.GetProcessRegisters().genRegs[1] = a;
        myProc.GetProcessRegisters().genRegs[2] = b;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[0] == static_cast<uint32_t>(a & ~(b)));
        delete pInstruction;
    }

    SECTION("BIC with a register")
    {
        std::string instructionStr = "BIC R0, R1";
        int a = GENERATE(take(5, random(INT32_MIN, INT32_MAX)));
        int b = GENERATE(take(5, random(INT32_MIN, INT32_MAX)));

        myProc.GetProcessRegisters().genRegs[0] = a;
        myProc.GetProcessRegisters().genRegs[1] = b;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[0] == static_cast<uint32_t>(a & ~(b)));
        delete pInstruction;
    }

    SECTION("BIC literal and a register")
    {
        int literal = GENERATE(take(5, random(INT32_MIN, INT32_MAX)));
        int a = GENERATE(take(5, random(INT32_MIN, INT32_MAX)));
        std::string baseInstructionStr = "BIC R0, R1, #";
        std::string instructionStr = baseInstructionStr + std::to_string(literal);
        myProc.GetProcessRegisters().genRegs[1] = a;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[0] == static_cast<uint32_t>(a & ~(literal)));
        delete pInstruction;
    }

    SECTION("BIC register with a literal")
    {
        int literal = GENERATE(take(5, random(INT32_MIN, INT32_MAX)));
        std::string baseInstructionStr = "BIC R1, #";
        std::string instructionStr = baseInstructionStr + std::to_string(literal);
        myProc.GetProcessRegisters().genRegs[1] = 1;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[1] == static_cast<uint32_t>(1 & ~(literal)));
        delete pInstruction;
    }

    SECTION("BICS Test")
    {
        // "MOV" R1, #1
        myProc.GetProcessRegisters().genRegs[1] = 0x1;
        std::string instructionStr = "BICS R1, R1";

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().GetZeroFlag());
        REQUIRE(!myProc.GetProcessRegisters().GetNegativeFlag());
        delete pInstruction;

        // "MOV" R5, #0xFFFFFFFF
        myProc.GetProcessRegisters().genRegs[5] = 0xFFFFFFFF;

        instructionStr = "BICS R5, #0xF";

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(!myProc.GetProcessRegisters().GetZeroFlag());
        REQUIRE(myProc.GetProcessRegisters().GetNegativeFlag());
        delete pInstruction;
    }
}
