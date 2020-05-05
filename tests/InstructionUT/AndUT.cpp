/////////////////////////////////
/// @file AndUT.cpp
///
/// @brief Unit Test for ANDInstruction
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "ANDInstruction.hpp"  // Test class
#include "SLList.hpp"
#include "Process.hpp"

////////////////////////////////
/// Test Objects
////////////////////////////////
ANDInstruction and_instruction = ANDInstruction();
Process myProc = Process();
SLList<std::string> arguments = SLList<std::string>();

////////////////////////////////
/// Setup Function
////////////////////////////////
void setup()
{
    for (int i = 0; i < 13; i++)
    {
        myProc.GetProcessRegisters().genRegs[i] = i;
    }
}

////////////////////////////////
/// AndRegTest Function
////////////////////////////////
void AndRegTest()
{
    // AND R1, R2, R3
    arguments.InsertBack("R1");
    arguments.InsertBack("R2");
    arguments.InsertBack("R3");

    and_instruction.Execute(arguments, myProc, false);

    assert(myProc.GetProcessRegisters().genRegs[1] == 2);
    arguments.Clear();

    // AND R4, R5
    arguments.InsertBack("R4");
    arguments.InsertBack("R5");

    and_instruction.Execute(arguments, myProc, false);

    assert(myProc.GetProcessRegisters().genRegs[4] == 4);
    arguments.Clear();
}

////////////////////////////////
/// AndLiteralTest Function
////////////////////////////////
void AndLiteralTest()
{
    // AND R7, #3
    arguments.InsertBack("R7");
    arguments.InsertBack("#3");

    and_instruction.Execute(arguments, myProc, false);

    assert(myProc.GetProcessRegisters().genRegs[7] == 3);
    arguments.Clear();
}

////////////////////////////////
/// AndsTest Function
////////////////////////////////
void AndsTest()
{
    // ANDS R3, #0
    arguments.InsertBack("R3");
    arguments.InsertBack("#0");

    and_instruction.Execute(arguments, myProc, true);

    assert(myProc.GetProcessRegisters().GetZeroFlag());
    assert(!myProc.GetProcessRegisters().GetNegativeFlag());
    arguments.Clear();

    // "MOV" R5, #0xFFFFFFFF
    myProc.GetProcessRegisters().genRegs[5] = 0xFFFFFFFF;

    // ANDS R5, #0xFFFF0000
    arguments.InsertBack("r5");
    arguments.InsertBack("#0xFFFF0000");

    and_instruction.Execute(arguments, myProc, true);

    assert(!myProc.GetProcessRegisters().GetZeroFlag());
    assert(myProc.GetProcessRegisters().GetNegativeFlag());
    arguments.Clear();
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

    AndRegTest();
    AndLiteralTest();
    AndsTest();

    teardown();

    std::cout << "ANDInstruction Unit Test Complete: SUCCESS";
    return 0;
}