/////////////////////////////////
/// @file POPInstruction.hpp
///
/// @brief Declaration of POPInstruction class
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef POP_INSTRUCTION_HPP
#define POP_INSTRUCTION_HPP

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "InstructionBase.hpp" // For InstructionBase

// FORWARD DECLARATIONS
// (None)

////////////////////////////////
/// @class POPInstruction
///
/// @brief Class to represent POP instruction
////////////////////////////////
class POPInstruction : public InstructionBase
{
public:

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    POPInstruction() :
        InstructionBase(InstructionType::MEMORY)
    {}

    ////////////////////////////////
    /// METHOD NAME: Execute
    ///
    /// @brief Pops 32 bits of data from
    /// the top of the stack and places it into
    /// a corresponding register. The registers
    /// are filled in ascending order
    ///
    /// @copydoc InstructionBase::Execute()
    ////////////////////////////////
    void Execute(const SLList<std::string>& rArguments, Process& rProcess);

protected:

private:

};

#endif