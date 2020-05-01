/////////////////////////////////
/// @file NoMainException.hpp
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef NO_MAIN_EXCEPTION_HPP
#define NO_MAIN_EXCEPTION_HPP

// SYSTEM INCLUDES
#include <exception>
#include <string>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
// (None)

////////////////////////////////
/// @struct NoMainException
///
/// @brief Exception used when a program
/// is missing a __main label
////////////////////////////////
struct NoMainException : public std::exception
{
    NoMainException() :
        m_message(std::string("No __main label"))
    {}

    const char* what() const throw()
    {
        return m_message.c_str();
    }

private:

    /// Message to print when exception is thrown
    std::string m_message;
};

#endif