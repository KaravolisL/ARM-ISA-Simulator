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
    // BIC R0, R5, R1
    arguments.InsertBack("R0");
    arguments.InsertBack("R5");
    arguments.InsertBack("R1");

    bic.Execute(arguments, myProc, false);

    assert(myProc.GetProcessRegisters().genRegs[0] == 0b0100);
    arguments.Clear();

    // BIC R7, R9
    arguments.InsertBack("R7"); // 0b0111
    arguments.InsertBack("R9"); // 0b1001

    bic.Execute(arguments, myProc, false);

    assert(myProc.GetProcessRegisters().genRegs[7] == 0b0110);
    arguments.Clear();
}

////////////////////////////////
/// BicLiterals Function
////////////////////////////////
void BicLiterals()
{
    // BIC R0, R5, #0xB
    arguments.InsertBack("R0");
    arguments.InsertBack("R5"); // 0b0101
    arguments.InsertBack("#0xB"); // 0b1011

    bic.Execute(arguments, myProc, false);

    assert(myProc.GetProcessRegisters().genRegs[0] == 0b0100);
    arguments.Clear();

    // BIC R10, #xF
    arguments.InsertBack("R10");
    arguments.InsertBack("#0xF");

    bic.Execute(arguments, myProc, false);

    assert(myProc.GetProcessRegisters().genRegs[10] == 0x0);
    arguments.Clear();
}

////////////////////////////////
/// BicsTest Function
////////////////////////////////
void BicsTest()
{
    // Reset registers
    setup();

    // BICS R1, R1
    arguments.InsertBack("R1");
    arguments.InsertBack("R1");

    bic.Execute(arguments, myProc, true);

    assert(myProc.GetProcessRegisters().GetZeroFlag());
    assert(!myProc.GetProcessRegisters().GetNegativeFlag());
    arguments.Clear();

    // "MOV" R5, #0xFFFFFFFF
    myProc.GetProcessRegisters().genRegs[5] = 0xFFFFFFFF;

    // BICS R5, #0xF
    arguments.InsertBack("R5");
    arguments.InsertBack("#0xF");

    bic.Execute(arguments, myProc, true);

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

    BicRegsTest();
    BicLiterals();
    BicsTest();

    teardown();

    std::cout << "BICInstruction Unit Test Complete: SUCCESS";
    return 0;
}