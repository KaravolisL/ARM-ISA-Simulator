/////////////////////////////////
/// @file OrrUT.cpp
///
/// @brief Unit Test for ORRInstruction
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "ORRInstruction.hpp"  // Test class
#include "SLList.hpp"
#include "Process.hpp"

////////////////////////////////
/// Test Objects
////////////////////////////////
ORRInstruction orr = ORRInstruction();
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
/// OrrRegsTest Function
////////////////////////////////
void OrrRegsTest()
{
    // ORR R0, R1, R2
    arguments.InsertBack("R0");
    arguments.InsertBack("R1");
    arguments.InsertBack("R2");

    orr.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().genRegs[0] == 3);
    arguments.Clear();

    // ORR R0, R1
    arguments.InsertBack("R0");
    arguments.InsertBack("R4");

    orr.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().genRegs[0] == 7);
    arguments.Clear();
}

////////////////////////////////
/// OrrLiterals Function
////////////////////////////////
void OrrLiterals()
{
    // ORR R0, R5, #0xF
    arguments.InsertBack("R0");
    arguments.InsertBack("R5");
    arguments.InsertBack("#0xF");

    orr.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().genRegs[0] == 15);
    arguments.Clear();

    // ORR R1, #x12
    arguments.InsertBack("R1");
    arguments.InsertBack("#0x12");

    orr.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().genRegs[1] == 0x13);
    arguments.Clear();
}

////////////////////////////////
/// OrrsTest Function
////////////////////////////////
void OrrsTest()
{
    // Reset registers
    setup();

    // Set flagged
    orr.SetFlagged();

    // ORRS R1, R2, #0x80000000
    arguments.InsertBack("R1");
    arguments.InsertBack("R2");
    arguments.InsertBack("#0x80000000");

    orr.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().GetNegativeFlag());
    arguments.Clear();

    // ORRS R0, #0
    arguments.InsertBack("R0");
    arguments.InsertBack("#0");

    orr.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().GetZeroFlag());
    assert(!myProc.GetProcessRegisters().GetNegativeFlag());
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

    OrrRegsTest();
    OrrLiterals();
    OrrsTest();

    teardown();

    std::cout << "ORRInstruction Unit Test Complete: SUCCESS";
    return 0;
}