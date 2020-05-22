/////////////////////////////////
/// @file InstructionBuilder.hpp
///
/// @brief Declarations for InstructionBuilder
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef INSTRUCTION_BUILDER_HPP
#define INSTRUCTION_BUILDER_HPP

// SYSTEM INCLUDES
#include <string>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "OpCodes.hpp" // For OpCode enum

// FORWARD DECLARATIONS
class InstructionBase;
class Process;

////////////////////////////////
/// @class InstructionBuilder
///
/// @brief This class holds instances
/// of instruction classes that can be retrieved
/// using the GetInstruction method
////////////////////////////////
class InstructionBuilder
{
public:

    ////////////////////////////////
    /// METHOD NAME: GetInstance
    ////////////////////////////////
    static InstructionBuilder& GetInstance()
    {
        static InstructionBuilder* pInstance = new InstructionBuilder();
        return *pInstance;
    }

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
    /// METHOD NAME: DetermineOpCode
    ///
    /// @brief This method will parse the instruction
    /// keyword. It determines the type of instruction that
    /// needs built.
    ///
    /// @param[in] rInstructionKeyword      Instruction to be parsed
    /// @return OpCode of the instruction
    ////////////////////////////////
    const OpCode DetermineOpCode(std::string& rInstructionKeyword) const;

    ////////////////////////////////
    /// Constructor
    ///
    /// @note Private to ensure singleton
    ////////////////////////////////
    InstructionBuilder() {}

    ////////////////////////////////
    /// Copy Constructer
    ////////////////////////////////
    InstructionBuilder(InstructionBuilder const&);

    ////////////////////////////////
    /// Assignment operator
    ////////////////////////////////
    InstructionBuilder& operator=(InstructionBuilder const&);

};

#endif