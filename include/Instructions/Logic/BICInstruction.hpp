/////////////////////////////////
/// @file BICInstruction.hpp
///
/// @brief Declaration of BICInstruction class
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef BIC_INSTRUCTION_HPP
#define BIC_INSTRUCTION_HPP

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "InstructionBase.hpp" // For InstructionBase

// FORWARD DECLARATIONS
// (None)

////////////////////////////////
/// @class BICInstruction
///
/// @brief Class to represent BIC instruction
////////////////////////////////
class BICInstruction : public InstructionBase
{
public:

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    BICInstruction() :
        InstructionBase(InstructionType::LOGIC)
    {}

    ////////////////////////////////
    /// METHOD NAME: Execute
    ///
    /// @brief Bit clears the arguments
    /// and places it in the first argument
    ///
    /// @copydoc InstructionBase::Execute()
    ////////////////////////////////
    void Execute(const SLList<std::string>& rArguments, Process& rProcess);

protected:

private:

};

#endif