/////////////////////////////////
/// @file CMNInstruction.hpp
///
/// @brief Declaration of CMNInstruction class
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef CMN_INSTRUCTION_HPP
#define CMN_INSTRUCTION_HPP

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "InstructionBase.hpp" // For InstructionBase

// FORWARD DECLARATIONS
// (None)

////////////////////////////////
/// @class CMNInstruction
///
/// @brief Class to represent CMN instruction
////////////////////////////////
class CMNInstruction : public InstructionBase
{
public:

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    CMNInstruction() :
        InstructionBase(InstructionType::COMPARISON)
    {}

    ////////////////////////////////
    /// METHOD NAME: Execute
    ///
    /// @brief Adds the given arguments
    /// and sets the flags accordingly
    ///
    /// @copydoc InstructionBase::Execute()
    ////////////////////////////////
    void Execute(const SLList<std::string>& rArguments, Process& rProcess);

protected:

private:


};

#endif