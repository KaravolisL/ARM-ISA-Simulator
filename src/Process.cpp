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
#include "Assert.hpp" // For ASSERT
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

    // Continue fetching instructions until we run out
    while (FetchNextInstruction())
    {
        if (debug)
        {
            LOG_USER("Executing: %s ", m_pFileIterator->GetCurrentLine().c_str());
            HandleUserInput();
        }
        else
        {
            ExecuteNextInstruction();
        }
    }
}

////////////////////////////////
/// METHOD NAME: Process::ExecuteNextInstruction
////////////////////////////////
void Process::ExecuteNextInstruction()
{
    // Construct a line parser using the current line
    Io::LineParser lineParser(&m_pFileIterator->GetCurrentLine());
    LOG_DEBUG("Instruction to be executed: %s", m_pFileIterator->GetCurrentLine().c_str());

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
}

////////////////////////////////
/// METHOD NAME: Process::FetchNextInstruction
////////////////////////////////
bool Process::FetchNextInstruction()
{
    // Fetch the next line
    Io::LineParser lineParser(&m_pFileIterator->GoToLine(m_processRegisters.PC));

    // Find next valid line
    while (lineParser.GetLineType() != Io::LineType::INSTRUCTION &&
           lineParser.GetLineType() != Io::LineType::LABEL_AND_INSTRUCTION)
    {
        if (lineParser.GetLineType() == Io::LineType::ENDP)
        {
            LOG_DEBUG("Execution Complete");
            return false;
        }
        lineParser.SetLine(&m_pFileIterator->Next());
    }

    return true;
}

////////////////////////////////
/// METHOD NAME: Process::HandleUserInput
////////////////////////////////
void Process::HandleUserInput()
{
    LOG_USER("Debug Option: ");
    StepType stepType = StepType::STEP;

    std::string userInput;
    do
    {
        userInput.push_back(std::cin.get());
    } while (userInput.back() != '\n');
    userInput.pop_back();

    if (userInput.size() > 0)
    {
        switch (userInput.back())
        {
            case '2':
                stepType = StepType::STEP_OUT;
                break;
            case '3':
                stepType = StepType::STEP_OVER;
                break;
            case 'q':
                stepType = StepType::STEP_NULL;
                break;
            default:
                stepType = StepType::STEP;
        }
    }

    HandleStepType(stepType);
}

////////////////////////////////
/// METHOD NAME: Process::HandleStepType
////////////////////////////////
void Process::HandleStepType(const StepType stepType)
{
    switch (stepType)
    {
        case StepType::STEP_OVER:
            ASSERT(false);
            break;
        case StepType::STEP_OUT:
        {
            // If the call stack size shrinks, we know we've exited the current function
            uint8_t initialCallStackSize = m_Metadata.GetCallStack().Size();
            do
            {
                ExecuteNextInstruction();
                if ((initialCallStackSize > m_Metadata.GetCallStack().Size()) ||
                    (m_Metadata.IsInMain()))
                {
                    break;
                }
            } while (FetchNextInstruction());
            break;
        }
        case StepType::STEP:
            ExecuteNextInstruction();
            break;
        // case StepType::STEP_NULL:
        //     LOG_USER("Aborting program...\n");
        //     while (FetchNextInstruction()) {}
        //     break;
        default:
            ASSERT(false, "Invalid step type %d", stepType);
    }
}