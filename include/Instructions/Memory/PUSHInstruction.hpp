/////////////////////////////////
/// @file PUSHInstruction.hpp
///
/// @brief Declaration of PUSHInstruction class
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef PUSH_INSTRUCTION_HPP
#define PUSH_INSTRUCTION_HPP

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "InstructionBase.hpp" // For InstructionBase

// FORWARD DECLARATIONS
// (None)

////////////////////////////////
/// @class PUSHInstruction
///
/// @brief Class to represent PUSH instruction
////////////////////////////////
class PUSHInstruction : public InstructionBase
{
public:

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    PUSHInstruction() :
        InstructionBase(OpCode::PUSH)
    {}

    ////////////////////////////////
    /// METHOD NAME: Execute
    ///
    /// @brief Places a set of registers onto the
    /// stack in memory. The list must be wrapped in
    /// curly braces and the registers will be pushed in 
    /// ascending order
    ///
    /// @copydoc InstructionBase::Execute()
    ////////////////////////////////
    void Execute(const SLList<std::string>& rArguments, Process& rProcess);

    void Execute(Registers& rProcRegisters) {}

protected:

private:

};

#endif