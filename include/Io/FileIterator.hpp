/////////////////////////////////
/// @file FileIterator.hpp
///
/// @brief Declarations for FileIterator class
///
/// @details This class is used to iterate
/// through the lines of a given file
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef FILE_ITERATOR_HPP
#define FILE_ITERATOR_HPP

// SYSTEM INCLUDES
#include <fstream>
#include <string>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
// (None)

// FORWARD DECLARATIONS
// (None)

namespace Io
{

////////////////////////////////
/// @class Io::FileIterator
////////////////////////////////
class FileIterator
{
public:

    ////////////////////////////////
    /// Constructor
    ////////////////////////////////
    FileIterator(const std::string& fileName);

    ////////////////////////////////
    /// METHOD NAME: Next
    ///
    /// @brief Returns the next line in the file
    ///
    /// @returns Next line in file
    /// @throw EndOfFileException
    ////////////////////////////////
    std::string& Next();

    ////////////////////////////////
    /// METHOD NAME: HasNext
    ///
    /// @returns Whether there are more lines in the file
    ////////////////////////////////
    bool HasNext() const;

    ////////////////////////////////
    /// METHOD NAME: GoToLine
    ///
    /// @brief Resets iterator to a given line
    ///
    /// @param[in] lineNumber   Number of line to go to
    /// @returns Line that was seeked to
    /// @throw EndOfFileException
    ////////////////////////////////
    std::string& GoToLine(int lineNumber);

    ////////////////////////////////
    /// METHOD NAME: GetLineNumber
    ////////////////////////////////
    uint32_t GetLineNumber() { return m_lineNumber; }

    ////////////////////////////////
    /// METHOD NAME: GetCurrentLine
    ////////////////////////////////
    std::string& GetCurrentLine() { return m_currentLine;}

    ////////////////////////////////
    /// @struct EndOfFileException
    ////////////////////////////////
    struct EndOfFileException : public std::exception
    {
        const char* what() const throw()
        {
            return "End of File Exception";
        }
    };

protected:

private:

    /// Input file stream for main file containing assembly
    std::ifstream m_fileStream;

    /// Current line
    std::string m_currentLine;

    /// Line number
    uint32_t m_lineNumber;

};

} // Io

#endif