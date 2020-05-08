/////////////////////////////////
/// @file BXInstruction.hpp
///
/// @brief Declaration of BXInstruction class
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef BX_INSTRUCTION_HPP
#define BX_INSTRUCTION_HPP

// SYSTEM INCLUDES
#include <string>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "InstructionBase.hpp" // For InstructionBase

// FORWARD DECLARATIONS
// (None)

////////////////////////////////
/// @class BXInstruction
///
/// @brief Class to represent BX instruction
////////////////////////////////
class BXInstruction : public InstructionBase
{
public:

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    BXInstruction() :
        InstructionBase(InstructionType::FLOW_CTRL)
    {}

    ////////////////////////////////
    /// METHOD NAME: Execute
    ///
    /// @brief Places the contents of a given
    /// register into the PC. Normally used as BX LR
    /// in order to return from a function
    ///
    /// @copydoc InstructionBase::Execute()
    ////////////////////////////////
    void Execute(const SLList<std::string>& rArguments, Process& rProcess);

protected:

private:


};

#endif