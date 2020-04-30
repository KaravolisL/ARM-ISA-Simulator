#include "FileIterator.hpp"

namespace Io
{

std::string& FileIterator::GoToLine(int lineNumber)
{
    return m_currentLine;
}

}