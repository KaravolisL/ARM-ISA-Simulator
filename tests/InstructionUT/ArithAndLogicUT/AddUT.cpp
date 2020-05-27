/////////////////////////////////
/// @file AddUT.cpp
///
/// @brief Unit Test for ADD Instruction
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
/// AddRegsTest Function
////////////////////////////////
void AddRegsTest()
{
    std::string instructionStr = "ADD R0, R1, R2";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().genRegs[0] == 3);

    instructionStr = "ADD R0, R1";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().genRegs[0] == 4);
}

////////////////////////////////
/// AddLiterals Function
////////////////////////////////
void AddLiterals()
{
    std::string instructionStr = "ADD R0, R1, #0xA";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().genRegs[0] == 11);

    instructionStr = "ADD R1, #0x11";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().genRegs[1] == 18);    
}

////////////////////////////////
/// AddsTest Function
////////////////////////////////
void AddsTest()
{
    // Reset registers
    setup();

    std::string instructionStr = "ADDS R0, R0";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().GetZeroFlag());
    assert(!myProc.GetProcessRegisters().GetNegativeFlag());
    assert(!myProc.GetProcessRegisters().GetCarryFlag());
    assert(!myProc.GetProcessRegisters().GetOverflowFlag());

    instructionStr = "ADDS R0, #-2";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(!myProc.GetProcessRegisters().GetZeroFlag());
    assert(myProc.GetProcessRegisters().GetNegativeFlag());
    assert(!myProc.GetProcessRegisters().GetCarryFlag());
    assert(!myProc.GetProcessRegisters().GetOverflowFlag());

    instructionStr = "ADDS R10, #0xFFFFFFFF";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(!myProc.GetProcessRegisters().GetZeroFlag());
    assert(!myProc.GetProcessRegisters().GetNegativeFlag());
    assert(myProc.GetProcessRegisters().GetCarryFlag());
    assert(!myProc.GetProcessRegisters().GetOverflowFlag());

    // "MOV" R1, #0x40000000
    myProc.GetProcessRegisters().genRegs[1] = 0x40000000;

    instructionStr = "ADDS R1, #0x40000000";

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

    AddRegsTest();
    AddLiterals();
    AddsTest();

    teardown();

    std::cout << "ADD Instruction Unit Test Complete: SUCCESS";
    return 0;
}