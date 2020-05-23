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
struct Registers;

////////////////////////////////
/// @class InstructionBuilder
///
/// @brief This class is used as the first
/// step in building an instruction. It performs
/// some operations then passes the remaining
/// operations to another builder class
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
    virtual InstructionBase* BuildInstruction(std::string& rInstruction, Process* pProcess);

protected:

private:

    ////////////////////////////////
    /// METHOD NAME: DetermineOpCode
    ///
    /// @brief This method will parse the instruction
    /// keyword. It determines the type of instruction that
    /// needs built. The opcode will be stripped if present.
    ///
    /// @param[in] rKeyword      Instruction to be parsed
    /// @return OpCode of the instruction
    ////////////////////////////////
    OpCode DetermineOpCode(std::string& rKeyword) const;

    ////////////////////////////////
    /// METHOD NAME: CheckConditionalCode
    ///
    /// @brief Determines whether the given
    /// instruction should be executed depending
    /// on the conditional codes and flags. The conditional
    /// code will also be stripped.
    ///
    /// @param[in,out] rKeyword         Instruction to be executed
    /// @param[in] rRegisters           Registers of the process for this instruction
    /// @return Whether the instruction should be executed
    /// @retval true        - The instruction should be executed
    /// @retval false       - The instruction should become a nop
    ////////////////////////////////
    bool CheckConditionalCode(std::string& rKeyword, const Registers& rRegisters) const;

    ////////////////////////////////
    /// METHOD NAME: CheckSFlag
    ///
    /// @brief Check whether the instruction should 
    /// set the process's flags following its execution. The
    /// S will be stripped if present
    ///
    /// @param[in] rKeyword      Instruction to be checked
    /// @return Whether instruction needs to set the process flags
    /// @retval true        - The instruction needs to set the process flags
    /// @retval false       - The instruction need not to set flags
    ////////////////////////////////
    bool CheckSFlag(std::string& rKeyword) const;

    ////////////////////////////////
    /// Constructor
    ///
    /// @note Private to ensure singleton
    ////////////////////////////////
    InstructionBuilder() {}

    ////////////////////////////////
    /// Deconstructor
    ////////////////////////////////
    ~InstructionBuilder();

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