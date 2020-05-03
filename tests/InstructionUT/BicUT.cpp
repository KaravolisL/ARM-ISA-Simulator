/////////////////////////////////
/// @file BicUT.cpp
///
/// @brief Unit Test for BICInstruction
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "BICInstruction.hpp"  // Test class
#include "SLList.hpp"
#include "Process.hpp"

////////////////////////////////
/// Test Objects
////////////////////////////////
BICInstruction bic = BICInstruction();
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
/// BicRegsTest Function
////////////////////////////////
void BicRegsTest()
{
    // ORR R0, R5, R1
    arguments.InsertBack("R0");
    arguments.InsertBack("R5");
    arguments.InsertBack("R1");

    bic.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().genRegs[0] == 0b0100);
    arguments.Clear();

    // ORR R7, R9
    arguments.InsertBack("R7"); // 0b0111
    arguments.InsertBack("R9"); // 0b1001

    bic.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().genRegs[7] == 0b0110);
    arguments.Clear();
}

////////////////////////////////
/// BicLiterals Function
////////////////////////////////
void BicLiterals()
{
    // ADD R0, R5, #0xA
    arguments.InsertBack("R0");
    arguments.InsertBack("R5"); // 0b0101
    arguments.InsertBack("#0xB"); // 0b1011

    bic.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().genRegs[0] == 0b0100);
    arguments.Clear();

    // ADD R10, #xF
    arguments.InsertBack("R10");
    arguments.InsertBack("#0xF");

    bic.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().genRegs[10] == 0x0);
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

    BicRegsTest();
    BicLiterals();

    teardown();

    std::cout << "BICInstruction Unit Test Complete: SUCCESS";
    return 0;
}