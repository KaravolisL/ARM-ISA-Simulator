/////////////////////////////////
/// @file DataStructureTestSuite.cpp
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "UnitTestSuite.hpp" // For UnitTestSuite

// Individual unit tests
extern bool StackUT();
extern bool HashMapUT();

////////////////////////////////
/// FUNCTION NAME: main
////////////////////////////////
int main(int argc, char* argv[])
{
    UnitTestSuite dataStructureTestSuite("Data Structure Unit Test Suite");

    dataStructureTestSuite.AddTest(StackUT);
    dataStructureTestSuite.AddTest(HashMapUT);

    return !(dataStructureTestSuite.Run());
}