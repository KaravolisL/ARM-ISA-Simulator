/////////////////////////////////
/// @file Logger.cpp
///
/// @brief Declaration for Logger class
///
/// @copydetail Logger
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>
#include <cstdarg>
#include <string>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "Logger.hpp" // Header for class

////////////////////////////////
/// METHOD NAME: Log
////////////////////////////////
void Logger::Log(const char* msg, Logger::LogLevel logLevel)
{
    // Print log level
    switch (logLevel)
    {
        case LogLevel::INFO:
            m_logStream << "INFO: ";
            break;
        case LogLevel::DEBUG:
            m_logStream << "DEBUG: ";
            break;
        case LogLevel::ERROR:
            m_logStream << "ERROR: ";
            break;
        default:
            assert(false);
    }

    // Print message
    m_logStream << msg << "\n";

    // Flush the log
    m_logStream.flush();
}

////////////////////////////////
/// METHOD NAME: Log
////////////////////////////////
void Logger::Log(std::string msg, Logger::LogLevel logLevel)
{
    this->Log(msg.c_str(), logLevel);
}

////////////////////////////////
/// METHOD NAME: Log
////////////////////////////////
void Logger::Log(int numStrings, ...)
{
    // Initialize valist
    va_list valist;
    va_start(valist, numStrings);

    // Concatenate given strings
    std::string concatString = "";
    for (int i = 0; i < numStrings; i++)
    {
        concatString.append(va_arg(valist, char*));
    }

    // Clean up memory
    va_end(valist);

    this->Log(concatString);
}