/////////////////////////////////
/// @file EORInstruction.hpp
///
/// @brief Declaration of EORInstruction class
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef EOR_INSTRUCTION_HPP
#define EOR_INSTRUCTION_HPP

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "InstructionBase.hpp" // For InstructionBase

// FORWARD DECLARATIONS
// (None)

////////////////////////////////
/// @class EORInstruction
///
/// @brief Class to represent EOR instruction
////////////////////////////////
class EORInstruction : public InstructionBase
{
public:

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    EORInstruction() {}

    ////////////////////////////////
    /// METHOD NAME: Execute
    ///
    /// @brief Logical xors the arguments
    /// and places it in the first argument
    ///
    /// @copydoc InstructionBase::Execute()
    ////////////////////////////////
    void Execute(const SLList<std::string>& rArguments, Process& rProcess);

protected:

private:

};

#endif