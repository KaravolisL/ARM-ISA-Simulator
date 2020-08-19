#include "FileIterator.hpp"

namespace Io
{

std::string& FileIterator::GoToLine(int lineNumber)
{
    return m_currentLine;
}

FileIterator::FileIterator(const std::string& rFileName) :
    m_fileStream(std::ifstream("MockFile.txt")),
    m_currentLine(""),
    m_lineNumber(0)
{

}

}