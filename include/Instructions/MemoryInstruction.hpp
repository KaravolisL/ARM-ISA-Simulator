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
#include "MemoryTransferTypes.hpp" // For MemoryTranferType enum
#include "OffsetTypes.hpp" // For OffsetType enum

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
        m_pDestOrSrcRegister(nullptr),
        m_pAddressRegister(nullptr),
        m_transferType(MemoryTransferType::WORD),
        m_offset(0),
        m_offsetType(OffsetType::ZERO)
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

    ////////////////////////////////
    /// METHOD NAME: SetDestOrSrcRegister
    ////////////////////////////////
    void SetDestOrSrcRegister(Register* pDestinationRegister) { m_pDestOrSrcRegister = pDestinationRegister; }

    ////////////////////////////////
    /// METHOD NAME: SetAddressRegister
    ////////////////////////////////
    void SetAddressRegister(Register* pAddressRegister) { m_pAddressRegister = pAddressRegister; }

    ////////////////////////////////
    /// METHOD NAME: SetTransferType
    ////////////////////////////////
    void SetTransferType(MemoryTransferType transferType) { m_transferType = transferType; }

    ////////////////////////////////
    /// METHOD NAME: GetTransferType
    ////////////////////////////////
    MemoryTransferType GetTransferType() const { return m_transferType; }

    ////////////////////////////////
    /// METHOD NAME: SetOffset
    ////////////////////////////////
    void SetOffset(uint32_t offset) { m_offset = offset; }

    ////////////////////////////////
    /// METHOD NAME: SetOffsetType
    ////////////////////////////////
    void SetOffsetType(OffsetType offsetType) { m_offsetType = offsetType; }

    ////////////////////////////////
    /// METHOD NAME: SetAddressRegisterToOffset
    ///
    /// @brief This method is used when the address
    /// for the instruction comes from the constants dictionary
    /// In this case, it will be stored in the offset member variable
    ////////////////////////////////
    void SetAddressRegisterToOffset() { m_pAddressRegister = reinterpret_cast<Register*>(&m_offset); }

protected:

private:

    /// Pointer to the destination or source register
    Register* m_pDestOrSrcRegister;

    /// Pointer to the register holding the base address
    Register* m_pAddressRegister;

    /// Type of memory transfer
    MemoryTransferType m_transferType;

    /// Offset from base address
    uint32_t m_offset;

    /// Type of offset to perform
    OffsetType m_offsetType;

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