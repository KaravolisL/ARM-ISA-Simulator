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

// FORWARD DECLARATIONS
class InstructionBase;

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
    /// @return Instance of matching instruction
    ////////////////////////////////
    InstructionBase* GetInstruction(const std::string& rInstruction);

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
    static const uint8_t INITIAL_SIZE = 43;

    ////////////////////////////////
    /// Constructor
    ///
    /// @note Private to ensure singleton
    ////////////////////////////////
    InstructionRepository() :
        m_instructionDict(HashMap<InstructionBase*>(INITIAL_SIZE))
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