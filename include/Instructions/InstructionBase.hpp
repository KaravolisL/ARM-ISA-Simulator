/////////////////////////////////
/// @file InstructionBase.hpp
///
/// @brief Declaration of InstructionBase class
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef INSTRUCTION_BASE_HPP
#define INSTRUCTION_BASE_HPP

// SYSTEM INCLUDES
#include <string>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "OpCodes.hpp" // For OpCode enum

// FORWARD DECLARATIONS
template <typename T>
class SLList;

class Process;
struct Registers;

////////////////////////////////
/// @class InstructionBase
///
/// @brief Base class used by 
/// specific instruction classes
////////////////////////////////
class InstructionBase
{
public:

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    InstructionBase(OpCode opCode) :
        m_opCode(opCode)
    {}

    ////////////////////////////////
    /// Deconstructor
    ////////////////////////////////
    virtual ~InstructionBase() {}

    ////////////////////////////////
    /// METHOD NAME: Execute
    ///
    /// @param[in,out] rProcessRegisters    Set of registers to manipulate
    ////////////////////////////////
    virtual void Execute(Registers& rProcessRegisters) = 0;

    ////////////////////////////////
    /// METHOD NAME: GetOpCode
    ////////////////////////////////
    OpCode GetOpCode() const { return m_opCode; }

protected:

    ////////////////////////////////
    /// METHOD NAME: ParseArgument
    ///
    /// @brief Interprets a given string as an integer
    /// This could be either a # followed by a literal,
    /// a register, or a = follow by a constant.
    ///
    /// @param[in] rArguments   Argument to be parsed into integer
    /// @param[in,out] rProcess Process that this instruction is apart of
    ////////////////////////////////
    uint32_t ParseArgument(const std::string& rArgument, Process& rProcess);

    /// OpCode of instruction
    OpCode m_opCode;

private:

};

#endif