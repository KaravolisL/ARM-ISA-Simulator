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
#include "InstructionTypes.hpp"

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
        m_flagged(false),
        m_opCode(opCode),
        m_type(InstructionType::ARITHMETIC)
    {}

    InstructionBase(InstructionType type) :
        m_flagged(false),
        m_opCode(OpCode::INVALID),
        m_type(type)
    {}

    ////////////////////////////////
    /// Deconstructor
    ////////////////////////////////
    virtual ~InstructionBase() {}

    ////////////////////////////////
    /// METHOD NAME: Execute
    ///
    /// @param[in] rArguments   List of arguments to be used by the instruction
    /// @param[in,out] rProcess Process that this instruction is apart of
    ////////////////////////////////
    virtual void Execute(const SLList<std::string>& rArguments, Process& rProcess) = 0;

    virtual void Execute(Registers& rProcessRegisters) {};

    ////////////////////////////////
    /// METHOD NAME: SetFlagged
    ////////////////////////////////
    void SetFlagged() { m_flagged = true; }

    ////////////////////////////////
    /// METHOD NAME: ClearFlagged
    ////////////////////////////////
    void ClearFlagged() { m_flagged = false; }

    ////////////////////////////////
    /// METHOD NAME: GetOpCode
    ////////////////////////////////
    OpCode GetOpCode() const { return m_opCode; }

    InstructionType GetType() { return m_type; }

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

    /// Flag to determine whether flags need to be set following instruction execution
    bool m_flagged;

    /// OpCode of instruction
    OpCode m_opCode;

    InstructionType m_type;

private:

};

#endif