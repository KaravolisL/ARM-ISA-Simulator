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
enum OpCode
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
    CMP,
    CMN,
    STR,
    LDR,
    PUSH,
    POP,
    MOV,
    NOP,
    INVALID
};

#endif