/////////////////////////////////
/// @file MemoryInstructionTestSuite.cpp
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "UnitTestSuite.hpp" // For UnitTestSuite

extern bool LdmAndStmUT();
extern bool LdrAndStrUT();
extern bool PushAndPopUT();

////////////////////////////////
/// FUNCTION NAME: main
////////////////////////////////
int main(int argc, char* argv[])
{
    UnitTestSuite memInstructionTestSuite("Memory Instruction Unit Test Suite");

    memInstructionTestSuite.AddTest(LdmAndStmUT);
    memInstructionTestSuite.AddTest(LdrAndStrUT);
    memInstructionTestSuite.AddTest(PushAndPopUT);

    return !(memInstructionTestSuite.Run());
}