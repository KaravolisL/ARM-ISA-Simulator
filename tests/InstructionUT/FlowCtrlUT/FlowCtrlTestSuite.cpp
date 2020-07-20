/////////////////////////////////
/// @file FlowCtrlTestSuite.cpp
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <iostream>
#include <fstream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "UnitTestSuite.hpp" // For UnitTestSuite
#include "KeywordDict.hpp"

// Individual unit tests
extern bool BlUT();
extern bool BlxUT();
extern bool BranchUT();
extern bool BxUT();

////////////////////////////////
/// FUNCTION NAME: suiteSetup
////////////////////////////////
void suiteSetup()
{
    std::ofstream myOStream("TestFile.txt", std::ofstream::out);
    myOStream << "Test Line";
    myOStream.close();

    KeywordDict::GetInstance().Initialize();
}

////////////////////////////////
/// FUNCTION NAME: main
////////////////////////////////
int main(int argc, char* argv[])
{
    UnitTestSuite flowCtrlTestSuite("Flow Control Instructions Unit Test Suite");
    flowCtrlTestSuite.SetSetup(suiteSetup);

    flowCtrlTestSuite.AddTest(BlUT);
    flowCtrlTestSuite.AddTest(BlxUT);
    flowCtrlTestSuite.AddTest(BranchUT);
    flowCtrlTestSuite.AddTest(BxUT);

    return !(flowCtrlTestSuite.Run());
}