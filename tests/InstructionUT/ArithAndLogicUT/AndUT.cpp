/////////////////////////////////
/// @file AndUT.cpp
///
/// @brief Unit Test for AND Instruction
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

TEST_CASE("AND Instruction", "[instruction][ArithAndLogic]")
{
    Process myProc = Process();
    InstructionBuilder& builder = InstructionBuilder::GetInstance();
    InstructionBase* pInstruction = nullptr;

    for (int i = 0; i < 13; i++)
    {
        myProc.GetProcessRegisters().genRegs[i] = i;
    }

    SECTION("AND two registers")
    {
        std::string instructionStr = "AND R0, R1, R2";
        int a = GENERATE(take(5, random(INT32_MIN, INT32_MAX)));
        int b = GENERATE(take(5, random(INT32_MIN, INT32_MAX)));

        myProc.GetProcessRegisters().genRegs[1] = a;
        myProc.GetProcessRegisters().genRegs[2] = b;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[0] == static_cast<uint32_t>((a & b)));
        delete pInstruction;
    }

    SECTION("AND to a register")
    {
        std::string instructionStr = "AND R0, R1";
        int a = GENERATE(take(5, random(INT32_MIN, INT32_MAX)));
        int b = GENERATE(take(5, random(INT32_MIN, INT32_MAX)));

        myProc.GetProcessRegisters().genRegs[0] = a;
        myProc.GetProcessRegisters().genRegs[1] = b;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[0] == static_cast<uint32_t>((a & b)));
        delete pInstruction;
    }

    SECTION("AND a register and a literal")
    {
        int literal = GENERATE(take(5, random(INT32_MIN, INT32_MAX)));
        std::string baseInstructionStr = "AND R0, R1, #";
        std::string instructionStr = baseInstructionStr + std::to_string(literal);
        int a = GENERATE(take(1, random(INT32_MIN, INT32_MAX)));
        myProc.GetProcessRegisters().genRegs[1] = a;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[0] == static_cast<uint32_t>(a & literal));
        delete pInstruction;
    }

    SECTION("AND a register with a literal")
    {
        int literal = GENERATE(take(5, random(INT32_MIN, INT32_MAX)));
        std::string baseInstructionStr = "AND R0, #";
        std::string instructionStr = baseInstructionStr + std::to_string(literal);
        int a = GENERATE(take(1, random(INT32_MIN, INT32_MAX)));
        myProc.GetProcessRegisters().genRegs[0] = a;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[0] == static_cast<uint32_t>(a & literal));
        delete pInstruction;
    }

    SECTION("ANDS Test")
    {
        std::string instructionStr = "ANDS R3, #0";

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().GetZeroFlag());
        REQUIRE(!myProc.GetProcessRegisters().GetNegativeFlag());
        delete pInstruction;

        // "MOV" R5, #0xFFFFFFFF
        myProc.GetProcessRegisters().genRegs[5] = 0xFFFFFFFF;

        instructionStr = "ANDS R5, #0xFFFF0000";

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(!myProc.GetProcessRegisters().GetZeroFlag());
        REQUIRE(myProc.GetProcessRegisters().GetNegativeFlag());
        delete pInstruction;
    }
}
