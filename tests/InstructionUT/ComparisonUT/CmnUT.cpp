/////////////////////////////////
/// @file CmnUT.cpp
///
/// @brief Unit Test for CMNInstruction
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "CMNInstruction.hpp"  // Test class
#include "SLList.hpp"
#include "Process.hpp"

////////////////////////////////
/// Test Objects
////////////////////////////////
CMNInstruction cmn = CMNInstruction();
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
/// CmnTest Function
////////////////////////////////
void CmnTest()
{
    // CMN R0, R0
    arguments.InsertBack("R0");
    arguments.InsertBack("R0");

    cmn.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().GetZeroFlag());
    assert(!myProc.GetProcessRegisters().GetNegativeFlag());
    assert(!myProc.GetProcessRegisters().GetCarryFlag());
    assert(!myProc.GetProcessRegisters().GetOverflowFlag());
    arguments.Clear();

    // CMN R0, #-2
    arguments.InsertBack("R0");
    arguments.InsertBack("#-2");

    cmn.Execute(arguments, myProc);

    assert(!myProc.GetProcessRegisters().GetZeroFlag());
    assert(myProc.GetProcessRegisters().GetNegativeFlag());
    assert(!myProc.GetProcessRegisters().GetCarryFlag());
    assert(!myProc.GetProcessRegisters().GetOverflowFlag());
    arguments.Clear();

    // CMN R10, #0xFFFFFFFF
    arguments.InsertBack("R10");
    arguments.InsertBack("#0xFFFFFFFF");

    cmn.Execute(arguments, myProc);

    assert(!myProc.GetProcessRegisters().GetZeroFlag());
    assert(!myProc.GetProcessRegisters().GetNegativeFlag());
    assert(myProc.GetProcessRegisters().GetCarryFlag());
    assert(!myProc.GetProcessRegisters().GetOverflowFlag());
    arguments.Clear();

    // "MOV" R1, #0x40000000
    myProc.GetProcessRegisters().genRegs[1] = 0x40000000;

    // CMN R1, #0x40000000
    arguments.InsertBack("R1");
    arguments.InsertBack("#0x40000000");

    cmn.Execute(arguments, myProc);

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

    CmnTest();

    teardown();

    std::cout << "CMNInstruction Unit Test Complete: SUCCESS";
    return 0;
}