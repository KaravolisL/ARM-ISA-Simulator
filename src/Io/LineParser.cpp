/////////////////////////////////
/// @file LineParser.cpp
///
/// @brief Implementation of LineParser class
///
/// @copydetail LineParser
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>
#include <iostream>
#include <string.h>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "LineParser.hpp" // Header for class

namespace Io
{

////////////////////////////////
/// Constructor
////////////////////////////////
LineParser::LineParser(std::string& rLine) :
    m_rLine(rLine)
{
    // Strip comment when constructed
    this->StripComment();
}

////////////////////////////////
/// METHOD NAME: Io::LineParser::GetLineType
////////////////////////////////
LineParser::LineType LineParser::GetLineType()
{
    if (m_rLine.size() == 0) return LineParser::LineType::COMMENT;

    std::string token;
    this->GetToken(0, token);

    if (token == "INCLUDE")
    {
        return LineParser::LineType::INCLUDE;
    }


    return LineParser::LineType::INVALID;
}

////////////////////////////////
/// METHOD NAME: Io::LineParser::GetToken
////////////////////////////////
void LineParser::GetToken(int index, std::string& rToken)
{
    // Copy line so it can be modified
    char lineCopy[m_rLine.length()];
    m_rLine.copy(lineCopy, m_rLine.length(), 0);

    char* pToken = strtok(lineCopy, " ,");

    // Iterate through tokens
    for (int i = 0; i < index; i++)
    {
        pToken = strtok(NULL, " ,");
    }

    // Store string in given parameter
    rToken = std::string(pToken);

    assert(pToken != NULL);
}

////////////////////////////////
/// METHOD NAME: Io::FileParser::StripComment
////////////////////////////////
void LineParser::StripComment()
{
    size_t semicolonPos = m_rLine.find_first_of(';');

    if (semicolonPos == std::string::npos)
    {
        return;
    }
    else
    {
        m_rLine = m_rLine.substr(0, semicolonPos);
    }
}

} // Io