/////////////////////////////////
/// @file Assert.cpp
///
/// @brief Implementation of Assert functions
///
/// @copydetail Assert.hpp
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>
#include <cstdarg>
#include <iostream>
#include <sstream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "Assert.hpp" // Header for functions
#include "Logger.hpp" // For Logger class

////////////////////////////////
/// FUNCTION NAME: Assert
////////////////////////////////
void Assert(bool expr, const char* fileName, int lineNumber, int numArgs, ...)
{
    if (expr) return;

    // Initialize valist
    va_list valist;
    va_start(valist, numArgs);

    // Concatenate given strings
    std::stringstream concatString;
    concatString << fileName << " : Line " << lineNumber << " : ";
    
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
                        concatString << value;
                        break;
                    }
                    case 'f':
                    {
                        float value = va_arg(valist, double);
                        concatString << value;
                        break;
                    }
                    case 's':
                    {
                        char* value = va_arg(valist, char*);
                        concatString << value;
                        break;
                    }
                    case 'p':
                    {
                        void* value = va_arg(valist, void*);
                        concatString << value;
                        break;
                    }
                    default:
                        concatString << "Unknown format";
                }
            }
            else
            {
                concatString << *msg;
            }
            msg++;
        }

        // Clean up memory
        va_end(valist);
    }

    Logger::GetInstance().Log(concatString.str(), Logger::LogLevel::ERROR);

    std::cout << "Assertion failed: " << concatString.str() << '\n';
    std::cout << "See Debug.log for more details\n";

    assert(expr);
}