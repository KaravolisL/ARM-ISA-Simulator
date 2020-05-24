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
    ArithAndLogicInstructionBuilder() :
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
    /// METHOD NAME: ParseRegister
    ///
    /// @brief Takes a string and converts it
    /// to a pointer to a register
    ///
    /// @param[in] rDestStr     String of the register
    /// @param[in] pProcess     Process to which the instruction belongs
    /// @return A pointer to the corresponding register
    ////////////////////////////////
    Register* ParseRegister(std::string& rDestStr, Process* pProcess) const;

    ////////////////////////////////
    /// METHOD NAME: ParseImmediate
    ///
    /// @brief Takes a string and converts it
    /// to an immediate value
    ///
    /// @param[in] rImmedStr     String of the immediate
    /// @return The immediate value
    ////////////////////////////////
    Register ParseImmediate(std::string& rImmedStr) const;

    ////////////////////////////////
    /// METHOD NAME: IsShift
    ///
    /// @brief Determines whether a string
    /// is a shift operation
    ///
    /// @param[in] rShiftStr    String to investigate
    /// @return Whether the string is a shift operation or not
    ////////////////////////////////
    bool IsShift(std::string& rShiftStr) const;

    ////////////////////////////////
    /// METHOD NAME: HandleShift
    ///
    /// @brief Shifts the given register by the 
    /// amount and in the provided manner.
    ///
    /// @param[in,out] rArgument    Register to be shifted
    /// @param[in]     rShiftType   Type of shift to be done
    /// @param[in]     rShiftAmtStr Amount to shift register by
    ////////////////////////////////
    void HandleShift(Register& rArgument, std::string& rShiftType, std::string& rShiftAmtStr) const;

};

#endif