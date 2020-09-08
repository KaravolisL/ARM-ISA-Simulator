/////////////////////////////////
/// @file Registers.hpp
///
/// @brief Declarations of register types
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef REGISTERS_HPP
#define REGISTERS_HPP

// SYSTEM INCLUDES
#include <stdint.h>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
// (None)

// FORWARD DECLARATIONS
// (None)

typedef uint32_t Register;

/////////////////////////////////
/// @struct Registers
///
/// @brief Group of registers given
/// to each process
/////////////////////////////////
typedef struct Registers
{
    /// General registers R0 - R14
    Register genRegs[14];

    /// Link Register
    Register LR;

    /// Program Counter
    Register PC;

    /// Stack Pointer
    Register SP;

    /// Flags
    Register CPSR;

    /////////////////////////////////////
    /// @brief Constructs a new Registers object
    /////////////////////////////////////
    Registers() :
        LR(0),
        PC(0),
        SP(0),
        CPSR(0)
    {}

    /////////////////////////////////////
    /// @brief Gets the N flag
    ///
    /// @return Bit 31
    /////////////////////////////////////
    bool GetNegativeFlag() const { return (CPSR & 0x80000000) != 0; }

    /////////////////////////////////////
    /// @brief Sets the N flag
    /////////////////////////////////////
    void SetNegativeFlag() { CPSR |= 0x80000000; }

    /////////////////////////////////////
    /// @brief Clears the N flag
    /////////////////////////////////////
    void ClearNegativeFlag() { CPSR &= ~(0x80000000); }

    /////////////////////////////////////
    /// @brief Gets the Z flag
    ///
    /// @return Bit 30
    /////////////////////////////////////
    bool GetZeroFlag() const { return (CPSR & 0x40000000) != 0; }

    /////////////////////////////////////
    /// @brief Sets the Z flag
    /////////////////////////////////////
    void SetZeroFlag() { CPSR |= 0x40000000; }

    /////////////////////////////////////
    /// @brief Clears the Z flag
    /////////////////////////////////////
    void ClearZeroFlag() { CPSR &= ~(0x40000000); }

    /////////////////////////////////////
    /// @brief Gets the C flag
    ///
    /// @return Bit 29
    /////////////////////////////////////
    bool GetCarryFlag() const { return (CPSR & 0x20000000) != 0; }

    /////////////////////////////////////
    /// @brief Sets the C flag
    /////////////////////////////////////
    void SetCarryFlag() { CPSR |= 0x20000000; }

    /////////////////////////////////////
    /// @brief Clears the C flag
    /////////////////////////////////////
    void ClearCarryFlag() { CPSR &= ~(0x20000000); }

    /////////////////////////////////////
    /// @brief Gets the V flag
    ///
    /// @return Bit 28
    /////////////////////////////////////
    bool GetOverflowFlag() const { return (CPSR & 0x10000000) != 0; }

    /////////////////////////////////////
    /// @brief Sets the V flag
    /////////////////////////////////////
    void SetOverflowFlag() { CPSR |= 0x10000000; }

    /////////////////////////////////////
    /// @brief Clears the V flag
    /////////////////////////////////////
    void ClearOverflowFlag() { CPSR &= ~(0x10000000); }

} Registers;

#endif
