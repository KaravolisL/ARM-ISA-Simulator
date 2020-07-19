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
#include "KeywordDict.hpp" // For KeywordDict
#include "MemoryApi.hpp" // For MemoryApi

// Individual unit tests
extern bool LdmAndStmUT();
extern bool LdrAndStrUT();
extern bool PushAndPopUT();

////////////////////////////////
/// FUNCTION NAME: suiteSetup
////////////////////////////////
void suiteSetup()
{
    KeywordDict::GetInstance().Initialize();

    Memory::MemoryApi::Initialize();
}

////////////////////////////////
/// FUNCTION NAME: main
////////////////////////////////
int main(int argc, char* argv[])
{
    UnitTestSuite memInstructionTestSuite("Memory Instruction Unit Test Suite");
    memInstructionTestSuite.SetSetup(suiteSetup);

    memInstructionTestSuite.AddTest(LdmAndStmUT);
    memInstructionTestSuite.AddTest(LdrAndStrUT);
    memInstructionTestSuite.AddTest(PushAndPopUT);

    return !(memInstructionTestSuite.Run());
}