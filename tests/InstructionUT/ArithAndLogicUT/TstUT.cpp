/////////////////////////////////
/// @file TstUT.cpp
///
/// @brief Unit Test for TST Instruction
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

TEST_CASE("TST Instruction", "[instruction][ArithAndLogic]")
{
    Process myProc = Process();
    InstructionBuilder& builder = InstructionBuilder::GetInstance();
    InstructionBase* pInstruction = nullptr;
    std::string instructionStr;

    for (int i = 0; i < 13; i++)
    {
        myProc.GetProcessRegisters().genRegs[i] = i;
    }

    instructionStr = "TST R8, #2";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    REQUIRE(myProc.GetProcessRegisters().genRegs[8] == 8);
    REQUIRE(myProc.GetProcessRegisters().GetNegativeFlag() == false);
    REQUIRE(myProc.GetProcessRegisters().GetZeroFlag() == true);
    REQUIRE(myProc.GetProcessRegisters().GetCarryFlag() == false);
    REQUIRE(myProc.GetProcessRegisters().GetOverflowFlag() == false);
    delete pInstruction;

    instructionStr = "TST R8, #8";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    REQUIRE(myProc.GetProcessRegisters().genRegs[8] == 8);
    REQUIRE(myProc.GetProcessRegisters().GetNegativeFlag() == false);
    REQUIRE(myProc.GetProcessRegisters().GetZeroFlag() == false);
    REQUIRE(myProc.GetProcessRegisters().GetCarryFlag() == false);
    REQUIRE(myProc.GetProcessRegisters().GetOverflowFlag() == false);
    delete pInstruction;

    myProc.GetProcessRegisters().genRegs[10] = 0x80000000;
    instructionStr = "TST R10, #0x80000000";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    REQUIRE(myProc.GetProcessRegisters().genRegs[10] == 0x80000000);
    REQUIRE(myProc.GetProcessRegisters().GetNegativeFlag() == true);
    REQUIRE(myProc.GetProcessRegisters().GetZeroFlag() == false);
    REQUIRE(myProc.GetProcessRegisters().GetCarryFlag() == false);
    REQUIRE(myProc.GetProcessRegisters().GetOverflowFlag() == false);
    delete pInstruction;
}
