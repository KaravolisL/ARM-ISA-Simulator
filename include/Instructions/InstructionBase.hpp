/////////////////////////////////
/// @file InstructionBase.hpp
///
/// @brief Declaration of InstructionBase class
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef INSTRUCTION_BASE_HPP
#define INSTRUCTION_BASE_HPP

// SYSTEM INCLUDES
#include <string>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
// (None)

// FORWARD DECLARATIONS
template <typename T>
class SLList;

class Process;

////////////////////////////////
/// @class InstructionBase
///
/// @brief Base class used by 
/// specific instruction classes
////////////////////////////////
class InstructionBase
{
public:

    ////////////////////////////////
    /// Deconstructor
    ////////////////////////////////
    virtual ~InstructionBase() {}

    ////////////////////////////////
    /// METHOD NAME: Execute
    ///
    /// @param[in] rArguments   List of arguments to be used by the instruction
    /// @param[in,out] rProcess Process that this instruction is apart of
    ////////////////////////////////
    virtual void Execute(const SLList<std::string>& rArguments, Process& rProcess) = 0;

protected:

    ////////////////////////////////
    /// METHOD NAME: ParseArgument
    ///
    /// @brief Interprets a given string as an integer
    /// This could be either a # followed by a literal,
    /// a register, or a = follow by a constant.
    ///
    /// @param[in] rArguments   Argument to be parsed into integer
    /// @param[in,out] rProcess Process that this instruction is apart of
    ////////////////////////////////
    uint32_t ParseArgument(const std::string& rArgument, Process& rProcess);

private:

};

#endif