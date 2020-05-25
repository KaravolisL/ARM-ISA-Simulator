/////////////////////////////////
/// @file MovUT.cpp
///
/// @brief Unit Test for MOV Instruction
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
/// MovRegTest Function
////////////////////////////////
void MovRegTest()
{
    instructionStr = "MOV R0, R1";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().genRegs[0] == 1);
}

////////////////////////////////
/// MovLiteralTest Function
////////////////////////////////
void MovLiteralTest()
{
    instructionStr = "MOV R0, #0xFF";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().genRegs[0] == 0xFF);
}

////////////////////////////////
/// MovsTest Function
////////////////////////////////
void MovsTest()
{
    instructionStr = "MOVS R0, #0";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().GetZeroFlag());
    assert(!myProc.GetProcessRegisters().GetNegativeFlag());

    instructionStr = "MOVS R0, #0xFFFFFFFF";

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

    MovRegTest();
    MovLiteralTest();
    MovsTest();

    teardown();

    std::cout << "MOV Instruction Unit Test Complete: SUCCESS";
    return 0;
}