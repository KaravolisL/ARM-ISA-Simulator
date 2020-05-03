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
#include "DLB.hpp" // For DLB

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

protected:

private:

    /// DLB containing pairs of instruction keyword : instances of instruction class
    DLB<InstructionBase*> m_instructionDict;

    ////////////////////////////////
    /// Constructor
    ///
    /// @note Private to ensure singleton
    ////////////////////////////////
    InstructionRepository() :
        m_instructionDict(DLB<InstructionBase*>())
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