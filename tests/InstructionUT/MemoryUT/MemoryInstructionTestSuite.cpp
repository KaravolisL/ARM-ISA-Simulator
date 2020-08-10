/////////////////////////////////
/// @file MemoryInstructionTestSuite.cpp
///
/// @author Luke Karavolis
/////////////////////////////////
#define CATCH_CONFIG_RUNNER

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include <catch2/catch.hpp>
#include "KeywordDict.hpp" // For KeywordDict
#include "MemoryApi.hpp" // For MemoryApi

int main(int argc, char* argv[])
{
    KeywordDict::GetInstance().Initialize();

    Memory::MemoryApi::Initialize();

    int result = Catch::Session().run(argc, argv);

    return result;
}
