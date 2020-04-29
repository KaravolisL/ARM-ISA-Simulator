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
#include "KeywordDict.hpp" // For KeywordDict class

////////////////////////////////
/// FUNCTION NAME: main
////////////////////////////////
int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Invalid command line arguments";
        exit(EXIT_FAILURE);
    }

    // Initialize the keyword dictionary
    KeywordDict::GetInstance().Initialize();

    // Create empty Process in heap
    Process* pProcess = new Process();

    // Initalize the process using the given file
    pProcess->Initialize(argv[1]);

    // Prepare the process for execution
    pProcess->PrepareForExecution(argv[1]);

    pProcess->Step();
    pProcess->Step();
    pProcess->Step();

    return 0;
}