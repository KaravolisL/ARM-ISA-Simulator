/////////////////////////////////
/// @file AssemblingException.hpp
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef LABEL_REDEFINITION_EXCEPTION_HPP
#define LABEL_REDEFINITION_EXCEPTION_HPP

// SYSTEM INCLUDES
#include <exception>
#include <string>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
// (None)

////////////////////////////////
/// @struct AssemblingException
///
/// @brief Exception used prior to program
/// execution
////////////////////////////////
struct AssemblingException : public std::exception
{
    AssemblingException(const char* pMsg, const std::string& rLine, const int lineNumber) :
        m_message()
    {
        m_message = std::string(pMsg);
        m_message.append("\n Line " + std::to_string(lineNumber));
        m_message.append(": ");
        m_message.append(rLine);
    }

    AssemblingException(const char* pMsg) :
        m_message()
    {
        m_message = std::string(pMsg);
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