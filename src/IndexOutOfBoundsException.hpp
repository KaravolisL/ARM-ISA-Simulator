/////////////////////////////////
/// IndexOutOfBoundsException.hpp
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
/// STRUCT NAME: IndexOutOfBoundsException
///
/// @brief Exception used for list data structures
////////////////////////////////
struct IndexOutOfBoundsException : public std::exception
{
    const char* what() const throw()
    {
        return "Index Out of Bounds Exception";
    }
};

#endif