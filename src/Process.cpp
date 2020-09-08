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
#include "MemoryApi.hpp" // For Memory::ReadWord

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
    pInstruction->Execute(GetProcessRegisters());

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
            case 'Q':
            case 'q':
                stepType = StepType::STEP_ABORT;
                break;
            case 'I':
            case 'i':
                // Allow user to inspect memory and don't execute an instruction
                InspectMemory();
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
        {
            uint8_t initialCallStackSize = m_Metadata.GetCallStack().Size();
            // Continue executing instructions until our call stack has shrunk
            do
            {
                ExecuteNextInstruction();
            } while (initialCallStackSize < m_Metadata.GetCallStack().Size() && FetchNextInstruction());
            break;
        }
        case StepType::STEP_OUT:
        {
            // If we're in main, just execute a single instruction
            if (m_Metadata.IsInMain())
            {
                ExecuteNextInstruction();
            }
            else
            {
                // Continue executing instructions until the call stack shrinks
                uint8_t initialCallStackSize = m_Metadata.GetCallStack().Size();
                do
                {
                    ExecuteNextInstruction();
                    if (initialCallStackSize > m_Metadata.GetCallStack().Size()) break;
                } while (FetchNextInstruction());
            }
            break;
        }
        case StepType::STEP:
            ExecuteNextInstruction();
            break;
        case StepType::STEP_ABORT:
            LOG_USER("Aborting program...\n");
            while (FetchNextInstruction())
            {
                m_processRegisters.PC++;
            }
            break;
        case StepType::STEP_NULL:
            break;
        default:
            ASSERT(false, "Invalid step type %d", stepType);
    }
}

////////////////////////////////
/// METHOD NAME: Process::InspectMemory
////////////////////////////////
void Process::InspectMemory() const
{
    LOG_USER("Register or Memory Address to Inspect: ");

    std::string userInput;
    do
    {
        userInput.push_back(std::cin.get());
    } while (userInput.back() != '\n');
    userInput.pop_back();

    if (userInput.size() == 0)
    {
        return;
    }

    uint32_t data;
    if (userInput[0] != 'R' && userInput[0] != 'r')
    {
        if (userInput == "LR")
        {
            data = m_processRegisters.LR;
        }
        else if (userInput == "SP")
        {
            data = m_processRegisters.SP;
        }
        else if (userInput == "PC")
        {
            data = m_processRegisters.PC;
        }
        else
        {
            // It must be a memory address
            try
            {
                uint32_t memAddress = static_cast<uint32_t>(std::stoul(userInput.c_str(), nullptr, 0));
                data = Memory::MemoryApi::ReadWord(memAddress);
            }
            catch (const std::exception& e)
            {
                LOG_USER("Invalid Memory Address\n");
                return;
            }
        }
    }
    else
    {
        try
        {
            // Convert string to register number
            uint8_t regNumber = atoi(userInput.substr(1).c_str());
            if (regNumber >= (sizeof(m_processRegisters) / sizeof(Register)))
            {
                throw IndexOutOfBoundsException();
            }
            data = m_processRegisters.genRegs[regNumber];
        }
        catch (const std::exception& e)
        {
            LOG_USER("Invalid Register\n");
            return;
        }
    }

    LOG_USER("Value of %s = 0x%x\n", userInput.c_str(), data);
}