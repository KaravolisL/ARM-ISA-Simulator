/////////////////////////////////
/// @file LabelRedefinitionException.hpp
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
/// @struct LabelRedefinitionException
///
/// @brief Exception used when a label has
/// already been defined in a program
////////////////////////////////
struct LabelRedefinitionException : public std::exception
{
    LabelRedefinitionException(std::string& rLine, int lineNumber) :
        m_message()
    {
        m_message = std::string("Label already defined\nLine ");
        m_message.append(std::to_string(lineNumber));
        m_message.append(": ");
        m_message.append(rLine);
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