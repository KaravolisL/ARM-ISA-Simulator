/////////////////////////////////
/// @file LineParser.hpp
///
/// @brief Declaration for LineParser class
///
/// @details This class is used to parse a given
/// line in a file. It includes methods to get the
/// type of line, instructions, and arguments
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef LINE_PARSER_HPP
#define LINE_PARSER_HPP

// SYSTEM INCLUDES
#include <stdint.h>
#include <string>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "LineTypes.hpp" // For LineType enum

// FORWARD DECLARATIONS
// (None)

namespace Io
{

////////////////////////////////
/// @class LineParser
////////////////////////////////
class LineParser
{
public:

    ////////////////////////////////
    /// Constructor
    ///
    /// @param rLine    Reference to line to be parsed
    ////////////////////////////////
    LineParser(std::string& rLine);

    ////////////////////////////////
    /// METHOD NAME: GetLineType
    ///
    /// @brief Determine the what is stored
    /// at the current line
    ///
    /// @returns Type of the current line
    ////////////////////////////////
    LineType GetLineType();

    ////////////////////////////////
    /// METHOD NAME: GetInstruction
    ///
    /// @brief Retrieves the instruction 
    /// from the line being parsed
    ///
    /// 
    ////////////////////////////////
    void GetInstruction();

protected:

private:

    ////////////////////////////////
    /// METHOD NAME: GetToken
    ///
    /// @brief Retrieves a given token from the line
    ///
    /// @param[in] index    Position of token
    /// @param[out] rToken  Reference to token
    ////////////////////////////////
    void GetToken(int index, std::string& rToken);

    ////////////////////////////////
    /// METHOD NAME: StripComment
    ///
    /// @brief Strips the line of trailing comments
    ////////////////////////////////
    void StripComment();

    /// Reference to line being parsed
    std::string& m_rLine;

};

} // Io

#endif