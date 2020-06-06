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

    // PROTECTED METHODS
    // (None)

    // PROTECTED MEMBERS

    /// OpCode of instruction
    OpCode m_opCode;

private:

    // PRIVATE METHODS
    // (None)

    // PRIVATE MEMBERS
    // (None)

};

#endif