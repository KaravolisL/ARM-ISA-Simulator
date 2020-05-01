/////////////////////////////////
/// @file InvalidSyntaxException.hpp
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef INVALID_SYNTAX_EXCEPTION_HPP
#define INVALID_SYNTAX_EXCEPTION_HPP

// SYSTEM INCLUDES
#include <exception>
#include <string>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
// (None)

////////////////////////////////
/// @struct InvalidSyntaxException
///
/// @brief Exception used when invalid
/// syntax is detected
////////////////////////////////
struct InvalidSyntaxException : public std::exception
{
    InvalidSyntaxException(const char* pMsg, const std::string& rLine, const int lineNumber) :
        m_message()
    {
        m_message = std::string(pMsg);
        m_message.append("\n");
        m_message.append(std::to_string(lineNumber));
        m_message.append(": ");
        m_message.append(rLine);
    }

    InvalidSyntaxException(const std::string& rLine, const int lineNumber) :
        m_message()
    {
        InvalidSyntaxException("Invalid syntax", rLine, lineNumber);
    }

    InvalidSyntaxException(const char* pMsg, const std::string& info) :
        m_message()
    {
        m_message = std::string(pMsg);
        m_message.append("\n");
        m_message.append(info);
    }

    InvalidSyntaxException(const char* pMsg) :
        m_message()
    {
        m_message = std::string(pMsg);
        m_message.append("\n");
    }

    const char* what() const throw()
    {
        return m_message.c_str();
    }

private:

    /// Message to print when exception is thrown
    std::string m_message;
};

#endif