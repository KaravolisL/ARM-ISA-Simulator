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
#include <assert.h>
#include <stdint.h>
#include <string>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "LineTypes.hpp" // For LineType enum

// FORWARD DECLARATIONS
template<typename T>
class List;

template<typename T>
class DLB;

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
    /// @param pLine    Reference to line to be parsed
    ////////////////////////////////
    LineParser(std::string* pLine);

    ////////////////////////////////
    /// METHOD NAME: SetLine
    ///
    /// @brief Updates the line being parsed
    ///
    /// @param[in] pNewLine     New line to be parsed
    ////////////////////////////////
    void SetLine(std::string* pNewLine);

    ////////////////////////////////
    /// METHOD NAME: GetLineType
    ///
    /// @brief Determine the what is stored
    /// at the current line
    ///
    /// @returns Type of the current line
    ////////////////////////////////
    LineType GetLineType() const;

    ////////////////////////////////
    /// METHOD NAME: GetFileName
    ///
    /// @brief Retrieves the file name 
    /// following an include directive
    ///
    /// @param[out] rFileName    Name of file to be included
    ////////////////////////////////
    void GetFileName(std::string& rFileName) const
    {
        assert(GetLineType() == LineType::INCLUDE);
        GetToken(1, rFileName);
    }

    ////////////////////////////////
    /// METHOD NAME: GetLabel
    ///
    /// @brief Retrieves the label 
    /// following an EQU directive or
    /// from a label line
    ///
    /// @param[out] rLabel    Label on line
    ////////////////////////////////
    void GetLabel(std::string& rLabel) const;

    ////////////////////////////////
    /// METHOD NAME: GetLabel
    ///
    /// @brief Retrieves the label 
    /// following an EQU directive or
    /// from a label line
    ///
    /// @return Label on the line
    ////////////////////////////////
    std::string GetLabel() const;

    ////////////////////////////////
    /// METHOD NAME: GetInstruction
    ///
    /// @brief Retrieves the instruction keyword
    ///
    /// @param[out] rInstruction    Instruction keyword
    ////////////////////////////////
    void GetInstruction(std::string& rInstruction) const;

    ////////////////////////////////
    /// METHOD NAME: Tokenize
    ///
    /// @brief Tokenizes the string using the 
    /// provided deliminators
    ///
    /// @param[out] rTokens     List of tokens
    /// @param[in] pDeliminators Deliminators to use when tokenizing
    ////////////////////////////////
    void Tokenize(List<std::string>& rTokens, const char* pDeliminators = " ,") const;

    ////////////////////////////////
    /// METHOD NAME: GetValue
    ///
    /// @brief Retrieves the value included
    /// in an EQU directive
    ///
    /// @param[in] rConstantsDictionary     Reference to constants dictionary
    ///                                     that's being created
    /// @returns value as int
    ////////////////////////////////
    int GetValue(DLB<uint32_t>& rConstantsDictionary) const;

    ////////////////////////////////
    /// METHOD NAME: GetLine
    ///
    /// @returns Line being parsed
    ////////////////////////////////
    std::string* GetLine() const { return m_pLine; }

    ////////////////////////////////
    /// METHOD NAME: GetTrimmedLine
    ///
    /// @returns Line trimmed of labels and 
    /// whitespace
    ////////////////////////////////
    std::string GetTrimmedLine() const;

protected:

private:

    ////////////////////////////////
    /// METHOD NAME: GetToken
    ///
    /// @brief Retrieves a given token from the line
    ///
    /// @param[in] index            Position of token
    /// @param[out] rToken          Reference to token
    /// @param[in] pDeliminators     Deliminators to use when tokenizing
    ////////////////////////////////
    void GetToken(int index, std::string& rToken, const char* deliminators = " ,") const;

    ////////////////////////////////
    /// METHOD NAME: GetNumberOfTokens
    ///
    /// @brief Retrieves the number of tokens on the line
    ///
    /// @return Number of tokens on the line
    ////////////////////////////////
    int GetNumberOfTokens() const;

    ////////////////////////////////
    /// METHOD NAME: StripComment
    ///
    /// @brief Strips the line of trailing comments
    ////////////////////////////////
    void StripComment();

    ////////////////////////////////
    /// METHOD NAME: WhitespaceTrim
    ///
    /// @brief Strips the leading and trailing white space
    ////////////////////////////////
    void WhitespaceTrim();

    /// Pointer to line being parsed
    std::string* m_pLine;

};

} // Io

#endif