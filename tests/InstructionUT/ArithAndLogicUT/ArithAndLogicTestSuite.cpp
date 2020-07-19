/////////////////////////////////
/// @file ArithAndLogicTestSuite.cpp
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "UnitTestSuite.hpp" // For UnitTestSuite
#include "KeywordDict.hpp" // For KeywordDict

// Individual unit tests
extern bool AddUT();
extern bool AndUT();
extern bool BicUT();
extern bool CmnUT();
extern bool CmpUT();
extern bool EorUT();
extern bool LslUT();
extern bool LsrUT();
extern bool MovUT();
extern bool OrrUT();
extern bool SubUT();

////////////////////////////////
/// FUNCTION NAME: suiteSetup
////////////////////////////////
void suiteSetup()
{
    KeywordDict::GetInstance().Initialize();
}

////////////////////////////////
/// FUNCTION NAME: main
////////////////////////////////
int main(int argc, char* argv[])
{
    UnitTestSuite arithAndLogicTestSuite("Arithmetic And Logic Instructions Unit Test Suite");
    arithAndLogicTestSuite.SetSetup(suiteSetup);

    arithAndLogicTestSuite.AddTest(AddUT);
    arithAndLogicTestSuite.AddTest(AndUT);
    arithAndLogicTestSuite.AddTest(BicUT);
    arithAndLogicTestSuite.AddTest(CmnUT);
    arithAndLogicTestSuite.AddTest(CmpUT);
    arithAndLogicTestSuite.AddTest(EorUT);
    arithAndLogicTestSuite.AddTest(LslUT);
    arithAndLogicTestSuite.AddTest(LsrUT);
    arithAndLogicTestSuite.AddTest(MovUT);
    arithAndLogicTestSuite.AddTest(OrrUT);
    arithAndLogicTestSuite.AddTest(SubUT);

    return !(arithAndLogicTestSuite.Run());
}