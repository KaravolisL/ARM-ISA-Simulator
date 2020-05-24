/////////////////////////////////
/// @file ArithAndLogicInstructionBuilder.hpp
///
/// @brief Declarations for ArithAndLogicInstructionBuilder
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef ARITH_AND_LOGIC_INSTRUCTION_BUILDER_HPP
#define ARITH_AND_LOGIC_INSTRUCTION_BUILDER_HPP

// SYSTEM INCLUDES
#include <string>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "InstructionBuilder.hpp" // For InstructionBuilder
#include "Registers.hpp" // For Register

// FORWARD DECLARATIONS
class ArithAndLogicInstruction;
class Process;

////////////////////////////////
/// @class ArithAndLogicInstructionBuilder
///
/// @brief This class is responsible for building
/// arithmetic and logic instructions.
////////////////////////////////
class ArithAndLogicInstructionBuilder : public InstructionBuilder
{
public:

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    ArithAndLogicInstructionBuilder();

    ////////////////////////////////
    /// Deconstructor
    ////////////////////////////////
    ~ArithAndLogicInstructionBuilder();

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
    /// METHOD NAME: ParseDestination
    ///
    /// @brief Takes a string and converts it
    /// to a pointer to the destination register
    ///
    /// @param[in] rDestStr     String of the destination register
    /// @param[in] pProcess     Process to which the instruction belongs
    /// @return A pointer to the corresponding register
    ////////////////////////////////
    Register* ParseDestination(std::string& rDestStr, Process* pProcess) const;

};

#endif