/////////////////////////////////
/// @file NOPInstruction.hpp
///
/// @brief Declaration of NOPInstruction class
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef NOP_INSTRUCTION_HPP
#define NOP_INSTRUCTION_HPP

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "InstructionBase.hpp" // For InstructionBase

// FORWARD DECLARATIONS
// (None)

////////////////////////////////
/// @class NOPInstruction
///
/// @brief Class to represent NOP instruction
////////////////////////////////
class NOPInstruction : public InstructionBase
{
public:

    /////////////////////////////////////
    /// @brief Constructs a new NOPInstruction object
    /////////////////////////////////////
    NOPInstruction() :
        InstructionBase(OpCode::NOP)
    {}

    ////////////////////////////////
    /// @brief ... does absolutely nothing
    ///
    /// @copydoc InstructionBase::Execute()
    ////////////////////////////////
    void Execute(Registers& rProcessRegisters) {}

protected:

private:

};

#endif