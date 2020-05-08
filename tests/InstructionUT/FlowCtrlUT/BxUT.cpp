/////////////////////////////////
/// @file BxUT.cpp
///
/// @brief Unit Test for BXInstruction
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "BXInstruction.hpp"  // Test class
#include "SLList.hpp"
#include "InvalidSyntaxException.hpp"
#include "Process.hpp"
#include "FileIterator.hpp"

////////////////////////////////
/// Test Objects
////////////////////////////////
BXInstruction bx = BXInstruction();
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

    std::ofstream myOStream("TestFile.txt", std::ofstream::out);
    myOStream << "Test Line";
    myOStream.close();

    Io::FileIterator* pFileIterator = new Io::FileIterator("TestFile.txt");
    myProc.SetFileIterator(pFileIterator);
}

////////////////////////////////
/// BranchExchangeTest Function
////////////////////////////////
void BranchExchangeTest()
{
    // BX LR
    arguments.InsertBack("LR");

    bx.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().PC == 10);
    arguments.Clear();

    // BX R1
    arguments.InsertBack("R1");

    bx.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().PC == 15);
    arguments.Clear();

    // BX Label
    arguments.InsertBack("Label");

    try
    {
        bx.Execute(arguments, myProc);
        assert(false);
    }
    catch(const InvalidSyntaxException& e)
    {
        std::cerr << e.what() << '\n';
    }
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

    BranchExchangeTest();

    teardown();

    std::cout << "BXInstruction Unit Test Complete: SUCCESS";
    return 0;
}