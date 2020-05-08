/////////////////////////////////
/// @file BLInstruction.hpp
///
/// @brief Declaration of BLInstruction class
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef BL_INSTRUCTION_HPP
#define BL_INSTRUCTION_HPP

// SYSTEM INCLUDES
#include <string>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "InstructionBase.hpp" // For InstructionBase

// FORWARD DECLARATIONS
// (None)

////////////////////////////////
/// @class BLInstruction
///
/// @brief Class to represent BL instruction
////////////////////////////////
class BLInstruction : public InstructionBase
{
public:

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    BLInstruction() :
        InstructionBase(InstructionType::FLOW_CTRL)
    {}

    ////////////////////////////////
    /// METHOD NAME: Execute
    ///
    /// @brief Sets the LR to the current
    /// PC value + 1 and sets the PC to the value
    /// associated with the given label
    ///
    /// @copydoc InstructionBase::Execute()
    ////////////////////////////////
    void Execute(const SLList<std::string>& rArguments, Process& rProcess);

protected:

private:


};

#endif