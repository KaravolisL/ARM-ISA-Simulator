/////////////////////////////////
/// @file ArithAndLogicInstructionBuilder.cpp
///
/// @brief Implementation for ArithAndLogicInstructionBuilder
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "ArithAndLogicInstructionBuilder.hpp" // Header for class
#include "ArithAndLogicInstruction.hpp" // For ArithAndLogicInstruction
#include "InvalidSyntaxException.hpp" // For InvalidSyntaxException
#include "Process.hpp" // For Process
#include "SLList.hpp" // For SLList
#include "LineParser.hpp" // For Io::LineParser
#include "Assert.hpp" // For ASSERT
#include "Logger.hpp" // For LOB_DEBUG

////////////////////////////////
/// METHOD NAME: ArithAndLogicInstructionBuilder::BuildInstruction 
////////////////////////////////
InstructionBase* ArithAndLogicInstructionBuilder::BuildInstruction(std::string& rInstruction, Process* pProcess)
{
    ArithAndLogicInstruction* pInstruction = new ArithAndLogicInstruction();

    // Check for the S flag
    std::string keyword = rInstruction.substr(0, rInstruction.find_first_of(' '));
    if (CheckSFlag(keyword)) 
    {
        pInstruction->SetSFlag();
    }

    // Add a character as a placeholder to the keyword
    rInstruction.insert(0, "|");

    LOG_DEBUG("rInstruction = %s", rInstruction.c_str());

    // Create a line parser to retrieve the remaining arguments
    Io::LineParser lineParser(&rInstruction);
    SLList<std::string> arguments;
    lineParser.GetArguments(arguments);
    int argumentNumber = 0;

    // Parse the destination
    Register* pDestination = ParseRegister(arguments[argumentNumber++], pProcess);
    pInstruction->SetDestination(pDestination);

    // Handle the first argument
    switch(arguments[argumentNumber][0])
    {
        case 'r':
        case 'R':
        {
            // First argument is just a register
            Register* pArgument = ParseRegister(arguments[argumentNumber++], pProcess);
            pInstruction->SetArgument1(*pArgument);
            break;
        }
        case '#':
        {
            // First argument is an immediate
            Register immediate = ParseImmediate(arguments[argumentNumber++]);
            pInstruction->SetArgument1(immediate);
            break;
        }
        default:
            // TODO: Throw syntax exception
            break;
    }

    // Handle a possible third instruction
    if (arguments.GetLength() > argumentNumber)
    {
        // Check first if it's a shift
        if (IsShift(arguments[argumentNumber]))
        {
            // Passing the first argument, shift type, and amount
            if (arguments[argumentNumber] == "RRX")
            {
                std::string zero = std::string("0");
                HandleShift(pInstruction->GetArgument1(), arguments[argumentNumber++], zero);
            }
            else
            {
                HandleShift(pInstruction->GetArgument1(), arguments[argumentNumber], arguments[argumentNumber + 1]);
                // Two arguments were handled in the above call
                argumentNumber += 2;
            }
        }
        else
        {
            switch(arguments[argumentNumber][0])
            {
                case 'r':
                case 'R':
                {
                    // Second argument is just a register
                    Register* pArgument = ParseRegister(arguments[argumentNumber++], pProcess);
                    pInstruction->SetArgument2(*pArgument);
                    break;
                }
                case '#':
                {
                    // Second argument is an immediate
                    Register immediate = ParseImmediate(arguments[argumentNumber++]);
                    pInstruction->SetArgument2(immediate);
                    break;
                }
                default:
                    // TODO: Throw syntax exception
                    break;
            }
        }
    }
    else
    {
        // There is only one argument, so use the destination as the second argument
        pInstruction->SetArgument2(*pDestination);
    }
    

    // Any additional arguments would have to be shifting
    if (arguments.GetLength() > argumentNumber)
    {
        if (!IsShift(arguments[argumentNumber]))
        {
            // TODO: Throw syntax exception
        }
        if (arguments[argumentNumber] == "RRX")
        {
            std::string zero = std::string("0");
            HandleShift(pInstruction->GetArgument2(), arguments[argumentNumber++], zero);
        }
        else
        {
            HandleShift(pInstruction->GetArgument2(), arguments[argumentNumber], arguments[argumentNumber + 1]);
            // Two arguments were handled in the call above
            argumentNumber += 2;
        }
    }

    // Add the actual operation based on the opcode
    LOG_DEBUG("m_opCode = %d", m_opCode);

    switch (m_opCode)
    {
    case OpCode::ADD:
        pInstruction->SetOperation([](Register a, Register b) { return a + b; });
        break;
    
    default:
        break;
    }

    return pInstruction;
}

////////////////////////////////
/// METHOD NAME: ArithAndLogicInstructionBuilder::CheckSFlag 
////////////////////////////////
bool ArithAndLogicInstructionBuilder::CheckSFlag(std::string& rKeyword) const
{
    if (rKeyword.length() > 1 && rKeyword[0] == 'S')
    {
        LOG_DEBUG("Instruction will set the flags");
        rKeyword = rKeyword.substr(1);
        return true;
    }
    else
    {
        return false;
    }
}

////////////////////////////////
/// METHOD NAME: ArithAndLogicInstructionBuilder::ParseRegister 
////////////////////////////////
Register* ArithAndLogicInstructionBuilder::ParseRegister(std::string& rRegStr, Process* pProcess) const
{
    LOG_DEBUG("rRegStr = %s", rRegStr.c_str());

    if (rRegStr[0] != 'R' && rRegStr[0] != 'r')
    {
        // TODO: Throw SyntaxException
    }

    // Convert string to register number 
    uint8_t regNumber = atoi(rRegStr.substr(1).c_str());

    return &pProcess->GetProcessRegisters().genRegs[regNumber];
}

Register ArithAndLogicInstructionBuilder::ParseImmediate(std::string& rImmedStr) const
{
    ASSERT(rImmedStr[0] == '#', "Immediate string does not begin with a #");

    // TODO: See Git Issue #32
    return static_cast<uint32_t>(std::stoul(rImmedStr.substr(1).c_str(), nullptr, 0));
}

bool ArithAndLogicInstructionBuilder::IsShift(std::string& rShiftStr) const
{
    return false;
}

void ArithAndLogicInstructionBuilder::HandleShift(Register& rArgument, std::string& rShiftType, std::string& rShiftAmtStr) const
{

}
