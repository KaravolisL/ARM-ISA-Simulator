/////////////////////////////////
/// @file CmpUT.cpp
///
/// @brief Unit Test for CMPInstruction
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

TEST_CASE("CMP Instruction", "[instruction][ArithAndLogic]")
{
    Process myProc = Process();
    InstructionBuilder& builder = InstructionBuilder::GetInstance();
    InstructionBase* pInstruction = nullptr;
    std::string instructionStr;

    for (int i = 0; i < 13; i++)
    {
        myProc.GetProcessRegisters().genRegs[i] = i;
    }

    instructionStr = "CMP R10, #10";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    REQUIRE(myProc.GetProcessRegisters().genRegs[10] == 10);
    REQUIRE(myProc.GetProcessRegisters().GetNegativeFlag() == false);
    REQUIRE(myProc.GetProcessRegisters().GetZeroFlag() == true);
    REQUIRE(myProc.GetProcessRegisters().GetCarryFlag() == true);
    REQUIRE(myProc.GetProcessRegisters().GetOverflowFlag() == false);
    delete pInstruction;

    instructionStr = "CMP R10, #6";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    REQUIRE(myProc.GetProcessRegisters().genRegs[10] == 10);
    REQUIRE(myProc.GetProcessRegisters().GetNegativeFlag() == false);
    REQUIRE(myProc.GetProcessRegisters().GetZeroFlag() == false);
    REQUIRE(myProc.GetProcessRegisters().GetCarryFlag() == true);
    REQUIRE(myProc.GetProcessRegisters().GetOverflowFlag() == false);
    delete pInstruction;

    instructionStr = "CMP R10, #16";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    REQUIRE(myProc.GetProcessRegisters().genRegs[10] == 10);
    REQUIRE(myProc.GetProcessRegisters().GetNegativeFlag() == true);
    REQUIRE(myProc.GetProcessRegisters().GetZeroFlag() == false);
    REQUIRE(myProc.GetProcessRegisters().GetCarryFlag() == false);
    REQUIRE(myProc.GetProcessRegisters().GetOverflowFlag() == false);
    delete pInstruction;

    // "MOV" R1, #0
    myProc.GetProcessRegisters().genRegs[1] = 0;

    instructionStr = "CMP R0, R1";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    REQUIRE(myProc.GetProcessRegisters().genRegs[0] == 0);
    REQUIRE(myProc.GetProcessRegisters().genRegs[1] == 0);
    REQUIRE(myProc.GetProcessRegisters().GetNegativeFlag() == false);
    REQUIRE(myProc.GetProcessRegisters().GetZeroFlag() == true);
    REQUIRE(myProc.GetProcessRegisters().GetCarryFlag() == true);
    REQUIRE(myProc.GetProcessRegisters().GetOverflowFlag() == false);
    delete pInstruction;
}
