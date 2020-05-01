/////////////////////////////////
/// @file IndexOutOfBoundsException.hpp
///
/// @brief Exception used for list data
/// structures when an index > length - 1
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef INDEX_OUT_OF_BOUNDS_EXCEPTION_HPP
#define INDEX_OUT_OF_BOUNDS_EXCEPTION_HPP

// SYSTEM INCLUDES
#include <exception>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
// (None)

////////////////////////////////
/// @struct IndexOutOfBoundsException
///
/// @brief Exception used for list data structures
////////////////////////////////
struct IndexOutOfBoundsException : public std::exception
{
    IndexOutOfBoundsException(const int index) :
        m_message()
    {
        m_message = "Index ";
        m_message.append(std::to_string(index));
        m_message.append(" out of bounds\n");
    }

    IndexOutOfBoundsException() :
        m_message("Index out of bounds exception\n")
    {}

    const char* what() const throw()
    {
        return m_message.c_str();
    }

private:

    /// Message to be outputted
    std::string m_message;

};

#endif