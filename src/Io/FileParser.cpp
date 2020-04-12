/////////////////////////////////
/// @file FileParser.cpp
///
/// @brief <Brief description>
///
/// @details <Detailed description>
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <iostream>
#include <string>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "FileParser.hpp" // Header for class
#include "LineTypes.hpp" // For LineTypes enum

namespace Io
{

////////////////////////////////
/// METHOD NAME: Io::FileParser::GetCurrentLine
////////////////////////////////
std::string& FileParser::GetCurrentLine()
{
    std::string line
}

////////////////////////////////
/// METHOD NAME: Io::FileParser::CurrentLineType
////////////////////////////////
LineType FileParser::CurrentLineType()
{
    std::string line;
    while (std::getline(m_fileStream, line))
    {
        this->StripComment(line);
        std::cout << line.c_str() << "\n";
    }
    return LineType::INCLUDE;
}

////////////////////////////////
/// METHOD NAME: Io::FileParser::StripComment
////////////////////////////////
void FileParser::StripComment(std::string& line)
{
    size_t semicolonPos = line.find_first_of(';');

    if (semicolonPos == std::string::npos) 
    {
        return;
    }
    else
    {
        line = line.substr(0, semicolonPos);
    }
}

} // Io