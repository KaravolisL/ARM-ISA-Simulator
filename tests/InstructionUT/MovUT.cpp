/////////////////////////////////
/// @file MovUT.cpp
///
/// @brief Unit Test for MOVInstruction
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "MOVInstruction.hpp"  // Test class
#include "SLList.hpp"
#include "Process.hpp"

////////////////////////////////
/// Test Objects
////////////////////////////////
MOVInstruction mov = MOVInstruction();
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
/// MovRegTest Function
////////////////////////////////
void MovRegTest()
{
    // MOV R0, R1
    arguments.InsertBack("R0");
    arguments.InsertBack("R1");

    mov.Execute(arguments, myProc, false);

    assert(myProc.GetProcessRegisters().genRegs[0] == 1);
    arguments.Clear();
}

////////////////////////////////
/// MovLiteralTest Function
////////////////////////////////
void MovLiteralTest()
{
    // MOV R0, #0xFF
    arguments.InsertBack("R0");
    arguments.InsertBack("#0xFF");

    mov.Execute(arguments, myProc, false);

    assert(myProc.GetProcessRegisters().genRegs[0] == 0xFF);
    arguments.Clear();
}

////////////////////////////////
/// MovsTest Function
////////////////////////////////
void MovsTest()
{
    // MOVS R0, #0
    arguments.InsertBack("R0");
    arguments.InsertBack("#0");

    mov.Execute(arguments, myProc, true);

    assert(myProc.GetProcessRegisters().GetZeroFlag());
    assert(!myProc.GetProcessRegisters().GetNegativeFlag());
    arguments.Clear();

    // MOVS R0, #0xFFFFFFFF
    arguments.InsertBack("R0");
    arguments.InsertBack("#0xFFFFFFFF");

    mov.Execute(arguments, myProc, true);

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

    MovRegTest();
    MovLiteralTest();
    MovsTest();

    teardown();

    std::cout << "MOVInstruction Unit Test Complete: SUCCESS";
    return 0;
}