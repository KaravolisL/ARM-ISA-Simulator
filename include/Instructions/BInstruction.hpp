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
#include "InstructionIface.hpp" // For InstructionIface

// FORWARD DECLARATIONS
// (None)

////////////////////////////////
/// @class BInstruction
///
/// @brief Class to represent B instruction
////////////////////////////////
class BInstruction : public InstructionIface
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
    /// @param[in] rArguments   List of arguments to be used by the instruction
    /// @param[in,out] rProcess Process that this instruction is apart of
    ////////////////////////////////
    void Execute(const SLList<std::string>& rArguments, Process& rProcess);

protected:

private:


};

#endif