/////////////////////////////////
/// @file TeqUT.cpp
///
/// @brief Unit Test for TEQ Instruction
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

TEST_CASE("TEQ Instruction", "[instruction][ArithAndLogic]")
{
    Process myProc = Process();
    InstructionBuilder& builder = InstructionBuilder::GetInstance();
    InstructionBase* pInstruction = nullptr;
    std::string instructionStr;

    for (int i = 0; i < 13; i++)
    {
        myProc.GetProcessRegisters().genRegs[i] = i;
    }

    instructionStr = "TEQ R8, #2";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    REQUIRE(myProc.GetProcessRegisters().genRegs[8] == 8);
    REQUIRE(myProc.GetProcessRegisters().GetNegativeFlag() == false);
    REQUIRE(myProc.GetProcessRegisters().GetZeroFlag() == false);
    REQUIRE(myProc.GetProcessRegisters().GetCarryFlag() == false);
    REQUIRE(myProc.GetProcessRegisters().GetOverflowFlag() == false);
    delete pInstruction;

    myProc.GetProcessRegisters().genRegs[8] = -1;
    instructionStr = "TEQ R8, #1";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    REQUIRE(static_cast<int32_t>(myProc.GetProcessRegisters().genRegs[8]) == -1);
    REQUIRE(myProc.GetProcessRegisters().GetNegativeFlag() == true);
    REQUIRE(myProc.GetProcessRegisters().GetZeroFlag() == false);
    REQUIRE(myProc.GetProcessRegisters().GetCarryFlag() == false);
    REQUIRE(myProc.GetProcessRegisters().GetOverflowFlag() == false);
    delete pInstruction;

    instructionStr = "TEQ R0, #0";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    REQUIRE(myProc.GetProcessRegisters().genRegs[10] == 10);
    REQUIRE(myProc.GetProcessRegisters().GetNegativeFlag() == false);
    REQUIRE(myProc.GetProcessRegisters().GetZeroFlag() == true);
    REQUIRE(myProc.GetProcessRegisters().GetCarryFlag() == false);
    REQUIRE(myProc.GetProcessRegisters().GetOverflowFlag() == false);
    delete pInstruction;
}
