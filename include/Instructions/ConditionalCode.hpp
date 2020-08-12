/////////////////////////////////
/// @file ConditionalCodes.hpp
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef CONDITIONAL_CODES_HPP
#define CONDITIONAL_CODES_HPP

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
// (None)

// FORWARD DECLARATIONS
// (None)

////////////////////////////////
/// @enum ConditionalCode
///
/// @brief Enum for types of conditional codes
////////////////////////////////
enum class ConditionalCode
{
    EQ = 0, // Z == 1
    NE = 1, // Z == 0
    GT = 2, // Z == 0 && N == V
    LT = 3, // N != V
    GE = 4, // N == V
    LE = 5, // Z == 1 || N != V
    CS = 6, // C == 1 A.K.A HS
    CC = 7, // C == 0 A.K.A LO
    MI = 8, // N == 1
    PL = 9, // N == 0
    AL = 10, // Always
    NV = 11, // Never
    VS = 12, // V == 1
    VC = 13, // V == 0
    HI = 14, // C == 1 && Z == 0
    LS = 15 // C == 0 || Z == 0
};

#endif