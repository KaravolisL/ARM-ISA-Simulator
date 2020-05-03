/////////////////////////////////
/// @file EorUT.cpp
///
/// @brief Unit Test for EORInstruction
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "EORInstruction.hpp"  // Test class
#include "SLList.hpp"
#include "Process.hpp"

////////////////////////////////
/// Test Objects
////////////////////////////////
EORInstruction eor = EORInstruction();
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
/// EorRegsTest Function
////////////////////////////////
void EorRegsTest()
{
    // ORR R0, R1, R2
    arguments.InsertBack("R0");
    arguments.InsertBack("R5");
    arguments.InsertBack("R7");

    eor.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().genRegs[0] == 2);
    arguments.Clear();

    // ORR R0, R1
    arguments.InsertBack("R8");
    arguments.InsertBack("R9");

    eor.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().genRegs[8] == 1);
    arguments.Clear();
}

////////////////////////////////
/// EorLiterals Function
////////////////////////////////
void EorLiterals()
{
    // ADD R0, R1, #0xA
    arguments.InsertBack("R0");
    arguments.InsertBack("R5");
    arguments.InsertBack("#0xF");

    eor.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().genRegs[0] == 10);
    arguments.Clear();

    // ADD R0, #x11
    arguments.InsertBack("R1");
    arguments.InsertBack("#0x13");

    eor.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().genRegs[1] == 0x12);
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

    EorRegsTest();
    EorLiterals();

    teardown();

    std::cout << "ORRInstruction Unit Test Complete: SUCCESS";
    return 0;
}