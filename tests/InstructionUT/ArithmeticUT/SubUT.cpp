/////////////////////////////////
/// @file SubUT.cpp
///
/// @brief Unit Test for SUBInstruction
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "SUBInstruction.hpp"  // Test class
#include "SLList.hpp"
#include "Process.hpp"

////////////////////////////////
/// Test Objects
////////////////////////////////
SUBInstruction sub = SUBInstruction();
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
/// SubRegsTest Function
////////////////////////////////
void SubRegsTest()
{
    // SUB R0, R2, R1
    arguments.InsertBack("R0");
    arguments.InsertBack("R2");
    arguments.InsertBack("R1");

    sub.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().genRegs[0] == 1);
    arguments.Clear();

    // SUB R0, R1
    arguments.InsertBack("R0");
    arguments.InsertBack("R1");

    sub.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().genRegs[0] == 0);
    arguments.Clear();
}

////////////////////////////////
/// SubLiterals Function
////////////////////////////////
void SubLiterals()
{
    // ADD R0, R11, #0xA
    arguments.InsertBack("R0");
    arguments.InsertBack("R11");
    arguments.InsertBack("#0xA");

    sub.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().genRegs[0] == 1);
    arguments.Clear();

    // ADD R5, #0x4
    arguments.InsertBack("R5");
    arguments.InsertBack("#0x4");

    sub.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().genRegs[5] == 1);
    arguments.Clear();
}

////////////////////////////////
/// SubsTest Function
////////////////////////////////
void SubsTest()
{
    // Reset registers
    setup();

    // Set flagged
    sub.SetFlagged();

    // SUBS R10, #10
    arguments.InsertBack("R10");
    arguments.InsertBack("#10");

    sub.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().GetNegativeFlag() == false);
    assert(myProc.GetProcessRegisters().GetZeroFlag() == true);
    assert(myProc.GetProcessRegisters().GetCarryFlag() == true);
    assert(myProc.GetProcessRegisters().GetOverflowFlag() == false);
    arguments.Clear();

    // SUBS R9, #6
    arguments.InsertBack("R9");
    arguments.InsertBack("#6");

    sub.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().GetNegativeFlag() == false);
    assert(myProc.GetProcessRegisters().GetZeroFlag() == false);
    assert(myProc.GetProcessRegisters().GetCarryFlag() == true);
    assert(myProc.GetProcessRegisters().GetOverflowFlag() == false);
    arguments.Clear();

    // SUBS R10, #16
    arguments.InsertBack("R10");
    arguments.InsertBack("#16");

    sub.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().GetNegativeFlag() == true);
    assert(myProc.GetProcessRegisters().GetZeroFlag() == false);
    assert(myProc.GetProcessRegisters().GetCarryFlag() == false);
    assert(myProc.GetProcessRegisters().GetOverflowFlag() == false);
    arguments.Clear();

    // SUBS R0, #0
    arguments.InsertBack("R0");
    arguments.InsertBack("#0");

    sub.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().GetNegativeFlag() == false);
    assert(myProc.GetProcessRegisters().GetZeroFlag() == true);
    assert(myProc.GetProcessRegisters().GetCarryFlag() == true);
    assert(myProc.GetProcessRegisters().GetOverflowFlag() == false);
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

    SubRegsTest();
    SubLiterals();
    SubsTest();

    teardown();

    std::cout << "SUBInstruction Unit Test Complete: SUCCESS";
    return 0;
}