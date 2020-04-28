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
    Register r0;
    Register r1;
    Register r2;
    Register r3;
    Register r4;
    Register r5;
    Register r6;
    Register r7;
    Register r8;
    Register r9;
    Register r10;
    Register r11;
    Register r12;
    Register LR;
    Register PC;
    Register SP;

    Registers() :
        r0(0),
        r1(0),
        r2(0),
        r3(0),
        r4(0),
        r5(0),
        r6(0),
        r7(0),
        r8(0),
        r9(0),
        r10(0),
        r11(0),
        r12(0),
        LR(0),
        PC(0),
        SP(0)
    {}

} Registers;

#endif
