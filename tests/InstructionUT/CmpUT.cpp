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
#include "CMPInstruction.hpp"  // Test class
#include "SLList.hpp"
#include "Process.hpp"

////////////////////////////////
/// Test Objects
////////////////////////////////
CMPInstruction cmp = CMPInstruction();
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
/// CompareTest Function
////////////////////////////////
void CompareTest()
{
    // CMP R10, #10
    arguments.InsertBack("R10");
    arguments.InsertBack("#10");

    cmp.Execute(arguments, myProc, false);

    assert(myProc.GetProcessRegisters().GetNegativeFlag() == false);
    assert(myProc.GetProcessRegisters().GetZeroFlag() == true);
    assert(myProc.GetProcessRegisters().GetCarryFlag() == true);
    assert(myProc.GetProcessRegisters().GetOverflowFlag() == false);
    arguments.Clear();

    // CMP R10, #6
    arguments.InsertBack("R10");
    arguments.InsertBack("#6");

    cmp.Execute(arguments, myProc, false);

    assert(myProc.GetProcessRegisters().GetNegativeFlag() == false);
    assert(myProc.GetProcessRegisters().GetZeroFlag() == false);
    assert(myProc.GetProcessRegisters().GetCarryFlag() == true);
    assert(myProc.GetProcessRegisters().GetOverflowFlag() == false);
    arguments.Clear();

    // CMP R10, #16
    arguments.InsertBack("R10");
    arguments.InsertBack("#16");

    cmp.Execute(arguments, myProc, false);

    assert(myProc.GetProcessRegisters().GetNegativeFlag() == true);
    assert(myProc.GetProcessRegisters().GetZeroFlag() == false);
    assert(myProc.GetProcessRegisters().GetCarryFlag() == false);
    assert(myProc.GetProcessRegisters().GetOverflowFlag() == false);
    arguments.Clear();

    // CMP R0, #0
    arguments.InsertBack("R0");
    arguments.InsertBack("#0");

    cmp.Execute(arguments, myProc, false);

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

    CompareTest();

    teardown();

    std::cout << "CMPInstruction Unit Test Complete: SUCCESS";
    return 0;
}