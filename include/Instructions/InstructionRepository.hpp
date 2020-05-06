/////////////////////////////////
/// @file InstructionRepository.hpp
///
/// @brief Declarations for InstructionRepository
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef INSTRUCTION_REPOSITORY_HPP
#define INSTRUCTION_REPOSITORY_HPP

// SYSTEM INCLUDES
#include <string>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "HashMap.hpp" // For HashMap
#include "ConditionalCode.hpp" // For ConditionalCodes

// FORWARD DECLARATIONS
class InstructionBase;
class Process;
struct Registers;

////////////////////////////////
/// @class InstructionRepository
///
/// @brief This class holds instances
/// of instruction classes that can be retrieved
/// using the GetInstruction method
////////////////////////////////
class InstructionRepository
{
public:

    ////////////////////////////////
    /// METHOD NAME: GetInstance
    ////////////////////////////////
    static InstructionRepository& GetInstance()
    {
        static InstructionRepository* pInstance = new InstructionRepository();
        return *pInstance;
    }

    ////////////////////////////////
    /// METHOD NAME: Initialize
    ///
    /// @brief Builds the instruction keyword dictionary
    ////////////////////////////////
    void Initialize();

    ////////////////////////////////
    /// METHOD NAME: GetInstruction
    ///
    /// @brief Retrieves an instance from
    /// the repository of the given instruction
    ///
    /// @param[in] rInstruction     Type of instruction to retrieve
    /// @param[in] rProcess         Process this instruction belongs to
    /// @return Instance of matching instruction
    ////////////////////////////////
    InstructionBase* GetInstruction(std::string& rInstruction, Process& rProcess);

    ////////////////////////////////
    /// METHOD NAME: GetInstructionStrings
    ///
    /// @return A list containing the instructions as strings
    ////////////////////////////////
    SLList<std::string> GetInstructionStrings() const { return m_instructionDict.GetKeys(); }

protected:

private:

    /// HashMap containing pairs of instruction keyword : instances of instruction class
    HashMap<InstructionBase*> m_instructionDict;

    /// Size used when initializing the HashMap
    static const uint8_t INSTRUCTION_DICT_SIZE = 43;

    /// HashMap containing pairs of conditional codes : CondCodeEnum
    HashMap<ConditionalCode> m_conditionalCodeDict;

    /// Number of conditional codes
    static const uint8_t NUMBER_OF_COND_CODES = 18;

    ////////////////////////////////
    /// METHOD NAME: CheckConditionalCode
    ///
    /// @brief Determines whether the given
    /// instruction should be executed depending
    /// on the conditional codes and flags. The conditional
    /// code will also be stripped.
    ///
    /// @param[in,out] rInstruction     Instruction to be executed
    /// @param[in] rRegisters           Registers of the process for this instruction
    /// @return Whether the instruction should be executed
    /// @retval true        - The instruction should be executed
    /// @retval false       - The instruction should become a nop
    ////////////////////////////////
    bool CheckConditionalCode(std::string& rInstruction, const Registers& rRegisters);

    ////////////////////////////////
    /// Constructor
    ///
    /// @note Private to ensure singleton
    ////////////////////////////////
    InstructionRepository() :
        m_instructionDict(HashMap<InstructionBase*>(INSTRUCTION_DICT_SIZE)),
        m_conditionalCodeDict(HashMap<ConditionalCode>(NUMBER_OF_COND_CODES))
    {}

    ////////////////////////////////
    /// Copy Constructer
    ////////////////////////////////
    InstructionRepository(InstructionRepository const&);

    ////////////////////////////////
    /// Assignment operator
    ////////////////////////////////
    InstructionRepository& operator=(InstructionRepository const&);

};

#endif