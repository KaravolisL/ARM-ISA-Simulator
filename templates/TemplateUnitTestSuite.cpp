/////////////////////////////////
/// @file <NAME OF TEST SUITE>.cpp
///
/// @author <Author>
/////////////////////////////////
#define CATCH_CONFIG_RUNNER

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include <catch2/catch.hpp>

int main(int argc, char* argv[])
{
    // GLOBAL SETUP

    int result = Catch::Session().run(argc, argv);

    // GLOBAL TEARDOWN

    return result;
}
