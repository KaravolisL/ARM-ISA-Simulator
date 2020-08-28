/////////////////////////////////
/// @file OpCodes.hpp
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef OP_CODES_HPP
#define OP_CODES_HPP

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
// (None)

// FORWARD DECLARATIONS
// (None)

////////////////////////////////
/// @enum OpCode
///
/// @brief Enum for all op codes
////////////////////////////////
enum class OpCode
{
    ADD,
    B,
    BL,
    BX,
    BLX,
    SUB,
    BIC,
    ORR,
    AND,
    EOR,
    LSL,
    LSR,
    CMP,
    CMN,
    TST,
    STR,
    LDR,
    PUSH,
    POP,
    STM,
    LDM,
    MOV,
    NOP,
    INVALID
};

#endif