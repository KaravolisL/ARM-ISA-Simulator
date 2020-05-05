/////////////////////////////////
/// @file AddUT.cpp
///
/// @brief Unit Test for ADDInstruction
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "ADDInstruction.hpp"  // Test class
#include "SLList.hpp"
#include "Process.hpp"

////////////////////////////////
/// Test Objects
////////////////////////////////
ADDInstruction add = ADDInstruction();
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
/// AddRegsTest Function
////////////////////////////////
void AddRegsTest()
{
    // ADD R0, R1, R2
    arguments.InsertBack("R0");
    arguments.InsertBack("R1");
    arguments.InsertBack("R2");

    add.Execute(arguments, myProc, false);

    assert(myProc.GetProcessRegisters().genRegs[0] == 3);
    arguments.Clear();

    // ADD R0, R1
    arguments.InsertBack("R0");
    arguments.InsertBack("R1");

    add.Execute(arguments, myProc, false);

    assert(myProc.GetProcessRegisters().genRegs[0] == 4);
    arguments.Clear();
}

////////////////////////////////
/// AddLiterals Function
////////////////////////////////
void AddLiterals()
{
    // ADD R0, R1, #0xA
    arguments.InsertBack("R0");
    arguments.InsertBack("R1");
    arguments.InsertBack("#0xA");

    add.Execute(arguments, myProc, false);

    assert(myProc.GetProcessRegisters().genRegs[0] == 11);
    arguments.Clear();

    // ADD R0, #x11
    arguments.InsertBack("R1");
    arguments.InsertBack("#0x11");

    add.Execute(arguments, myProc, false);

    assert(myProc.GetProcessRegisters().genRegs[1] == 18);
    arguments.Clear();
}

////////////////////////////////
/// AddsTest Function
////////////////////////////////
void AddsTest()
{
    // Reset registers
    setup();

    // ADDS R0, R0
    arguments.InsertBack("R0");
    arguments.InsertBack("R0");

    add.Execute(arguments, myProc, true);

    assert(myProc.GetProcessRegisters().GetZeroFlag());
    assert(!myProc.GetProcessRegisters().GetNegativeFlag());
    assert(!myProc.GetProcessRegisters().GetCarryFlag());
    assert(!myProc.GetProcessRegisters().GetOverflowFlag());
    arguments.Clear();

    // ADDS R0, #-2
    arguments.InsertBack("R0");
    arguments.InsertBack("#-2");

    add.Execute(arguments, myProc, true);

    assert(!myProc.GetProcessRegisters().GetZeroFlag());
    assert(myProc.GetProcessRegisters().GetNegativeFlag());
    assert(!myProc.GetProcessRegisters().GetCarryFlag());
    assert(!myProc.GetProcessRegisters().GetOverflowFlag());
    arguments.Clear();

    // ADDS R10, #0xFFFFFFFF
    arguments.InsertBack("R10");
    arguments.InsertBack("#0xFFFFFFFF");

    add.Execute(arguments, myProc, true);

    assert(!myProc.GetProcessRegisters().GetZeroFlag());
    assert(!myProc.GetProcessRegisters().GetNegativeFlag());
    assert(myProc.GetProcessRegisters().GetCarryFlag());
    assert(!myProc.GetProcessRegisters().GetOverflowFlag());
    arguments.Clear();

    // "MOV" R1, #0x40000000
    myProc.GetProcessRegisters().genRegs[1] = 0x40000000;

    // ADDS R1, #0x40000000
    arguments.InsertBack("R1");
    arguments.InsertBack("#0x40000000");

    add.Execute(arguments, myProc, true);

    assert(!myProc.GetProcessRegisters().GetZeroFlag());
    assert(myProc.GetProcessRegisters().GetNegativeFlag());
    assert(!myProc.GetProcessRegisters().GetCarryFlag());
    assert(myProc.GetProcessRegisters().GetOverflowFlag());
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

    AddRegsTest();
    AddLiterals();
    AddsTest();

    teardown();

    std::cout << "ADDInstruction Unit Test Complete: SUCCESS";
    return 0;
}