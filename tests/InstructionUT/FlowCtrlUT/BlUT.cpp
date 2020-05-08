/////////////////////////////////
/// @file BlUT.cpp
///
/// @brief Unit Test for BLInstruction
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "BLInstruction.hpp"  // Test class
#include "SLList.hpp"
#include "InvalidSyntaxException.hpp"
#include "Process.hpp"
#include "FileIterator.hpp"

////////////////////////////////
/// Test Objects
////////////////////////////////
BLInstruction bl = BLInstruction();
Process myProc = Process();
SLList<std::string> arguments = SLList<std::string>();

////////////////////////////////
/// Setup Function
////////////////////////////////
void setup()
{
    myProc.GetProcessRegisters().PC = 5;

    myProc.GetLabelDictionary().Insert("MyLabel", 10);

    std::ofstream myOStream("TestFile.txt", std::ofstream::out);
    myOStream << "Test Line";
    myOStream.close();

    Io::FileIterator* pFileIterator = new Io::FileIterator("TestFile.txt");
    myProc.SetFileIterator(pFileIterator);
}

////////////////////////////////
/// BranchAndLinkTest Function
////////////////////////////////
void BranchAndLinkTest()
{
    // BL MyLabel
    arguments.InsertBack("MyLabel");

    bl.Execute(arguments, myProc);

    assert(myProc.GetProcessRegisters().PC == 10);
    assert(myProc.GetProcessRegisters().LR == 6);
    arguments.Clear();

    // BL BadLabel
    arguments.InsertBack("BadLabel");

    try
    {
        bl.Execute(arguments, myProc);
        assert(false);
    }
    catch (const InvalidSyntaxException& e)
    {
        std::cout << e.what();
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

    BranchAndLinkTest();

    teardown();

    std::cout << "BLInstruction Unit Test Complete: SUCCESS";
    return 0;
}