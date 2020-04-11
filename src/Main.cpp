/////////////////////////////////
/// @file Main.cpp
///
/// @brief Implementation of main
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "Process.hpp"  // For Process

////////////////////////////////
/// FUNCTION NAME: main
////////////////////////////////
int main(int argc, char* argv[])
{
    // Create empty Process
    Process process = Process();

    process.Execute();

    return 0;
}