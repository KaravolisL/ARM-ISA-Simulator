/////////////////////////////////
/// @file CMPInstruction.hpp
///
/// @brief Declaration of CMPInstruction class
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef CMP_INSTRUCTION_HPP
#define CMP_INSTRUCTION_HPP

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "InstructionBase.hpp" // For InstructionBase

// FORWARD DECLARATIONS
// (None)

////////////////////////////////
/// @class CMPInstruction
///
/// @brief Class to represent CMP instruction
////////////////////////////////
class CMPInstruction : public InstructionBase
{
public:

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    CMPInstruction() :
        InstructionBase(InstructionType::COMPARISON)
    {}

    ////////////////////////////////
    /// METHOD NAME: Execute
    ///
    /// @brief Subtracts the given arguments
    /// and sets the flags accordingly
    ///
    /// @copydoc InstructionBase::Execute()
    ////////////////////////////////
    void Execute(const SLList<std::string>& rArguments, Process& rProcess);

protected:

private:


};

#endif