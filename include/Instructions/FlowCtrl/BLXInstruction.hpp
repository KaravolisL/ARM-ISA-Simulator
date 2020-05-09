/////////////////////////////////
/// @file BLXInstruction.hpp
///
/// @brief Declaration of BLXInstruction class
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef BLX_INSTRUCTION_HPP
#define BLX_INSTRUCTION_HPP

// SYSTEM INCLUDES
#include <string>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "InstructionBase.hpp" // For InstructionBase

// FORWARD DECLARATIONS
// (None)

////////////////////////////////
/// @class BLXInstruction
///
/// @brief Class to represent BLX instruction
////////////////////////////////
class BLXInstruction : public InstructionBase
{
public:

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    BLXInstruction() :
        InstructionBase(InstructionType::FLOW_CTRL)
    {}

    ////////////////////////////////
    /// METHOD NAME: Execute
    ///
    /// @brief Places the contents of a given
    /// register into the PC. Also, sets the LR to
    /// the next instruction
    ///
    /// @copydoc InstructionBase::Execute()
    ////////////////////////////////
    void Execute(const SLList<std::string>& rArguments, Process& rProcess);

protected:

private:


};

#endif