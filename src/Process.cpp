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
#include "FileIterator.hpp" // For Io::FileIterator
#include "LineParser.hpp" // For Io::LineParser

////////////////////////////////
/// METHOD NAME: Process::Initialize
////////////////////////////////
void Process::Initialize(const char* filename)
{
    std::cout << filename << "\n";

    Io::FileIterator mainFileIterator(filename);

    // For every line of the file...
    while (mainFileIterator.HasNext())
    {
        // Create a line parser using the next line
        Io::LineParser lineParser(mainFileIterator.Next());

        // Determine how to handle the current line
        switch (lineParser.GetLineType())
        {
            case Io::LineParser::LineType::INCLUDE:
                break;
            case Io::LineParser::LineType::LABEL:
                break;
            case Io::LineParser::LineType::COMMENT:
            default:
                break;
        }
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