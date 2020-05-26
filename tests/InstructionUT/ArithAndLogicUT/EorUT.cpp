/////////////////////////////////
/// @file EorUT.cpp
///
/// @brief Unit Test for EOR Instruction
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
/// EorRegsTest Function
////////////////////////////////
void EorRegsTest()
{
    instructionStr = "EOR R0, R5, R7";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().genRegs[0] == 2);

    instructionStr = "EOR R8, R9";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().genRegs[8] == 1);
}

////////////////////////////////
/// EorLiterals Function
////////////////////////////////
void EorLiterals()
{
    instructionStr = "EOR R0, R5, #0xF";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().genRegs[0] == 10);

    instructionStr = "EOR R1, #0x13";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().genRegs[1] == 0x12);
}

////////////////////////////////
/// EorsTest Function
////////////////////////////////
void EorsTest()
{
    // Reset registers
    setup();

    instructionStr = "EORS R1, R1";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().GetZeroFlag());
    assert(!myProc.GetProcessRegisters().GetNegativeFlag());

    instructionStr = "EORS R2, #0xFFFFFFFF";

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

    EorRegsTest();
    EorLiterals();
    EorsTest();

    teardown();

    std::cout << "EOR Instruction Unit Test Complete: SUCCESS";
    return 0;
}