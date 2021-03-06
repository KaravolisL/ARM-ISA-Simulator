/////////////////////////////////
/// @file FileIterator.cpp
///
/// @brief Implementation of FileIterator
///
/// @copydetail FileIterator
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <istream>
#include <string>
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "FileIterator.hpp" // Header for class
#include "AssemblingException.hpp" // For AssemblingException

namespace Io
{

////////////////////////////////
/// Constructor
////////////////////////////////
FileIterator::FileIterator(const std::string& fileName) :
    m_fileStream(std::ifstream(fileName, std::ifstream::in)),
    m_currentLine(""),
    m_lineNumber(0)
{
    if (!m_fileStream.is_open()) { throw AssemblingException("File not found", fileName, 0); }
} 

////////////////////////////////
/// METHOD NAME: HasNext
////////////////////////////////
bool FileIterator::HasNext() const
{
    return !m_fileStream.eof();
}

////////////////////////////////
/// METHOD NAME: Next
////////////////////////////////
std::string& FileIterator::Next()
{
    if (!this->HasNext())
    {
        // We must clear the error before continuing
        m_fileStream.clear();
        throw FileIterator::EndOfFileException();
    } 

    std::getline(m_fileStream, m_currentLine);
    m_lineNumber++;

    return m_currentLine;
}

////////////////////////////////
/// METHOD NAME: GoToLine
////////////////////////////////
std::string& FileIterator::GoToLine(int lineNumber)
{
    m_fileStream.seekg(0);
    m_lineNumber = 0;
    for (int i = 0; i < lineNumber; i++)
    {
        // Iterate through the lines
        this->Next();
    }
    return m_currentLine;
}


} // Io