/////////////////////////////////
/// @file MemoryTestSuite.cpp
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
#include "MemoryApi.hpp" // For MemoryApi

int main(int argc, char* argv[])
{
    Memory::MemoryApi::Initialize();

    int result = Catch::Session().run(argc, argv);

    Memory::MemoryApi::Close();

    return result;
}
