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
#include <string>

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
    BICInstruction() {}

    ////////////////////////////////
    /// METHOD NAME: Execute
    ///
    /// @brief Bit clears the arguments
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