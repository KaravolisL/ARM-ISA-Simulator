/////////////////////////////////
/// @file ProcessInitializer.cpp
///
/// @brief Implementation of ProcessInitializer class
///
/// @copydetail ProcessInitializer 
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "ProcessInitializer.hpp" // Header for class
#include "AssemblingException.hpp" // For AssemblingException
#include "FileIterator.hpp" // For Io::FileIterator
#include "MemoryConstants.hpp" // For MemoryConstants
#include "LineParser.hpp" // For Io::LineParser
#include "Process.hpp" // For Process
#include "MemoryApi.hpp" // For Memory::MemoryApi
#include "Logger.hpp" // For Logger

////////////////////////////////
/// METHOD NAME: ProcessInitializer::Initialize
////////////////////////////////
void ProcessInitializer::Initialize(const char* fileName) const
{
    // Run through the main file first and initialize
    InitializeFile(fileName);

    // Initialize the PC
    try
    {
        m_pProcess->m_processRegisters.PC = m_pProcess->m_labelDictionary.Get("__main");
    }
    catch(const DLB<uint32_t>::KeyNotFoundException& e)
    {
        throw AssemblingException("No __main label");
    }

    // Create the file iterator and send it to the line of the pc
    m_pProcess->m_pFileIterator = new Io::FileIterator(fileName);
    m_pProcess->m_pFileIterator->GoToLine(m_pProcess->m_processRegisters.PC);

    // Initialize the stack pointer
    // Note: Stack is full descending
    m_pProcess->m_processRegisters.SP = Memory::STACK_LOWER_BOUND;
}

////////////////////////////////
/// METHOD NAME: ProcessInitializer::InitializeFile
////////////////////////////////
void ProcessInitializer::InitializeFile(const char* fileName) const
{
    LOG_INFO("Initializing file %s", fileName);
    Io::FileIterator fileIterator(fileName);

    // For every line of the file...
    while (fileIterator.HasNext())
    {
        // Create a line parser using the next line
        Io::LineParser lineParser(&fileIterator.Next());

        // Determine how to handle the current line
        switch (lineParser.GetLineType())
        {
            case Io::LineType::INCLUDE:
            {
                std::string newFileName;
                lineParser.GetFileName(newFileName);
                // Recurse on the include file
                InitializeFile(newFileName.c_str());
                break;
            }
            case Io::LineType::EQU:
            {
                std::string constantName;
                lineParser.GetLabel(constantName);

                // We pass the constants dictionary in case it is already a constant
                int value = lineParser.GetValue(m_pProcess->m_constantsDictionary);

                m_pProcess->m_constantsDictionary.Insert(constantName, value);
                break;
            }
            case Io::LineType::LABEL:
            case Io::LineType::LABEL_AND_INSTRUCTION:
            case Io::LineType::LABEL_AND_PROC:
            {
                std::string label;
                lineParser.GetLabel(label);

                // Check if the label was already defined
                if (m_pProcess->m_labelDictionary.Contains(label))
                {
                    throw AssemblingException("Label Redefinition Error", *(lineParser.GetLine()), fileIterator.GetLineNumber());
                }

                m_pProcess->m_labelDictionary.Insert(label, fileIterator.GetLineNumber());
                break;
            }
            case Io::LineType::DCD:
            case Io::LineType::DCB:
            {
                HandleMemoryDirective(lineParser);
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

    LOG_INFO("Initialization of %s Complete", fileName);
}

////////////////////////////////
/// METHOD NAME: ProcessInitializer::HandleMemoryDirective
////////////////////////////////
void ProcessInitializer::HandleMemoryDirective(Io::LineParser& rLineParser) const
{
    // Next memory address to which to write constants
    static uint32_t nextMemoryAddress = Memory::GLOBAL_LOWER_BOUND;

    // Write the word to memory and store the label in the dictionary
    LOG_DEBUG(rLineParser.GetLine()->c_str());
    LOG_DEBUG(rLineParser.GetLabel().c_str());
    Memory::MemoryApi::WriteWord(nextMemoryAddress, rLineParser.GetValue(m_pProcess->m_constantsDictionary));
    m_pProcess->m_labelDictionary.Insert(rLineParser.GetLabel(), nextMemoryAddress);

    nextMemoryAddress += 4;
}

