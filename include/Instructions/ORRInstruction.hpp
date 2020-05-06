/////////////////////////////////
/// @file ORRInstruction.hpp
///
/// @brief Declaration of ORRInstruction class
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef ORR_INSTRUCTION_HPP
#define ORR_INSTRUCTION_HPP

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "InstructionBase.hpp" // For InstructionBase

// FORWARD DECLARATIONS
// (None)

////////////////////////////////
/// @class ORRInstruction
///
/// @brief Class to represent ORR instruction
////////////////////////////////
class ORRInstruction : public InstructionBase
{
public:

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    ORRInstruction() {}

    ////////////////////////////////
    /// METHOD NAME: Execute
    ///
    /// @brief Logical ors the arguments
    /// and places it in the first argument
    ///
    /// @copydoc InstructionBase::Execute()
    ////////////////////////////////
    void Execute(const SLList<std::string>& rArguments, Process& rProcess);

protected:

private:

};

#endif