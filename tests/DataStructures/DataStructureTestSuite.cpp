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
extern bool HashMapUT();
extern bool ListUT();
extern bool StackUT();

////////////////////////////////
/// FUNCTION NAME: main
////////////////////////////////
int main(int argc, char* argv[])
{
    UnitTestSuite dataStructureTestSuite("Data Structure Unit Test Suite");

    dataStructureTestSuite.AddTest(HashMapUT);
    dataStructureTestSuite.AddTest(ListUT);
    dataStructureTestSuite.AddTest(StackUT);

    return !(dataStructureTestSuite.Run());
}