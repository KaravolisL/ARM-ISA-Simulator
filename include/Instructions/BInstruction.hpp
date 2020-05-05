/////////////////////////////////
/// @file BInstruction.hpp
///
/// @brief Declaration of BInstruction class
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef B_INSTRUCTION_HPP
#define B_INSTRUCTION_HPP

// SYSTEM INCLUDES
#include <string>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "InstructionBase.hpp" // For InstructionBase

// FORWARD DECLARATIONS
// (None)

////////////////////////////////
/// @class BInstruction
///
/// @brief Class to represent B instruction
////////////////////////////////
class BInstruction : public InstructionBase
{
public:

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    BInstruction() {}

    ////////////////////////////////
    /// METHOD NAME: Execute
    ///
    /// @brief Set the PC to the value associated
    /// with the given label
    ///
    /// @copydoc InstructionBase::Execute()
    ////////////////////////////////
    void Execute(const SLList<std::string>& rArguments, Process& rProcess, bool flagged);

protected:

private:


};

#endif