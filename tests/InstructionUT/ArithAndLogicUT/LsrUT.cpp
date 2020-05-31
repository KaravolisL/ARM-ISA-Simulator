/////////////////////////////////
/// @file LsrUT.cpp
///
/// @brief Unit Test for LSR Instruction
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
/// LsrRegsTest Function
////////////////////////////////
void LsrRegsTest()
{
    instructionStr = "LSR R0, R8, R2";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().genRegs[0] == 2);

    instructionStr = "LSR R8, R3";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().genRegs[8] == 1);
}

////////////////////////////////
/// LsrLiterals Function
////////////////////////////////
void LsrLiterals()
{
    instructionStr = "LSR R0, R10, #0x2";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().genRegs[0] == 2);

    instructionStr = "LSR R12, #0x3";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().genRegs[12] == 1);
}

////////////////////////////////
/// LsrsTest Function
////////////////////////////////
void LsrsTest()
{
    // Reset registers
    setup();

    instructionStr = "LSRS R0, R1";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().GetZeroFlag());
    assert(!myProc.GetProcessRegisters().GetNegativeFlag());
    assert(!myProc.GetProcessRegisters().GetCarryFlag());

    instructionStr = "LSRS R7, #2";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(!myProc.GetProcessRegisters().GetZeroFlag());
    assert(!myProc.GetProcessRegisters().GetNegativeFlag());
    assert(myProc.GetProcessRegisters().GetCarryFlag());
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

    LsrRegsTest();
    LsrLiterals();
    LsrsTest();

    teardown();

    std::cout << "LSR Instruction Unit Test Complete: SUCCESS";
    return 0;
}