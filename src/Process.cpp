/////////////////////////////////
/// @file Process.cpp
///
/// @brief Implementation of Process class
///
/// @copydetail Process 
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "Process.hpp"  // Header for class
#include "FileParser.hpp" // For Io::FileParser
#include "LineTypes.hpp" // For Io::LineType enum

////////////////////////////////
/// METHOD NAME: Process::Initialize
////////////////////////////////
void Process::Initialize(const char* filename)
{
    std::cout << filename << "\n";

    Io::FileParser fileParser(filename);

    switch (fileParser.CurrentLineType())
    {
        case Io::LineType::INCLUDE:
            break;
        default:
            break;
    }
}

////////////////////////////////
/// METHOD NAME: Process::Execute
////////////////////////////////
void Process::Execute()
{
    
}

////////////////////////////////
/// METHOD NAME: Process::Step
////////////////////////////////
void Process::Step()
{
    
}