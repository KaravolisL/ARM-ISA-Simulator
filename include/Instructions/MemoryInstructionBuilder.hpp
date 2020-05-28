/////////////////////////////////
/// @file MemoryInstructionBuilder.hpp
///
/// @brief Declarations for MemoryInstructionBuilder
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef MEMORY_INSTRUCTION_BUILDER_HPP
#define MEMORY_INSTRUCTION_BUILDER_HPP

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "InstructionBuilder.hpp" // For InstructionBuilder

// FORWARD DECLARATIONS
class Process;
class MemoryInstruction;
class MultipleMemoryInstruction;

////////////////////////////////
/// @class MemoryInstructionBuilder
///
/// @brief This class is responsible for building
/// memory instructions
////////////////////////////////
class MemoryInstructionBuilder : public InstructionBuilder
{
public:

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    MemoryInstructionBuilder() :
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

    ////////////////////////////////
    /// METHOD NAME: BuildMemoryInstruction
    ///
    /// @brief Given a string containing the instruction
    /// and all it's arguments, this method will construct
    /// an instruction object to be executed
    ///
    /// @param[in] rInstruction     Instruction to be built
    /// @param[in] pProcess         Process for which the instruction is being built
    /// @return Instance of built instruction object
    ////////////////////////////////
    MemoryInstruction* BuildMemoryInstruction(std::string& rInstruction, Process* pProcess);

    ////////////////////////////////
    /// METHOD NAME: BuildMultipleMemoryInstruction
    ///
    /// @brief Given a string containing the instruction
    /// and all it's arguments, this method will construct
    /// an instruction object to be executed
    ///
    /// @param[in] rInstruction     Instruction to be built
    /// @param[in] pProcess         Process for which the instruction is being built
    /// @return Instance of built instruction object
    ////////////////////////////////
    MultipleMemoryInstruction* BuildMultipleMemoryInstruction(std::string& rInstruction, Process* pProcess);

};

#endif