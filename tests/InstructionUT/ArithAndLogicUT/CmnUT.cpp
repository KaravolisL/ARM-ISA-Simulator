/////////////////////////////////
/// @file CmnUT.cpp
///
/// @brief Unit Test for CMN Instruction
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
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
/// CmnTest Function
////////////////////////////////
void CmnTest()
{
    instructionStr = "CMN R0, R0";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().GetZeroFlag());
    assert(!myProc.GetProcessRegisters().GetNegativeFlag());
    assert(!myProc.GetProcessRegisters().GetCarryFlag());
    assert(!myProc.GetProcessRegisters().GetOverflowFlag());

    instructionStr = "CMN R0, #-2";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().genRegs[0] == 0);
    assert(!myProc.GetProcessRegisters().GetZeroFlag());
    assert(myProc.GetProcessRegisters().GetNegativeFlag());
    assert(!myProc.GetProcessRegisters().GetCarryFlag());
    assert(!myProc.GetProcessRegisters().GetOverflowFlag());

    instructionStr = "CMN R10, #0xFFFFFFFF";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(!myProc.GetProcessRegisters().GetZeroFlag());
    assert(!myProc.GetProcessRegisters().GetNegativeFlag());
    assert(myProc.GetProcessRegisters().GetCarryFlag());
    assert(!myProc.GetProcessRegisters().GetOverflowFlag());

    // "MOV" R1, #0x40000000
    myProc.GetProcessRegisters().genRegs[1] = 0x40000000;

    instructionStr = "CMN R1, #0x40000000";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(!myProc.GetProcessRegisters().GetZeroFlag());
    assert(myProc.GetProcessRegisters().GetNegativeFlag());
    assert(!myProc.GetProcessRegisters().GetCarryFlag());
    assert(myProc.GetProcessRegisters().GetOverflowFlag());
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

    CmnTest();

    teardown();

    std::cout << "CMN Instruction Unit Test Complete: SUCCESS";
    return 0;
}