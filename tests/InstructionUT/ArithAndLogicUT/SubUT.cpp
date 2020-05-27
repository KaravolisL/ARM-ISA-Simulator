/////////////////////////////////
/// @file SubUT.cpp
///
/// @brief Unit Test for SUB Instruction
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
/// SubRegsTest Function
////////////////////////////////
void SubRegsTest()
{
    instructionStr = "SUB R0, R2, R1";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().genRegs[0] == 1);


    instructionStr = "SUB R0, R1";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().genRegs[0] == 0);
}

////////////////////////////////
/// SubLiterals Function
////////////////////////////////
void SubLiterals()
{
    instructionStr = "SUB R0, R11, #0xA";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().genRegs[0] == 1);

    instructionStr = "SUB R5, #0x4";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());

    assert(myProc.GetProcessRegisters().genRegs[5] == 1);
}

////////////////////////////////
/// SubsTest Function
////////////////////////////////
void SubsTest()
{
    // Reset registers
    setup();

    instructionStr = "SUBS R10, #10";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().GetNegativeFlag() == false);
    assert(myProc.GetProcessRegisters().GetZeroFlag() == true);
    assert(myProc.GetProcessRegisters().GetCarryFlag() == true);
    assert(myProc.GetProcessRegisters().GetOverflowFlag() == false);

    instructionStr = "SUBS R9, #6";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().GetNegativeFlag() == false);
    assert(myProc.GetProcessRegisters().GetZeroFlag() == false);
    assert(myProc.GetProcessRegisters().GetCarryFlag() == true);
    assert(myProc.GetProcessRegisters().GetOverflowFlag() == false);


    instructionStr = "SUBS R10, #16";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
    assert(myProc.GetProcessRegisters().GetNegativeFlag() == true);
    assert(myProc.GetProcessRegisters().GetZeroFlag() == false);
    assert(myProc.GetProcessRegisters().GetCarryFlag() == false);
    assert(myProc.GetProcessRegisters().GetOverflowFlag() == false);

    instructionStr = "SUBS R0, #0";

    pInstruction = builder.BuildInstruction(instructionStr, &myProc);
    pInstruction->Execute(myProc.GetProcessRegisters());
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

    SubRegsTest();
    SubLiterals();
    SubsTest();

    teardown();

    std::cout << "SUB Instruction Unit Test Complete: SUCCESS";
    return 0;
}