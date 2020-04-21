/////////////////////////////////
/// @file LineTypes.hpp
///
/// @brief Enum for line types in a file
///
/// @details This enum is used by both the FileParser
/// class and the Process class in order to 
/// determine how the current line that's being parsed
/// should be handled
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef LINE_TYPE_HPP
#define LINE_TYPE_HPP

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
// (None)

// FORWARD DECLARATIONS
// (None)

namespace Io
{

////////////////////////////////
/// @enum LineType
///
/// @brief <Brief description>
////////////////////////////////
enum LineType
{
    INCLUDE,
    LABEL,
    INSTRUCTION,
    COMMENT,
    AREA,
    EXPORT,
    ENTRY,
    ALIGN,
    END,
    INVALID
};

} // Io

#endif