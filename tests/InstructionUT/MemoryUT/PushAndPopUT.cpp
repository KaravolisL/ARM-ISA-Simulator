/////////////////////////////////
/// @file PushAndPopUT.cpp
///
/// @brief Unit Test for PUSH and POP Instructions
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
#include "MemoryApi.hpp"
#include "MemoryConstants.hpp"

TEST_CASE("PUSH and POP Instructions", "[instruction][Memory]")
{
    Process myProc = Process();
    InstructionBuilder& builder = InstructionBuilder::GetInstance();
    InstructionBase* pInstruction = nullptr;
    std::string instructionStr;

    for (int i = 0; i < 13; i++)
    {
        myProc.GetProcessRegisters().genRegs[i] = i;
    }

    myProc.GetProcessRegisters().SP = Memory::STACK_LOWER_BOUND;

    instructionStr = "PUSH {R0}";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    REQUIRE(Memory::MemoryApi::ReadWord(myProc.GetProcessRegisters().SP) == 0);
    delete pInstruction;

    // "MOV" R0, #1
    myProc.GetProcessRegisters().genRegs[0] = 1;

    instructionStr = "POP {R0}";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    delete pInstruction;

    instructionStr = "PUSH {R1, R5, R2}";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    REQUIRE(Memory::MemoryApi::ReadWord(myProc.GetProcessRegisters().SP) == 5);
    delete pInstruction;

    // "MOV" R1, #10
    myProc.GetProcessRegisters().genRegs[1] = 10;
    // "MOV" R5, #10
    myProc.GetProcessRegisters().genRegs[5] = 10;
    // "MOV" R2, #10
    myProc.GetProcessRegisters().genRegs[2] = 10;

    instructionStr = "POP {R1, R5, R2}";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    REQUIRE(myProc.GetProcessRegisters().genRegs[5] == 5);
    REQUIRE(myProc.GetProcessRegisters().genRegs[1] == 1);
    REQUIRE(myProc.GetProcessRegisters().genRegs[2] == 2);
    delete pInstruction;

    instructionStr = "PUSH {R2, R5-R7, R0}";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    REQUIRE(Memory::MemoryApi::ReadWord(myProc.GetProcessRegisters().SP) == 7);
    delete pInstruction;

    // "MOV" R0, #10
    myProc.GetProcessRegisters().genRegs[0] = 10;
    // "MOV" R2, #10
    myProc.GetProcessRegisters().genRegs[2] = 10;
    // "MOV" R5, #10
    myProc.GetProcessRegisters().genRegs[5] = 10;
    // "MOV" R6, #10
    myProc.GetProcessRegisters().genRegs[6] = 10;
    // "MOV" R7, #10
    myProc.GetProcessRegisters().genRegs[7] = 10;

    instructionStr = "POP {R5-R7, R0, R2}";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    REQUIRE(myProc.GetProcessRegisters().genRegs[0] == 0);
    REQUIRE(myProc.GetProcessRegisters().genRegs[2] == 2);
    REQUIRE(myProc.GetProcessRegisters().genRegs[5] == 5);
    REQUIRE(myProc.GetProcessRegisters().genRegs[6] == 6);
    REQUIRE(myProc.GetProcessRegisters().genRegs[7] == 7);
    delete pInstruction;
}
