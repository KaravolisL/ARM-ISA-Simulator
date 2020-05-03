/////////////////////////////////
/// @file ANDInstruction.hpp
///
/// @brief Declaration of ANDInstruction class
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef AND_INSTRUCTION_HPP
#define AND_INSTRUCTION_HPP

// SYSTEM INCLUDES
#include <string>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "InstructionBase.hpp" // For InstructionBase

// FORWARD DECLARATIONS
// (None)

////////////////////////////////
/// @class ANDInstruction
///
/// @brief Class to represent AND instruction
////////////////////////////////
class ANDInstruction : public InstructionBase
{
public:

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    ANDInstruction() {}

    ////////////////////////////////
    /// METHOD NAME: Execute
    ///
    /// @brief Logical ands the arguments
    /// and places it in the first argument
    ///
    /// @param[in] rArguments   List of arguments to be used by the instruction
    /// @param[in,out] rProcess Process that this instruction is apart of
    ////////////////////////////////
    void Execute(const SLList<std::string>& rArguments, Process& rProcess);

protected:

private:

};

#endif