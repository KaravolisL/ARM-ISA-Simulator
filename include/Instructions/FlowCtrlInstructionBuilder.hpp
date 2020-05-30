/////////////////////////////////
/// @file FlowCtrlInstructionBuilder.hpp
///
/// @brief Declarations for FlowCtrlInstructionBuilder
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef FLOW_CTRL_INSTRUCTION_BUILDER_HPP
#define FLOW_CTRL_INSTRUCTION_BUILDER_HPP

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "InstructionBuilder.hpp" // For InstructionBuilder

// FORWARD DECLARATIONS
class Process;

////////////////////////////////
/// @class FlowCtrlInstructionBuilder
///
/// @brief This class is responsible for building
/// flow control instructions
////////////////////////////////
class FlowCtrlInstructionBuilder : public InstructionBuilder
{
public:

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    FlowCtrlInstructionBuilder() :
        InstructionBuilder()
    {}

    ////////////////////////////////
    /// METHOD NAME: BuildInstruction
    ///
    /// @brief Given a string containing the instruction
    /// and all it's arguments, this method will construct
    /// an instruction object to be executed
    ///
    /// @param[in] rInstruction     Instruction to be built
    /// @param[in] pProcess         Process for which the instruction is being built
    /// @return Instance of built instruction object
    ////////////////////////////////
    InstructionBase* BuildInstruction(std::string& rInstruction, Process* pProcess);

protected:

private:

};

#endif