/////////////////////////////////
/// @file OffestTypes.hpp
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef OFFSET_TYPES_HPP
#define OFFSET_TYPES_HPP

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
// (None)

// FORWARD DECLARATIONS
// (None)

////////////////////////////////
/// @enum OffsetType
///
/// @brief Enum for types of offsets
////////////////////////////////
enum class OffsetType
{
    ZERO,
    PREINDEXED,
    PREINDEXED_WITH_UPDATE,
    POSTINDEXED
};

#endif