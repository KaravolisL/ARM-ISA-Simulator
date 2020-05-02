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
#include <string>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "InstructionIface.hpp" // For InstructionIface

// FORWARD DECLARATIONS
// (None)

////////////////////////////////
/// @class CMPInstruction
///
/// @brief Class to represent CMP instruction
////////////////////////////////
class CMPInstruction : public InstructionIface
{
public:

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    CMPInstruction() {}

    ////////////////////////////////
    /// METHOD NAME: Execute
    ///
    /// @brief Subtracts the given arguments
    /// and sets the flags accordingly
    ///
    /// @param[in] rArguments   List of arguments to be used by the instruction
    /// @param[in,out] rProcess Process that this instruction is apart of
    ////////////////////////////////
    void Execute(const SLList<std::string>& rArguments, Process& rProcess);

protected:

private:


};

#endif