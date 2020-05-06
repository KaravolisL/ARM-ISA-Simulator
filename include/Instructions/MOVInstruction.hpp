/////////////////////////////////
/// @file MOVInstruction.hpp
///
/// @brief Declaration of MOVInstruction class
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef MOV_INSTRUCTION_HPP
#define MOV_INSTRUCTION_HPP

// SYSTEM INCLUDES
#include <string>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "InstructionBase.hpp" // For InstructionBase

// FORWARD DECLARATIONS
// (None)

////////////////////////////////
/// @class MOVInstruction
///
/// @brief Class to represent MOV instruction
////////////////////////////////
class MOVInstruction : public InstructionBase
{
public:

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    MOVInstruction() {}

    ////////////////////////////////
    /// METHOD NAME: Execute
    ///
    /// @brief Moves the value stored in the
    /// second argument into the first argument
    ///
    /// @copydoc InstructionBase::Execute()
    ////////////////////////////////
    void Execute(const SLList<std::string>& rArguments, Process& rProcess);

protected:

private:


};

#endif