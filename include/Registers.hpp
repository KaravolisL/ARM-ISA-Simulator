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
    Register genRegs[13];
    Register LR;
    Register PC;
    Register SP;
    Register CPSR;

    Registers() :
        LR(0),
        PC(0),
        SP(0),
        CPSR(0)
    {}

    /////////////////////////////////
    /// METHOD NAME: GetNegativeFlag
    /////////////////////////////////
    bool GetNegativeFlag() { return (CPSR & 0x80000000) != 0; }

    /////////////////////////////////
    /// METHOD NAME: SetNegativeFlag
    /////////////////////////////////
    void SetNegativeFlag() { CPSR |= 0x80000000; }

    /////////////////////////////////
    /// METHOD NAME: ClearNegativeFlag
    /////////////////////////////////
    void ClearNegativeFlag() { CPSR &= ~(0x80000000); }

    /////////////////////////////////
    /// METHOD NAME: GetZeroFlag
    /////////////////////////////////
    bool GetZeroFlag() { return (CPSR & 0x40000000) != 0; }

    /////////////////////////////////
    /// METHOD NAME: SetZeroFlag
    /////////////////////////////////
    void SetZeroFlag() { CPSR |= 0x40000000; }

    /////////////////////////////////
    /// METHOD NAME: ClearZeroFlag
    /////////////////////////////////
    void ClearZeroFlag() { CPSR &= ~(0x40000000); }

    /////////////////////////////////
    /// METHOD NAME: GetCarryFlag
    /////////////////////////////////
    bool GetCarryFlag() { return (CPSR & 0x20000000) != 0; }

    /////////////////////////////////
    /// METHOD NAME: SetCarryFlag
    /////////////////////////////////
    void SetCarryFlag() { CPSR |= 0x20000000; }

    /////////////////////////////////
    /// METHOD NAME: ClearCarryFlag
    /////////////////////////////////
    void ClearCarryFlag() { CPSR &= ~(0x20000000); }

    /////////////////////////////////
    /// METHOD NAME: GetOverflowFlag
    /////////////////////////////////
    bool GetOverflowFlag() { return (CPSR & 0x10000000) != 0; }

    /////////////////////////////////
    /// METHOD NAME: SetOverflowFlag
    /////////////////////////////////
    void SetOverflowFlag() { CPSR |= 0x10000000; }

    /////////////////////////////////
    /// METHOD NAME: ClearOverflowFlag
    /////////////////////////////////
    void ClearOverflowFlag() { CPSR &= ~(0x10000000); }

} Registers;

#endif
