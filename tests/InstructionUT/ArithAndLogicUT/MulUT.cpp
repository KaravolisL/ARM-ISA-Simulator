/////////////////////////////////
/// @file MulUT.cpp
///
/// @brief Unit Test for MUL Instruction
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

TEST_CASE("MUL Instruction", "[instruction][ArithAndLogic]")
{
    Process myProc = Process();
    InstructionBuilder& builder = InstructionBuilder::GetInstance();
    InstructionBase* pInstruction = nullptr;

    for (int i = 0; i < 13; i++)
    {
        myProc.GetProcessRegisters().genRegs[i] = i;
    }

    SECTION("Multiply registers")
    {
        std::string instructionStr = "MUL R0, R1, R2";
        int a = GENERATE(take(5, random(INT32_MIN, INT32_MAX)));
        int b = GENERATE(take(5, random(INT32_MIN, INT32_MAX)));

        myProc.GetProcessRegisters().genRegs[1] = a;
        myProc.GetProcessRegisters().genRegs[2] = b;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[0] == static_cast<uint32_t>((a * b)));
        delete pInstruction;
    }

    SECTION("Multiply to a register")
    {
        std::string instructionStr = "MUL R0, R1";
        int a = GENERATE(take(5, random(INT32_MIN, INT32_MAX)));
        int b = GENERATE(take(5, random(INT32_MIN, INT32_MAX)));

        myProc.GetProcessRegisters().genRegs[0] = a;
        myProc.GetProcessRegisters().genRegs[1] = b;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[0] == static_cast<uint32_t>((a * b)));
        delete pInstruction;
    }

    SECTION("Multiply literal with a register")
    {
        int literal = GENERATE(take(5, random(INT32_MIN, INT32_MAX)));
        std::string baseInstructionStr = "MUL R0, R1, #";
        std::string instructionStr = baseInstructionStr + std::to_string(literal);
        myProc.GetProcessRegisters().genRegs[1] = 3;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[0] == static_cast<uint32_t>(3 * literal));
        delete pInstruction;
    }

    SECTION("Multiply literal to a register")
    {
        int literal = GENERATE(take(5, random(INT32_MIN, INT32_MAX)));
        std::string baseInstructionStr = "MUL R1, #";
        std::string instructionStr = baseInstructionStr + std::to_string(literal);
        myProc.GetProcessRegisters().genRegs[1] = 3;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[1] == static_cast<uint32_t>(3 * literal));
        delete pInstruction;
    }

    SECTION("MULS test")
    {
        std::string instructionStr = "MULS R0, R10";

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().GetZeroFlag());
        REQUIRE(!myProc.GetProcessRegisters().GetNegativeFlag());
        REQUIRE(!myProc.GetProcessRegisters().GetCarryFlag());
        REQUIRE(!myProc.GetProcessRegisters().GetOverflowFlag());
        delete pInstruction;

        instructionStr = "MULS R1, #-2";

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(!myProc.GetProcessRegisters().GetZeroFlag());
        REQUIRE(myProc.GetProcessRegisters().GetNegativeFlag());
        REQUIRE(!myProc.GetProcessRegisters().GetCarryFlag());
        REQUIRE(!myProc.GetProcessRegisters().GetOverflowFlag());
        delete pInstruction;
    }
}
