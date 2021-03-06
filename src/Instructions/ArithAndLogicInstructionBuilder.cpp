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
#include "List.hpp" // For List
#include "LineParser.hpp" // For Io::LineParser
#include "FileIterator.hpp" // For Io::FileIterator
#include "Assert.hpp" // For ASSERT
#include "Logger.hpp" // For LOB_DEBUG

////////////////////////////////
/// METHOD NAME: ArithAndLogicInstructionBuilder::BuildInstruction 
////////////////////////////////
InstructionBase* ArithAndLogicInstructionBuilder::BuildInstruction(std::string& rInstruction, Process* pProcess)
{
    ArithAndLogicInstruction* pInstruction = new ArithAndLogicInstruction(m_opCode);

    // Check for the S flag
    std::string keyword = rInstruction.substr(0, rInstruction.find_first_of(' '));
    if (CheckSFlag(keyword)) 
    {
        // Set the flag and remove the S from the instruction
        pInstruction->SetSFlag();
        rInstruction.erase(0, 1);
    }

    LOG_INSTRUCTION("rInstruction = %s", rInstruction.c_str());

    // Create a line parser to retrieve the remaining arguments
    Io::LineParser lineParser(&rInstruction);
    List<std::string> arguments;
    lineParser.Tokenize(arguments);
    uint8_t argumentNumber = 0;

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
            throw InvalidSyntaxException("Invalid argument",
                                         pProcess->GetFileIterator()->GetCurrentLine(),
                                         pProcess->GetFileIterator()->GetLineNumber());
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
                    throw InvalidSyntaxException("Invalid argument",
                                                 pProcess->GetFileIterator()->GetCurrentLine(),
                                                 pProcess->GetFileIterator()->GetLineNumber());
                    break;
            }
        }
    }
    else
    {
        // There is only one argument, so move the first argument and use the destination as the first
        pInstruction->SetArgument2(pInstruction->GetArgument1());
        pInstruction->SetArgument1(*pDestination);
    }
    

    // Any additional arguments would have to be shifting
    if (arguments.GetLength() > argumentNumber)
    {
        if (!IsShift(arguments[argumentNumber]))
        {
            throw InvalidSyntaxException("Invalid syntax",
                                         pProcess->GetFileIterator()->GetCurrentLine(),
                                         pProcess->GetFileIterator()->GetLineNumber());
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
    LOG_INSTRUCTION("m_opCode = %d", m_opCode);

    switch (m_opCode)
    {
    case OpCode::ADD:
        pInstruction->SetOperation([](Register a, Register b) { return a + b; });
        break;
    case OpCode::SUB:
        pInstruction->SetOperation([](Register a, Register b) { return a - b; });
        break;
    case OpCode::MUL:
        pInstruction->SetOperation([](Register a, Register b) { return a * b; });
        break;
    case OpCode::AND:
        pInstruction->SetOperation([](Register a, Register b) { return a & b; });
        break;
    case OpCode::ORR:
        pInstruction->SetOperation([](Register a, Register b) { return a | b; });
        break;
    case OpCode::BIC:
        pInstruction->SetOperation([](Register a, Register b) { return a & (~b); });
        break;
    case OpCode::EOR:
        pInstruction->SetOperation([](Register a, Register b) { return a ^ b; });
        break;
    case OpCode::LSL:
        pInstruction->SetOperation([](Register a, Register b) { return a << b; });
        break;
    case OpCode::LSR:
        pInstruction->SetOperation([](Register a, Register b) { return a >> b; });
        break;
    case OpCode::CMN:
        // Set the flags, but "discard" result
        pInstruction->SetOperation([](Register a, Register b) { return a + b; });
        pInstruction->SetSFlag();
        pInstruction->VoidDestination();
        break;
    case OpCode::CMP:
        // Set the flags, but "discard" result
        pInstruction->SetOperation([](Register a, Register b) { return a - b; });
        pInstruction->SetSFlag();
        pInstruction->VoidDestination();
        break;
    case OpCode::TEQ:
        // Set the flags, but "discard" result
        pInstruction->SetOperation([](Register a, Register b) { return a ^ b; });
        pInstruction->SetSFlag();
        pInstruction->VoidDestination();
        break;
    case OpCode::TST:
        // Set the flags, but "discard" result
        pInstruction->SetOperation([](Register a, Register b) { return a & b; });
        pInstruction->SetSFlag();
        pInstruction->VoidDestination();
        break;
    case OpCode::MOV:
        pInstruction->SetOperation([](Register a, Register b) { return b; });
        break;
    default:
        ASSERT(false, "Unsupported opcode %d", m_opCode);
        break;
    }

    return pInstruction;
}

////////////////////////////////
/// METHOD NAME: ArithAndLogicInstructionBuilder::CheckSFlag 
////////////////////////////////
bool ArithAndLogicInstructionBuilder::CheckSFlag(std::string& rKeyword) const
{
    if (rKeyword.length() > 0 && rKeyword[0] == 'S')
    {
        LOG_INSTRUCTION("Instruction will set the flags");
        return true;
    }
    else
    {
        return false;
    }
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
