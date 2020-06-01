/////////////////////////////////
/// @file MemoryInstruction.hpp
///
/// @brief Declaration of MemoryInstruction class
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef MEMORY_INSTRUCTION_HPP
#define MEMORY_INSTRUCTION_HPP

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "InstructionBase.hpp" // For InstructionBase
#include "Registers.hpp" // For Register

// FORWARD DECLARATIONS
// (None)

////////////////////////////////
/// @class MemoryInstruction
///
/// @brief Derived class for memory
/// instructions
////////////////////////////////
class MemoryInstruction : public InstructionBase
{
public:

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    MemoryInstruction(OpCode opCode) :
        InstructionBase(opCode),
        m_pDestinationRegister(nullptr),
        m_pAddressRegister(nullptr),
        // m_transferType(MemoryTransferType::INVALID)
        m_offset(0)
        // m_offsetType(OffsetType::INVALID)
    {};

    ////////////////////////////////
    /// METHOD NAME: Execute
    ///
    /// @brief Executes the given operation
    /// on the arguments and places the result
    /// into the destination
    ///
    /// @param[in,out] rProcessRegisters    Registers associated with process
    ////////////////////////////////
    void Execute(Registers& rProcessRegisters);

protected:

private:

    /// Pointer to the destination register
    Register* m_pDestinationRegister;

    /// Pointer to the register holding the base address
    Register* m_pAddressRegister;

    /// Type of memory transfer
    // MemoryTransferType m_transferType;

    /// Offset from base address
    uint32_t m_offset;

    /// Type of offset to perform
    // OffsetType m_offsetType

    ////////////////////////////////
    /// Copy Constructer
    ////////////////////////////////
    MemoryInstruction(MemoryInstruction const&);

    ////////////////////////////////
    /// Assignment operator
    ////////////////////////////////
    MemoryInstruction& operator=(MemoryInstruction const&);

};

#endif