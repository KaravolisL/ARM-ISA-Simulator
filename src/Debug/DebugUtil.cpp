/////////////////////////////////
/// @file DebugUtil.cpp
///
/// @copybrief DebugUtil.hpp
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <iostream>
#include <sstream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "DebugUtil.hpp" // Header for functions

////////////////////////////////
/// FUNCTION NAME: format
////////////////////////////////
std::string format(int numArgs, va_list valist)
{
    std::stringstream formattedString;
    
    if (numArgs > 0)
    {
        // Print out the message filling in the given parameters
        char* msg = (va_arg(valist, char*));
        while (*msg != '\0')
        {
            if (*msg == '%')
            {
                switch(*(++msg))
                {
                    case 'd':
                    case 'i':
                    case 'c':
                    {
                        int value = va_arg(valist, int);
                        formattedString << value;
                        break;
                    }
                    case 'f':
                    {
                        float value = va_arg(valist, double);
                        formattedString << value;
                        break;
                    }
                    case 's':
                    {
                        char* value = va_arg(valist, char*);
                        formattedString << value;
                        break;
                    }
                    case 'p':
                    {
                        void* value = va_arg(valist, void*);
                        formattedString << value;
                        break;
                    }
                    default:
                        formattedString << "Unknown format";
                }
            }
            else
            {
                formattedString << *msg;
            }
            msg++;
        }
    }

    return formattedString.str();
}