/////////////////////////////////
/// @file PushAndPopUT.cpp
///
/// @brief Unit Test for PUSH and POP Instructions
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "InvalidSyntaxException.hpp"
#include "Process.hpp"
#include "InstructionBuilder.hpp"
#include "InstructionBase.hpp"
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
/// PushAndPopTest Function
////////////////////////////////
void PushAndPopTest()
{
    instructionStr = "PUSH {R0}";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessStack().Peek() == 0);
    delete pInstruction;

    // "MOV" R0, #1
    myProc.GetProcessRegisters().genRegs[0] = 1;

    instructionStr = "POP {R0}";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessStack().Size() == 0);
    delete pInstruction;

    instructionStr = "PUSH {R1, R5, R2}";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessStack().Peek() == 5);
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
    assert(myProc.GetProcessRegisters().genRegs[5] == 5);
    assert(myProc.GetProcessRegisters().genRegs[1] == 1);
    assert(myProc.GetProcessRegisters().genRegs[2] == 2);
    delete pInstruction;

    instructionStr = "PUSH {R2, R5-R7, R0}";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessStack().Peek() == 7);
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
    assert(myProc.GetProcessRegisters().genRegs[0] == 0);
    assert(myProc.GetProcessRegisters().genRegs[2] == 2);
    assert(myProc.GetProcessRegisters().genRegs[5] == 5);
    assert(myProc.GetProcessRegisters().genRegs[6] == 6);
    assert(myProc.GetProcessRegisters().genRegs[7] == 7);
    delete pInstruction;
}

////////////////////////////////
/// Teardown Function
////////////////////////////////
void teardown()
{

}

////////////////////////////////
/// Main Function
////////////////////////////////
int main(int argc, char* argv[])
{
    setup();

    PushAndPopTest();

    teardown();

    std::cout << "PUSH and POP Instruction Unit Test Complete: SUCCESS";
    return 0;
}