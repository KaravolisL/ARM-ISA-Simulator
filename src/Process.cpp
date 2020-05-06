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
#include "Process.hpp"  // Header for class
#include "FileIterator.hpp" // For Io::FileIterator
#include "InstructionBase.hpp" // For InstructionBase
#include "InstructionRepository.hpp" // For InstructionRepository
#include "LineParser.hpp" // For Io::LineParser
#include "LineTypes.hpp" // For Io::LineTypes enum
#include "AssemblingException.hpp" // For AssemblingException
#include "Logger.hpp" // For Logger class

////////////////////////////////
/// METHOD NAME: Process::Initialize
////////////////////////////////
void Process::Initialize(const char* filename)
{
    LOG_INFO("Initializing file %s", filename);

    Io::FileIterator fileIterator(filename);

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

                // Check if the label was already defined
                if (m_labelDictionary.Contains(label))
                {
                    throw AssemblingException("Label Redefinition Error", *(lineParser.GetLine()), fileIterator.GetLineNumber());
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

    LOG_INFO("Initialization of %s Complete", filename);
}

////////////////////////////////
/// METHOD NAME: Process::PrepareForExecution
////////////////////////////////
void Process::PrepareForExecution(const char* filename)
{
    // Initialize the PC
    try
    {
        m_processRegisters.PC = m_labelDictionary.Get("__main");
    }
    catch(const DLB<uint32_t>::KeyNotFoundException& e)
    {
        throw AssemblingException("No __main label");
    }

    // Create the file iterator and send it to the line of the pc
    m_pFileIterator = new Io::FileIterator(filename);
    m_pFileIterator->GoToLine(m_processRegisters.PC);
}

////////////////////////////////
/// METHOD NAME: Process::Execute
////////////////////////////////
void Process::Execute()
{
    while (this->Step()) {}
}

////////////////////////////////
/// METHOD NAME: Process::Step
////////////////////////////////
bool Process::Step()
{
    // Move to the next instruction
    Io::LineParser lineParser(&m_pFileIterator->Next());
    while (lineParser.GetLineType() != Io::LineType::INSTRUCTION)
    {
        if (lineParser.GetLineType() == Io::LineType::ENDP) return false;
        lineParser.SetLine(&m_pFileIterator->Next());
    }

    LOG_DEBUG("Executing %s", m_pFileIterator->GetCurrentLine().c_str());

    std::string instruction;
    lineParser.GetInstruction(instruction);

    InstructionBase* pInstruction = InstructionRepository::GetInstance().GetInstruction(instruction, *this);

    SLList<std::string> arguments;
    lineParser.GetArguments(arguments);

    pInstruction->Execute(arguments, *this);
    return true;
}