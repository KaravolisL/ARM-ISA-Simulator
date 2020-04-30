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

    myProc.GetConstantsDictionary().Insert("MY_CONSTANT", 10);
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

    add.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().genRegs[0] == 3);
    arguments.Clear();

    // ADD R0, R1
    arguments.InsertBack("R0");
    arguments.InsertBack("R1");

    add.Execute(arguments, myProc);

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

    add.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().genRegs[0] == 11);
    arguments.Clear();

    // ADD R0, #x11
    arguments.InsertBack("R1");
    arguments.InsertBack("#0x11");

    add.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().genRegs[1] == 18);
    arguments.Clear();
}

////////////////////////////////
/// AddConstants Function
////////////////////////////////
void AddConstants()
{
    // ADD R0, R2, =MY_CONSTANT
    arguments.InsertBack("R0");
    arguments.InsertBack("R2");
    arguments.InsertBack("=MY_CONSTANT");

    add.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().genRegs[0] == 12);
    arguments.Clear();

    // ADD r0, =MY_CONSTANT
    arguments.InsertBack("R0");
    arguments.InsertBack("=MY_CONSTANT");

    add.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().genRegs[0] == 22);
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
    AddConstants();

    teardown();

    std::cout << "ADDInstruction Unit Test Complete: SUCCESS";
    return 0;
}