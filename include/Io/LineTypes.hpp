/////////////////////////////////
/// @file LineTypes.hpp
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
/// @brief Enum for line types in a file
///
/// @details This enum is used by both the FileParser
/// class and the Process class in order to 
/// determine how the current line that's being parsed
/// should be handled
////////////////////////////////
enum LineType
{
    INCLUDE,
    LABEL,
    INSTRUCTION,
    COMMENT,
    EQU,
    AREA,
    EXPORT,
    ENTRY,
    ALIGN,
    END,
    ENDP,
    DCB,
    DCD,
    LABEL_AND_INSTRUCTION,
    LABEL_AND_PROC,
    INVALID
};

} // Io

#endif