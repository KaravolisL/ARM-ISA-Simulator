/////////////////////////////////
/// @file CmnUT.cpp
///
/// @brief Unit Test for CMN Instruction
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

TEST_CASE("CMN Instruction", "[instruction][ArithAndLogic]")
{
    Process myProc = Process();
    InstructionBuilder& builder = InstructionBuilder::GetInstance();
    InstructionBase* pInstruction = nullptr;
    std::string instructionStr;

    for (int i = 0; i < 13; i++)
    {
        myProc.GetProcessRegisters().genRegs[i] = i;
    }

    instructionStr = "CMN R0, R0";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    REQUIRE(myProc.GetProcessRegisters().GetZeroFlag());
    REQUIRE(!myProc.GetProcessRegisters().GetNegativeFlag());
    REQUIRE(!myProc.GetProcessRegisters().GetCarryFlag());
    REQUIRE(!myProc.GetProcessRegisters().GetOverflowFlag());
    delete pInstruction;

    instructionStr = "CMN R0, #-2";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    REQUIRE(myProc.GetProcessRegisters().genRegs[0] == 0);
    REQUIRE(!myProc.GetProcessRegisters().GetZeroFlag());
    REQUIRE(myProc.GetProcessRegisters().GetNegativeFlag());
    REQUIRE(!myProc.GetProcessRegisters().GetCarryFlag());
    REQUIRE(!myProc.GetProcessRegisters().GetOverflowFlag());
    delete pInstruction;

    instructionStr = "CMN R10, #0xFFFFFFFF";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    REQUIRE(!myProc.GetProcessRegisters().GetZeroFlag());
    REQUIRE(!myProc.GetProcessRegisters().GetNegativeFlag());
    REQUIRE(myProc.GetProcessRegisters().GetCarryFlag());
    REQUIRE(!myProc.GetProcessRegisters().GetOverflowFlag());
    delete pInstruction;

    // "MOV" R1, #0x40000000
    myProc.GetProcessRegisters().genRegs[1] = 0x40000000;

    instructionStr = "CMN R1, #0x40000000";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    REQUIRE(!myProc.GetProcessRegisters().GetZeroFlag());
    REQUIRE(myProc.GetProcessRegisters().GetNegativeFlag());
    REQUIRE(!myProc.GetProcessRegisters().GetCarryFlag());
    REQUIRE(myProc.GetProcessRegisters().GetOverflowFlag());
    delete pInstruction;
}
