/////////////////////////////////
/// @file ADDInstruction.hpp
///
/// @brief Declaration of ADDInstruction class
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef ADD_INSTRUCTION_HPP
#define ADD_INSTRUCTION_HPP

// SYSTEM INCLUDES
#include <string>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "InstructionBase.hpp" // For InstructionBase

// FORWARD DECLARATIONS
// (None)

////////////////////////////////
/// @class ADDInstruction
///
/// @brief Class to represent ADD instruction
////////////////////////////////
class ADDInstruction : public InstructionBase
{
public:

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    ADDInstruction() {}

    ////////////////////////////////
    /// METHOD NAME: Execute
    ///
    /// @brief Adds two arguments and places
    /// in the first argument. If two arguments
    /// are given, the source will be added onto
    /// the destination. Otherwise, the two sources
    /// will be added and the destination replaced by the sum
    ///
    /// @param[in] rArguments   List of arguments to be used by the instruction
    /// @param[in,out] rProcess Process that this instruction is apart of
    ////////////////////////////////
    void Execute(const SLList<std::string>& rArguments, Process& rProcess);

protected:

private:

};

#endif