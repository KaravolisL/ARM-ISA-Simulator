/////////////////////////////////
/// @file LslUT.cpp
///
/// @brief Unit Test for LSL Instruction
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
/// LslRegsTest Function
////////////////////////////////
void LslRegsTest()
{
    instructionStr = "LSL R0, R1, R2";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().genRegs[0] == 4);

    instructionStr = "LSL R2, R3";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().genRegs[2] == 16);
}

////////////////////////////////
/// LslLiterals Function
////////////////////////////////
void LslLiterals()
{
    instructionStr = "LSL R0, R3, #0xF";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().genRegs[0] == 0x18000);

    instructionStr = "LSL R1, #0x13";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().genRegs[1] == 0x80000);
}

////////////////////////////////
/// LslsTest Function
////////////////////////////////
void LslsTest()
{
    // Reset registers
    setup();

    instructionStr = "LSLS R0, R1";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().GetZeroFlag());
    assert(!myProc.GetProcessRegisters().GetNegativeFlag());
    assert(!myProc.GetProcessRegisters().GetCarryFlag());

    // "MOV" R2, #0x40000000
    myProc.GetProcessRegisters().genRegs[2] = 0xC0000000;

    instructionStr = "LSLS R2, #1";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(!myProc.GetProcessRegisters().GetZeroFlag());
    assert(myProc.GetProcessRegisters().GetNegativeFlag());
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

    LslRegsTest();
    LslLiterals();
    LslsTest();

    teardown();

    std::cout << "LSL Instruction Unit Test Complete: SUCCESS";
    return 0;
}