/////////////////////////////////
/// @file FileParser.hpp
///
/// @brief <Brief description>
///
/// @details <Detailed description>
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef FILE_PARSER_HPP
#define FILE_PARSER_HPP

// SYSTEM INCLUDES
#include <stdint.h>
#include <fstream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "LineTypes.hpp" // For LineTypes enum

// FORWARD DECLARATIONS
// (None)

namespace Io
{

////////////////////////////////
/// @class FileParser
///
/// @brief <Brief description>
////////////////////////////////
class FileParser
{
public:

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    FileParser(const char* filename) :
        m_fileStream(std::ifstream(filename, std::ifstream::in)),
        m_currentPos(0),
        m_currentLine("")
    {}

    ////////////////////////////////
    /// METHOD NAME: CurrentLineType
    ///
    /// @brief Determine the what is stored
    /// at the current line
    ///
    /// @returns Type of the current line
    ////////////////////////////////
    LineType CurrentLineType();

    ////////////////////////////////
    /// METHOD NAME: GetCurrentLine
    ///
    /// @note File is read then seekg 
    /// is used to "rewind"
    ///
    /// @return Current line being pointed to
    ////////////////////////////////
    std::string& GetCurrentLine(); 

protected:

private:

    ////////////////////////////////
    /// METHOD NAME: StripComment
    ///
    /// @brief Strips a line of trailing comments
    ///
    /// @param[in,out] line     Line to modify
    ////////////////////////////////
    void StripComment(std::string& line);

    /// Input file stream for main file containing assembly
    std::ifstream m_fileStream;

    /// Line number at which the file parser is currently on
    std::streampos m_currentPos;

    /// Current line being parsed
    std::string m_currentLine;

};

} // Io

#endif