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
// (None)

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

    /////////////////////////////////////
    /// @brief Constructs a new InstructionBase object
    ///
    /// @param[in] opCode Opcode of the instruction
    /////////////////////////////////////
    InstructionBase(OpCode opCode) :
        m_opCode(opCode)
    {}

    /////////////////////////////////////
    /// @brief Destroys the InstructionBase object
    /////////////////////////////////////
    virtual ~InstructionBase() {}

    ////////////////////////////////
    /// @brief Executes the instruction
    ///
    /// @param[in,out] rProcessRegisters    Set of registers to manipulate
    ////////////////////////////////
    virtual void Execute(Registers& rProcessRegisters) = 0;

    /////////////////////////////////////
    /// @brief Gets the OpCode member
    ///
    /// @return Instruction's Opcode
    /////////////////////////////////////
    OpCode GetOpCode() const { return m_opCode; }

protected:

    /// OpCode of instruction
    OpCode m_opCode;

private:

};

#endif