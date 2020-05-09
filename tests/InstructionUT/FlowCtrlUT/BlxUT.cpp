/////////////////////////////////
/// @file BlxUT.cpp
///
/// @brief Unit Test for BLXInstruction
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "BLXInstruction.hpp"  // Test class
#include "SLList.hpp"
#include "InvalidSyntaxException.hpp"
#include "Process.hpp"
#include "FileIterator.hpp"

////////////////////////////////
/// Test Objects
////////////////////////////////
BLXInstruction blx = BLXInstruction();
Process myProc = Process();
SLList<std::string> arguments = SLList<std::string>();

////////////////////////////////
/// Setup Function
////////////////////////////////
void setup()
{
    myProc.GetProcessRegisters().PC = 5;
    myProc.GetProcessRegisters().LR = 10;
    myProc.GetProcessRegisters().genRegs[1] = 15;

    myProc.GetLabelDictionary().Insert("MyLabel", 20);

    std::ofstream myOStream("TestFile.txt", std::ofstream::out);
    myOStream << "Test Line";
    myOStream.close();

    Io::FileIterator* pFileIterator = new Io::FileIterator("TestFile.txt");
    myProc.SetFileIterator(pFileIterator);
}

////////////////////////////////
/// BranchExchangeAndLinkTest Function
////////////////////////////////
void BranchExchangeAndLinkTest()
{
    // BLX LR
    arguments.InsertBack("LR");

    blx.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().PC == 10);
    assert(myProc.GetProcessRegisters().LR == 6);
    arguments.Clear();

    // BLX R1
    arguments.InsertBack("R1");

    blx.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().PC == 15);
    assert(myProc.GetProcessRegisters().LR == 11);
    arguments.Clear();

    // BLX Label
    arguments.InsertBack("MyLabel");

    blx.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().PC == 20);
    assert(myProc.GetProcessRegisters().LR == 16);
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

    BranchExchangeAndLinkTest();

    teardown();

    std::cout << "BLXInstruction Unit Test Complete: SUCCESS";
    return 0;
}