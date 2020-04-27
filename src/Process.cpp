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
#include <string.h>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "Assert.hpp"
#include "Process.hpp"  // Header for class
#include "FileIterator.hpp" // For Io::FileIterator
#include "LineParser.hpp" // For Io::LineParser
#include "LineTypes.hpp" // For Io::LineTypes enum
#include "Logger.hpp" // For Logger class

////////////////////////////////
/// METHOD NAME: Process::Initialize
////////////////////////////////
void Process::Initialize(const char* filename)
{
    LOG_INFO(filename);

    Io::FileIterator fileIterator(filename);

    // For every line of the file...
    while (fileIterator.HasNext())
    {
        // Create a line parser using the next line
        Io::LineParser lineParser(fileIterator.Next());
        LOG_DEBUG(lineParser.GetLine());

        // Determine how to handle the current line
        switch (lineParser.GetLineType())
        {
            case Io::LineType::INCLUDE:
            {
                std::string newFileName;
                lineParser.GetFileName(newFileName);
                // Recurse on the include file
                Initialize(newFileName.c_str());
                break;
            }
            case Io::LineType::EQU:
            {
                std::string constantName;
                lineParser.GetLabel(constantName);

                // We pass the constants dictionary in case it is already a constant
                int value = lineParser.GetValue(m_constantsDictionary);

                m_constantsDictionary.Insert(constantName, value);
                break;
            }
            case Io::LineType::LABEL:
            {
                std::string label;
                lineParser.GetLabel(label);

                LOG_DEBUG(label);

                // Check if the label was already defined
                if (m_labelDictionary.Contains(label))
                {
                    // TODO: Throw labeled redefinition exception
                }

                m_labelDictionary.Insert(label, fileIterator.GetLineNumber());
            }
            case Io::LineType::COMMENT:
            case Io::LineType::INSTRUCTION:
            case Io::LineType::AREA:
            case Io::LineType::EXPORT:
            case Io::LineType::END:
            case Io::LineType::ENTRY:
            case Io::LineType::ALIGN:
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