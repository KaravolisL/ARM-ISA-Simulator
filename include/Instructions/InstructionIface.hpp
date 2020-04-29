/////////////////////////////////
/// @file InstructionIface.hpp
///
/// @brief Declaration of interface class
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef INSTRUCTION_IFACE_HPP
#define INSTRUCTION_IFACE_HPP

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
/// @class InstructionIface
///
/// @brief Fully virtual class used by 
/// specific instruction classes
////////////////////////////////
class InstructionIface
{
public:

    ////////////////////////////////
    /// Deconstructor
    ////////////////////////////////
    virtual ~InstructionIface() {}

    ////////////////////////////////
    /// METHOD NAME: Execute
    ///
    /// @param[in] rArguments   List of arguments to be used by the instruction
    /// @param[in,out] rProcess Process that this instruction is apart of
    ////////////////////////////////
    virtual void Execute(SLList<std::string> rArguments, Process& rProcess) = 0;

protected:

private:


};

#endif