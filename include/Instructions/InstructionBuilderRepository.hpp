/////////////////////////////////
/// @file InstructionBuilderRepository.hpp
///
/// @brief Declarations for InstructionBuilderRepository
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef INSTRUCTION_BUILDER_REPOSITORY_HPP
#define INSTRUCTION_BUILDER_REPOSITORY_HPP

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "OpCodes.hpp" // For OpCode enum

// FORWARD DECLARATIONS
class InstructionBuilder;

////////////////////////////////
/// @class InstructionBuilderRepository
///
/// @brief This class holds instances
/// of instruction builder classes that can be retrieved
/// using the GetInstructionBuilder method
////////////////////////////////
class InstructionBuilderRepository
{
public:

    ////////////////////////////////
    /// METHOD NAME: GetInstance
    ////////////////////////////////
    static InstructionBuilderRepository& GetInstance()
    {
        static InstructionBuilderRepository* pInstance = new InstructionBuilderRepository();
        return *pInstance;
    }

    ////////////////////////////////
    /// METHOD NAME: GetInstructionBuilder
    ///
    /// @brief Retrieves an instance from
    /// the repository of the given instruction builder
    ///
    /// @param[in] opCode   OpCode used when determining what kind of builder to retrieve
    /// @return Instance of matching instruction builder
    ////////////////////////////////
    static InstructionBuilder* GetInstructionBuilder(const OpCode opCode);

protected:

private:

    ////////////////////////////////
    /// Constructor
    ///
    /// @note Private to ensure singleton
    ////////////////////////////////
    InstructionBuilderRepository();

    ////////////////////////////////
    /// Copy Constructer
    ////////////////////////////////
    InstructionBuilderRepository(InstructionBuilderRepository const&);

    ////////////////////////////////
    /// Assignment operator
    ////////////////////////////////
    InstructionBuilderRepository& operator=(InstructionBuilderRepository const&);

};

#endif