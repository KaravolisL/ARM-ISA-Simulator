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
#include "Registers.hpp" // For Register

// FORWARD DECLARATIONS
class InstructionBase;
class Process;

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

    /// OpCode of the instruction being build
    OpCode m_opCode;

    ////////////////////////////////
    /// Constructor
    ///
    /// @note Protected to ensure singleton,
    /// but allow access to sub classes
    ////////////////////////////////
    InstructionBuilder() :
        m_opCode(OpCode::INVALID)
    {}

    ////////////////////////////////
    /// Deconstructor
    ////////////////////////////////
    virtual ~InstructionBuilder() {};

    ////////////////////////////////
    /// METHOD NAME: ParseRegister
    ///
    /// @brief Takes a string and converts it
    /// to a pointer to a register
    ///
    /// @param[in] rDestStr     String of the register
    /// @param[in] pProcess     Process to which the instruction belongs
    /// @return A pointer to the corresponding register
    ////////////////////////////////
    Register* ParseRegister(const std::string& rDestStr, Process* pProcess) const;

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
    /// Copy Constructer
    ////////////////////////////////
    InstructionBuilder(InstructionBuilder const&);

    ////////////////////////////////
    /// Assignment operator
    ////////////////////////////////
    InstructionBuilder& operator=(InstructionBuilder const&);

};

#endif