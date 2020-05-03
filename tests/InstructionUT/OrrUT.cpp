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
    // ADD R0, R1, #0xA
    arguments.InsertBack("R0");
    arguments.InsertBack("R5");
    arguments.InsertBack("#0xF");

    orr.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().genRegs[0] == 15);
    arguments.Clear();

    // ADD R0, #x11
    arguments.InsertBack("R1");
    arguments.InsertBack("#0x12");

    orr.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().genRegs[1] == 0x13);
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

    teardown();

    std::cout << "ORRInstruction Unit Test Complete: SUCCESS";
    return 0;
}