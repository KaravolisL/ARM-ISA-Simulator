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

    /////////////////////////////////////
    /// @brief Constructs a new MemoryInstruction object
    ///
    /// @param[in] opCode Opcode of the instruction
    /////////////////////////////////////
    MemoryInstruction(OpCode opCode) :
        InstructionBase(opCode),
        m_pDestOrSrcRegister(nullptr),
        m_pAddressRegister(nullptr),
        m_transferType(MemoryTransferType::WORD),
        m_offset(0),
        m_offsetType(OffsetType::ZERO)
    {};

    ////////////////////////////////
    /// @brief Executes the given operation
    /// on the arguments and places the result
    /// into the destination
    ///
    /// @param[in,out] rProcessRegisters    Registers associated with process
    ////////////////////////////////
    void Execute(Registers& rProcessRegisters);

    /////////////////////////////////////
    /// @brief Sets the DestOrSrcRegister member
    ///
    /// @param[in] pDestinationRegister Pointer to the destination
    /// or source register
    /////////////////////////////////////
    void SetDestOrSrcRegister(Register* pDestinationRegister) { m_pDestOrSrcRegister = pDestinationRegister; }

    /////////////////////////////////////
    /// @brief Sets the AddressRegister member
    /// 
    /// @param[in] pAddressRegister Pointer to the register
    /// containing the memory address
    /////////////////////////////////////
    void SetAddressRegister(Register* pAddressRegister) { m_pAddressRegister = pAddressRegister; }

    /////////////////////////////////////
    /// @brief Sets the TransferType member
    ///
    /// @param[in] transferType 
    /////////////////////////////////////
    void SetTransferType(MemoryTransferType transferType) { m_transferType = transferType; }

    /////////////////////////////////////
    /// @brief Gets the TransferType member
    ///
    /// @return Instruction's transfer type
    /////////////////////////////////////
    MemoryTransferType GetTransferType() const { return m_transferType; }

    /////////////////////////////////////
    /// @brief Sets the Offset member
    ///
    /// @param[in] offset Offset for instruction
    /////////////////////////////////////
    void SetOffset(int32_t offset) { m_offset = offset; }

    /////////////////////////////////////
    /// @brief Sets the OffsetType member
    ///
    /// @param[in] offsetType Type of offset to be performed
    /////////////////////////////////////
    void SetOffsetType(OffsetType offsetType) { m_offsetType = offsetType; }

protected:

private:

    /// Pointer to the destination or source register
    Register* m_pDestOrSrcRegister;

    /// Pointer to the register holding the base address
    Register* m_pAddressRegister;

    /// Type of memory transfer
    MemoryTransferType m_transferType;

    /// Offset from base address
    int32_t m_offset;

    /// Type of offset to perform
    OffsetType m_offsetType;

    ////////////////////////////////
    /// @brief Copy Constructer
    ////////////////////////////////
    MemoryInstruction(MemoryInstruction const&);

    ////////////////////////////////
    /// @brief Assignment operator
    ////////////////////////////////
    MemoryInstruction& operator=(MemoryInstruction const&);

};

#endif