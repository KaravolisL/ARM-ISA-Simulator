/////////////////////////////////
/// @file SubUT.cpp
///
/// @brief Unit Test for SUB Instruction
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

TEST_CASE("SUB Instruction", "[instruction][ArithAndLogic]")
{
    Process myProc = Process();
    InstructionBuilder& builder = InstructionBuilder::GetInstance();
    InstructionBase* pInstruction = nullptr;
    std::string instructionStr;

    uint32_t a = GENERATE(take(5, random(INT32_MIN, INT32_MAX)));
    uint32_t b = GENERATE(take(5, random(0, 32)));

    SECTION("Subtract two registers")
    {
        instructionStr = "SUB R0, R1, R2";

        myProc.GetProcessRegisters().genRegs[1] = a;
        myProc.GetProcessRegisters().genRegs[2] = b;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[0] == (a - b));
        delete pInstruction;
    }

    SECTION("Subtract from a register")
    {
        instructionStr = "SUB R0, R1";

        myProc.GetProcessRegisters().genRegs[0] = a;
        myProc.GetProcessRegisters().genRegs[1] = b;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[0] == (a - b));
        delete pInstruction;
    }

    SECTION("Subtract literal and a register")
    {
        instructionStr = "SUB R0, R1, #" + std::to_string(b);

        myProc.GetProcessRegisters().genRegs[1] = a;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[0] == (a - b));
        delete pInstruction;
    }

    SECTION("Subtract literal from a register")
    {
        instructionStr = "SUB R0, #" + std::to_string(b);

        myProc.GetProcessRegisters().genRegs[0] = a;

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().genRegs[0] == (a - b));
        delete pInstruction;
    }

    SECTION("SUBS Test")
    {
        for (int i = 0; i < 13; i++)
        {
            myProc.GetProcessRegisters().genRegs[i] = i;
        }

        instructionStr = "SUBS R10, #10";

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().GetNegativeFlag() == false);
        REQUIRE(myProc.GetProcessRegisters().GetZeroFlag() == true);
        REQUIRE(myProc.GetProcessRegisters().GetCarryFlag() == true);
        REQUIRE(myProc.GetProcessRegisters().GetOverflowFlag() == false);
        delete pInstruction;

        instructionStr = "SUBS R9, #6";

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().GetNegativeFlag() == false);
        REQUIRE(myProc.GetProcessRegisters().GetZeroFlag() == false);
        REQUIRE(myProc.GetProcessRegisters().GetCarryFlag() == true);
        REQUIRE(myProc.GetProcessRegisters().GetOverflowFlag() == false);
        delete pInstruction;

        instructionStr = "SUBS R10, #16";

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().GetNegativeFlag() == true);
        REQUIRE(myProc.GetProcessRegisters().GetZeroFlag() == false);
        REQUIRE(myProc.GetProcessRegisters().GetCarryFlag() == false);
        REQUIRE(myProc.GetProcessRegisters().GetOverflowFlag() == false);
        delete pInstruction;

        instructionStr = "SUBS R0, #0";

        pInstruction = builder.BuildInstruction(instructionStr, &myProc);
        pInstruction->Execute(myProc.GetProcessRegisters());
        REQUIRE(myProc.GetProcessRegisters().GetNegativeFlag() == false);
        REQUIRE(myProc.GetProcessRegisters().GetZeroFlag() == true);
        REQUIRE(myProc.GetProcessRegisters().GetCarryFlag() == true);
        REQUIRE(myProc.GetProcessRegisters().GetOverflowFlag() == false);
        delete pInstruction;
    }
}
