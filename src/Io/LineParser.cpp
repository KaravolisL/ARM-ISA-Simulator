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
#include "ExpressionParser.hpp" // For Io::ExpressionParser
#include "IndexOutOfBoundsException.hpp" // For IndexOutOfBoundsException
#include "LineTypes.hpp"  // For LineType enum
#include "KeywordDict.hpp" // For KeywordDict class
#include "Logger.hpp"

namespace Io
{

////////////////////////////////
/// Constructor
////////////////////////////////
LineParser::LineParser(std::string& rLine) :
    m_rLine(rLine)
{
    // Strip comment and whitespace when constructed
    this->StripComment();
    // Must be done after stripping the comment
    this->WhitespaceTrim();
}

////////////////////////////////
/// METHOD NAME: Io::LineParser::GetLineType
////////////////////////////////
LineType LineParser::GetLineType()
{
    if (m_rLine.size() == 0) return LineType::COMMENT;

    std::string token;
    this->GetToken(0, token);

    // Look for the keyword in the keyword dictionary
    LineType lineType = KeywordDict::GetInstance().Get(token);

    // Label may be returned for a label, EQU, or memory directive
    if (lineType == LineType::LABEL)
    {
        if (m_rLine.find("EQU") != std::string::npos)
        {
            lineType = LineType::EQU;
        }
        else if (m_rLine.find("DCB") != std::string::npos)
        {
            lineType = LineType::DCB;
        }
    }

    return lineType;
}

////////////////////////////////
/// METHOD NAME: Io::LineParser::GetValue
////////////////////////////////
int LineParser::GetValue(DLB<uint32_t>& rConstantsDictionary)
{
    std::string expression;
    GetToken(2, expression);

    // Make the expression the entire enclosure if necessary
    if (expression[0] == '(')
    {
        expression = m_rLine.substr(m_rLine.find_first_of('('));
    }

    // Create an expression parser and evaluate
    ExpressionParser exParser(expression, rConstantsDictionary);
    return exParser.Evaluate();
}

////////////////////////////////
/// METHOD NAME: Io::LineParser::GetToken
////////////////////////////////
void LineParser::GetToken(int index, std::string& rToken)
{
    // Copy line so it can be modified
    char* lineCopy = new char[m_rLine.length() + 1];
    assert(m_rLine.copy(lineCopy, m_rLine.length(), 0) == m_rLine.length());
    // Copy doesn't add the null terminator
    lineCopy[m_rLine.length()] = '\0';

    char* pToken = strtok(lineCopy, " ,");

    // Iterate through tokens
    for (int i = 0; i < index; i++)
    {
        pToken = strtok(NULL, " ,");
    }

    if (pToken == NULL) throw new IndexOutOfBoundsException();

    // Store string in given parameter
    rToken = std::string(pToken);

    delete[] lineCopy;

    assert(pToken != NULL);
}

////////////////////////////////
/// METHOD NAME: Io::LineParser::StripComment
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

////////////////////////////////
/// METHOD NAME: Io::LineParser::WhitespaceTrim
////////////////////////////////
void LineParser::WhitespaceTrim()
{
    static const std::string WHITESPACE = " \n\r\t\f\v";
	size_t start = m_rLine.find_first_not_of(WHITESPACE);
	m_rLine = (start == std::string::npos) ? "" : m_rLine.substr(start);
    size_t end = m_rLine.find_last_not_of(WHITESPACE);
	m_rLine = (end == std::string::npos) ? "" : m_rLine.substr(0, end + 1);
}

} // Io