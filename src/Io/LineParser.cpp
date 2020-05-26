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
#include <iostream>
#include <string.h>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "LineParser.hpp" // Header for class
#include "Assert.hpp" // For ASSERT
#include "ExpressionParser.hpp" // For Io::ExpressionParser
#include "IndexOutOfBoundsException.hpp" // For IndexOutOfBoundsException
#include "LineTypes.hpp"  // For LineType enum
#include "KeywordDict.hpp" // For KeywordDict class
#include "SLList.hpp" // For SLList

namespace Io
{

////////////////////////////////
/// Constructor
////////////////////////////////
LineParser::LineParser(std::string* pLine) :
    m_pLine(pLine)
{
    // Strip comment and whitespace when constructed
    this->StripComment();
    // Must be done after stripping the comment
    this->WhitespaceTrim();
}

////////////////////////////////
/// METHOD NAME: Io::LineParser::SetLine
////////////////////////////////
void LineParser::SetLine(std::string* pNewLine)
{
    m_pLine = pNewLine;
    this->StripComment();
    this->WhitespaceTrim();
}

////////////////////////////////
/// METHOD NAME: Io::LineParser::GetLineType
////////////////////////////////
LineType LineParser::GetLineType() const
{
    if (m_pLine->size() == 0) return LineType::COMMENT;

    std::string token;
    this->GetToken(0, token);

    // Look for the keyword in the keyword dictionary
    LineType lineType = KeywordDict::GetInstance().Get(token);

    // Label may be returned for a label, EQU, or memory directive
    if (lineType == LineType::LABEL)
    {
        // Check if the line contains additional tokens that would make it another
        // type of line
        if (GetNumberOfTokens() > 1)
        {
            // Reevaluate line using the second token
            this->GetToken(1, token);
            lineType = KeywordDict::GetInstance().Get(token);
            if (lineType == Io::LineType::INSTRUCTION)
            {
                lineType = Io::LineType::LABEL_AND_INSTRUCTION;
            }
        }
    }

    return lineType;
}

////////////////////////////////
/// METHOD NAME: Io::LineParser::GetValue
////////////////////////////////
int LineParser::GetValue(DLB<uint32_t>& rConstantsDictionary) const
{
    std::string expression;
    GetToken(2, expression);

    // Make the expression the entire enclosure if necessary
    if (expression[0] == '(')
    {
        expression = m_pLine->substr(m_pLine->find_first_of('('));
    }

    // Create an expression parser and evaluate
    ExpressionParser exParser(expression, &rConstantsDictionary);
    return exParser.Evaluate();
}

////////////////////////////////
/// METHOD NAME: Io::LineParser::GetInstruction
////////////////////////////////
void LineParser::GetInstruction(std::string& rInstruction) const
{
    if (GetLineType() == LineType::INSTRUCTION)
    {
        GetToken(0, rInstruction);
    }
    else if (GetLineType() == LineType::LABEL_AND_INSTRUCTION)
    {
        GetToken(1, rInstruction);
    }
    else
    {
        ASSERT(false, "Unsupported line type");
    }
}

////////////////////////////////
/// METHOD NAME: Io::LineParser::GetArguments
////////////////////////////////
void LineParser::GetArguments(SLList<std::string>& rArguments) const
{
    // Start with the second token in the line unless it's a label and instruction line
    int i = 1;
    if (GetLineType() == LABEL_AND_INSTRUCTION)
    {
        i = 2;
    }

    while (true)
    {
        std::string token;
        try
        {
            GetToken(i++, token);
        }
        catch(const IndexOutOfBoundsException& e)
        {
            break;
        }
        rArguments.InsertBack(token);
    }
}

////////////////////////////////
/// METHOD NAME: Io::LineParser::GetTrimmedLine
////////////////////////////////
std::string LineParser::GetTrimmedLine() const
{
    std::string trimmedLine = *m_pLine;
    if (GetLineType() == LABEL_AND_INSTRUCTION)
    {
        std::string label;
        GetLabel(label);

        trimmedLine.erase(0, label.length() + 1);
    }
    return trimmedLine;
}

////////////////////////////////
/// METHOD NAME: Io::LineParser::GetToken
////////////////////////////////
void LineParser::GetToken(int index, std::string& rToken) const
{
    // Copy line so it can be modified
    char* lineCopy = new char[m_pLine->length() + 1];
    ASSERT(m_pLine->copy(lineCopy, m_pLine->length(), 0) == m_pLine->length(), "Failed to copy string");
    // Copy doesn't add the null terminator
    lineCopy[m_pLine->length()] = '\0';

    char* pToken = strtok(lineCopy, " ,{}");

    // Iterate through tokens
    int i;
    for (i = 0; i < index; i++)
    {
        pToken = strtok(NULL, " ,{}");
    }

    if (pToken == NULL) throw IndexOutOfBoundsException(i);

    // Store string in given parameter
    rToken = std::string(pToken);

    delete[] lineCopy;

    ASSERT(pToken != NULL);
}

////////////////////////////////
/// METHOD NAME: Io::LineParser::GetNumberOfTokens
////////////////////////////////
int LineParser::GetNumberOfTokens() const
{
    for (int i = 0; ; i++)
    {
        try
        {
            std::string dummyToken;
            GetToken(i, dummyToken);
        }
        catch(const IndexOutOfBoundsException& e)
        {
            return i;
        }
    }
}

////////////////////////////////
/// METHOD NAME: Io::LineParser::StripComment
////////////////////////////////
void LineParser::StripComment()
{
    size_t semicolonPos = m_pLine->find_first_of(';');

    if (semicolonPos == std::string::npos)
    {
        return;
    }
    else
    {
        *m_pLine = m_pLine->substr(0, semicolonPos);
    }
}

////////////////////////////////
/// METHOD NAME: Io::LineParser::WhitespaceTrim
////////////////////////////////
void LineParser::WhitespaceTrim()
{
    static const std::string WHITESPACE = " \n\r\t\f\v";
	size_t start = m_pLine->find_first_not_of(WHITESPACE);
	*m_pLine = (start == std::string::npos) ? "" : m_pLine->substr(start);
    size_t end = m_pLine->find_last_not_of(WHITESPACE);
	*m_pLine = (end == std::string::npos) ? "" : m_pLine->substr(0, end + 1);
}

} // Io