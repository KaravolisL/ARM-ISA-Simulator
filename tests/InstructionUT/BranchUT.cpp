/////////////////////////////////
/// @file BranchUT.cpp
///
/// @brief Unit Test for BInstruction
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "BInstruction.hpp"  // Test class
#include "SLList.hpp"
#include "InvalidSyntaxException.hpp"
#include "Process.hpp"
#include "FileIterator.hpp"

////////////////////////////////
/// Test Objects
////////////////////////////////
BInstruction branch = BInstruction();
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
/// BranchTest Function
////////////////////////////////
void BranchTest()
{
    // B MyLabel
    arguments.InsertBack("MyLabel");

    branch.Execute(arguments, myProc, false);

    assert(myProc.GetProcessRegisters().PC == 10);
    arguments.Clear();

    // B BadLabel
    arguments.InsertBack("BadLabel");

    try
    {
        branch.Execute(arguments, myProc, false);
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

    BranchTest();

    teardown();

    std::cout << "BInstruction Unit Test Complete: SUCCESS";
    return 0;
}