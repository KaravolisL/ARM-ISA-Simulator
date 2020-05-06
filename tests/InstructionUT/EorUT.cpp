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
    // EOR R0, R5, R7
    arguments.InsertBack("R0");
    arguments.InsertBack("R5");
    arguments.InsertBack("R7");

    eor.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().genRegs[0] == 2);
    arguments.Clear();

    // EOR R8, R9
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
    // EOR R0, R5, #0xF
    arguments.InsertBack("R0");
    arguments.InsertBack("R5");
    arguments.InsertBack("#0xF");

    eor.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().genRegs[0] == 10);
    arguments.Clear();

    // EOR R1, #0x13
    arguments.InsertBack("R1");
    arguments.InsertBack("#0x13");

    eor.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().genRegs[1] == 0x12);
    arguments.Clear();
}

////////////////////////////////
/// EorsTest Function
////////////////////////////////
void EorsTest()
{
    // Reset registers
    setup();

    // Set flagged
    eor.SetFlagged();

    // EORS R1, R1
    arguments.InsertBack("R1");
    arguments.InsertBack("R1");

    eor.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().GetZeroFlag());
    assert(!myProc.GetProcessRegisters().GetNegativeFlag());
    arguments.Clear();

    // EORS R2, #0xFFFFFFFF
    arguments.InsertBack("R2");
    arguments.InsertBack("#0xFFFFFFFF");

    eor.Execute(arguments, myProc);

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

    EorRegsTest();
    EorLiterals();
    EorsTest();

    teardown();

    std::cout << "ORRInstruction Unit Test Complete: SUCCESS";
    return 0;
}