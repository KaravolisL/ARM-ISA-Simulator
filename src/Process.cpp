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
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "Process.hpp"  // Header for class
#include "ProcessInitializer.hpp" // For ProcessInitializer
#include "FileIterator.hpp" // For Io::FileIterator
#include "InstructionBase.hpp" // For InstructionBase
#include "LineParser.hpp" // For Io::LineParser
#include "Logger.hpp" // For Logger class
#include "InstructionBuilder.hpp" // For InstructionBuilder

/////////////////////////////////////
/// Deconstructor
/////////////////////////////////////
Process::~Process()
{
    delete m_pFileIterator;
}

////////////////////////////////
/// METHOD NAME: Process::Initialize
////////////////////////////////
void Process::Initialize(const char* fileName)
{
    // Create a process initializer and use it to prepare the process
    ProcessInitializer processInitializer(this);
    processInitializer.Initialize(fileName);
}

////////////////////////////////
/// METHOD NAME: Process::Execute
////////////////////////////////
void Process::Execute(const bool debug)
{
    LOG_DEBUG("Executing process. debug = %d", debug);

    do
    {
        if (debug)
        {
            LOG_USER("Executing: %s", m_pFileIterator->GetCurrentLine().c_str());
            while (std::cin.get() != '\n') {}
        }
    } while (this->Step());

    LOG_DEBUG("Execution Complete");
}

////////////////////////////////
/// METHOD NAME: Process::Step
////////////////////////////////
bool Process::Step()
{
    // Fetch the next line
    Io::LineParser lineParser(&m_pFileIterator->GoToLine(m_processRegisters.PC));

    while (lineParser.GetLineType() != Io::LineType::INSTRUCTION &&
           lineParser.GetLineType() != Io::LineType::LABEL_AND_INSTRUCTION)
    {
        if (lineParser.GetLineType() == Io::LineType::ENDP) return false;
        lineParser.SetLine(&m_pFileIterator->Next());
    }
    // Update the pc once a valid line is found
    m_processRegisters.PC = m_pFileIterator->GetLineNumber();

    std::string instruction = lineParser.GetTrimmedLine();

    InstructionBase* pInstruction;
    pInstruction = InstructionBuilder::GetInstance().BuildInstruction(instruction, this);
    pInstruction->Execute(this->GetProcessRegisters());

    // If a branch instruction was executed, use the set PC
    OpCode opCode = pInstruction->GetOpCode();
    if ((opCode == OpCode::B) || (opCode == OpCode::BL) ||
        (opCode == OpCode::BX) || (opCode == OpCode::BLX))
    {
        LOG_DEBUG("PC set to %d", m_processRegisters.PC);
    }
    else
    {
        m_processRegisters.PC++;
        LOG_DEBUG("PC incremented to %d", m_processRegisters.PC);
    }

    // Delete the instruction now that it's been executed
    delete pInstruction;

    return true;
}