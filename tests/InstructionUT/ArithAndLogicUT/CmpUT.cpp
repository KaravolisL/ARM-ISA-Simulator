/////////////////////////////////
/// @file CmpUT.cpp
///
/// @brief Unit Test for CMPInstruction
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
/// CompareTest Function
////////////////////////////////
void CompareTest()
{
    instructionStr = "CMP R10, #10";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().genRegs[10] == 10);
    assert(myProc.GetProcessRegisters().GetNegativeFlag() == false);
    assert(myProc.GetProcessRegisters().GetZeroFlag() == true);
    assert(myProc.GetProcessRegisters().GetCarryFlag() == true);
    assert(myProc.GetProcessRegisters().GetOverflowFlag() == false);

    instructionStr = "CMP R10, #6";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().genRegs[10] == 10);
    assert(myProc.GetProcessRegisters().GetNegativeFlag() == false);
    assert(myProc.GetProcessRegisters().GetZeroFlag() == false);
    assert(myProc.GetProcessRegisters().GetCarryFlag() == true);
    assert(myProc.GetProcessRegisters().GetOverflowFlag() == false);

    instructionStr = "CMP R10, #16";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().genRegs[10] == 10);
    assert(myProc.GetProcessRegisters().GetNegativeFlag() == true);
    assert(myProc.GetProcessRegisters().GetZeroFlag() == false);
    assert(myProc.GetProcessRegisters().GetCarryFlag() == false);
    assert(myProc.GetProcessRegisters().GetOverflowFlag() == false);

    // "MOV" R1, #0
    myProc.GetProcessRegisters().genRegs[1] = 0;

    instructionStr = "CMP R0, R1";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().genRegs[0] == 0);
    assert(myProc.GetProcessRegisters().genRegs[1] == 0);
    assert(myProc.GetProcessRegisters().GetNegativeFlag() == false);
    assert(myProc.GetProcessRegisters().GetZeroFlag() == true);
    assert(myProc.GetProcessRegisters().GetCarryFlag() == true);
    assert(myProc.GetProcessRegisters().GetOverflowFlag() == false);
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

    CompareTest();

    teardown();

    std::cout << "CMP Instruction Unit Test Complete: SUCCESS";
    return 0;
}