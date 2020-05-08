/////////////////////////////////
/// @file InstructionTypes.hpp
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef INSTRUCTION_TYPES_HPP
#define INSTRUCTION_TYPES_HPP

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
// (None)

// FORWARD DECLARATIONS
// (None)

////////////////////////////////
/// @enum InstructionType
///
/// @brief Enum for types of instructions
////////////////////////////////
enum InstructionType
{
    ARITHMETIC,
    LOGIC,
    COMPARISON,
    FLOW_CTRL,
    MEMORY,
    OTHER
};

#endif