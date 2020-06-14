/////////////////////////////////
/// @file MemoryTransferTypes.hpp
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef MEMORY_TRANSFER_TYPES_HPP
#define MEMORY_TRANSFER_TYPES_HPP

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
// (None)

// FORWARD DECLARATIONS
// (None)

////////////////////////////////
/// @enum MemoryTransferType
///
/// @brief Enum for the memory transfer types
////////////////////////////////
enum MemoryTransferType
{
    WORD,
    UNSIGNED_BYTE, // B
    SIGNED_BYTE, // SB (LDR only)
    UNSIGNED_HALFWORD, // H
    SIGNED_HALFWORD // SH (LDR only)
};

#endif