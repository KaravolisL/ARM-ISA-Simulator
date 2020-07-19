/////////////////////////////////
/// @file <TEST SUITE NAME>.cpp
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "UnitTestSuite.hpp" // For UnitTestSuite

// Individual unit tests
extern bool nameOfUnitTest();

////////////////////////////////
/// FUNCTION NAME: main
////////////////////////////////
int main(int argc, char* argv[])
{
    UnitTestSuite nameOfTestSuite("<TEST SUITE NAME> Unit Test Suite");

    nameOfTestSuite.AddTest(nameOfUnitTest);

    return !(nameOfTestSuite.Run());
}