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
    bool GetNegativeFlag() { return (CPSR & ~(0x8000000)) != 0; }

    /////////////////////////////////
    /// METHOD NAME: GetZeroFlag
    /////////////////////////////////
    bool GetZeroFlag() { return (CPSR & ~(0x40000000)) != 0; }

    /////////////////////////////////
    /// METHOD NAME: GetCarryFlag
    /////////////////////////////////
    bool GetCarryFlag() { return (CPSR & ~(0x200000000)) != 0; }

    /////////////////////////////////
    /// METHOD NAME: GetOverflowFlag
    /////////////////////////////////
    bool GetOverflowFlag() { return (CPSR & ~(0x10000000)) != 0; }

} Registers;

#endif
