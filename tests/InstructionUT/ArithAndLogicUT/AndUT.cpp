/////////////////////////////////
/// @file AndUT.cpp
///
/// @brief Unit Test for AND Instruction
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "InstructionBase.hpp"
#include "InstructionBuilder.hpp"
#include "Process.hpp"
#include "KeywordDict.hpp"

////////////////////////////////
/// Test Objects
////////////////////////////////
Process myProc = Process();
InstructionBuilder& builder = InstructionBuilder::GetInstance();
InstructionBase* pInstruction = nullptr;
std::string instructionStr;

////////////////////////////////
/// Setup Function
////////////////////////////////
void setup()
{
    for (int i = 0; i < 13; i++)
    {
        myProc.GetProcessRegisters().genRegs[i] = i;
    }

    KeywordDict::GetInstance().Initialize();
}

////////////////////////////////
/// AndRegTest Function
////////////////////////////////
void AndRegTest()
{
    instructionStr = "AND R1, R2, R3";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().genRegs[1] == 2);

    instructionStr = "AND R4, R5";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().genRegs[4] == 4);
}

////////////////////////////////
/// AndLiteralTest Function
////////////////////////////////
void AndLiteralTest()
{
    instructionStr = "AND R7, #3";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().genRegs[7] == 3);
}

////////////////////////////////
/// AndsTest Function
////////////////////////////////
void AndsTest()
{
    instructionStr = "ANDS R3, #0";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().GetZeroFlag());
    assert(!myProc.GetProcessRegisters().GetNegativeFlag());

    // "MOV" R5, #0xFFFFFFFF
    myProc.GetProcessRegisters().genRegs[5] = 0xFFFFFFFF;

    instructionStr = "ANDS R5, #0xFFFF0000";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(!myProc.GetProcessRegisters().GetZeroFlag());
    assert(myProc.GetProcessRegisters().GetNegativeFlag());
}

////////////////////////////////
/// Teardown Function
////////////////////////////////
void teardown()
{
    delete pInstruction;
}

////////////////////////////////
/// Main Function
////////////////////////////////
int main(int argc, char* argv[])
{
    setup();

    AndRegTest();
    AndLiteralTest();
    AndsTest();

    teardown();

    std::cout << "ANDInstruction Unit Test Complete: SUCCESS";
    return 0;
}