/////////////////////////////////
/// @file SUBInstruction.hpp
///
/// @brief Declaration of SUBInstruction class
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef SUB_INSTRUCTION_HPP
#define SUB_INSTRUCTION_HPP

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "InstructionBase.hpp" // For InstructionBase

// FORWARD DECLARATIONS
// (None)

////////////////////////////////
/// @class SUBInstruction
///
/// @brief Class to represent SUB instruction
////////////////////////////////
class SUBInstruction : public InstructionBase
{
public:

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    SUBInstruction() :
        InstructionBase(InstructionType::ARITHMETIC)
    {}

    ////////////////////////////////
    /// METHOD NAME: Execute
    ///
    /// @brief Subtracts two arguments and places the result
    /// in the first argument. If two arguments
    /// are given, the source will be added onto
    /// the destination. Otherwise, the two sources
    /// will be subtracted and the destination replaced by the difference
    ///
    /// @copydoc InstructionBase::Execute()
    ////////////////////////////////
    void Execute(const SLList<std::string>& rArguments, Process& rProcess);

protected:

private:

};

#endif