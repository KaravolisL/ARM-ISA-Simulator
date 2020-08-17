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
#include "Assert.hpp" // For ASSERT
#include "FileIterator.hpp" // For Io::FileIterator
#include "MemoryConstants.hpp" // For MemoryConstants
#include "LineParser.hpp" // For Io::LineParser
#include "List.hpp" // For List
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

                // We need to add the path to the filename before recursing
                std::string originalFileName = std::string(fileName);
                std::string path = originalFileName.substr(0, originalFileName.rfind('/') + 1);
                newFileName = path + newFileName;

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
            case Io::LineType::ALIGN:
            {
                HandleMemoryDirective(lineParser);
            }
            case Io::LineType::COMMENT:
            case Io::LineType::INSTRUCTION:
            case Io::LineType::AREA:
            case Io::LineType::EXPORT:
            case Io::LineType::END:
            case Io::LineType::ENTRY:
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

    LOG_DEBUG("Handling %s", rLineParser.GetLine()->c_str());

    std::string memLabel = rLineParser.GetLabel();

    switch (rLineParser.GetLineType())
    {
        case Io::LineType::ALIGN:
        {
            LOG_DEBUG("Aligning memory to word boundary");
            nextMemoryAddress += (Memory::WORD_SIZE_IN_BYTES - (nextMemoryAddress % Memory::WORD_SIZE_IN_BYTES));
            break;
        }
        case Io::LineType::DCD:
        {
            List<uint32_t> values;
            rLineParser.GetValues<uint32_t>(m_pProcess->m_constantsDictionary, values);

            LOG_DEBUG("Label = %s, Address = %x, Values = %s", memLabel.c_str(), nextMemoryAddress, values.ToString().c_str());

            // Only add the label for the first entry
            m_pProcess->m_labelDictionary.Insert(memLabel, nextMemoryAddress);
            for (uint32_t i = 0; i < values.GetLength(); i++)
            {
                // Write the word to memory
                Memory::MemoryApi::WriteWord(nextMemoryAddress, values[i]);
                nextMemoryAddress += Memory::WORD_SIZE_IN_BYTES;
            }
            break;
        }
        case Io::LineType::DCB:
        {
            List<int8_t> values;
            rLineParser.GetValues<int8_t>(m_pProcess->m_constantsDictionary, values);

            LOG_DEBUG("Label = %s, Address = %x, Values = %s", memLabel.c_str(), nextMemoryAddress, values.ToString().c_str());

            // Only add the label for the first entry
            m_pProcess->m_labelDictionary.Insert(memLabel, nextMemoryAddress);
            for (uint32_t i = 0; i < values.GetLength(); i++)
            {
                Memory::MemoryApi::WriteUnsignedByte(nextMemoryAddress++, values[i]);
            }
            break;
        }
        default:
            ASSERT(false, "Unsupported line type %d", rLineParser.GetLineType());
    }

    if ((nextMemoryAddress % Memory::WORD_SIZE_IN_BYTES) != 0)
    {
        LOG_INFO("Warning: Memory is not word aligned. nextMemoryAddress = %x", nextMemoryAddress);
    }
}

