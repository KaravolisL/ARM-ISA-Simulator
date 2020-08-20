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
#include <iostream>
#include <string>
#include <sstream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "Assert.hpp" // For ASSERT
#include "Logger.hpp" // Header for class

////////////////////////////////
/// METHOD NAME: Log
////////////////////////////////
void Logger::Log(const std::string& rMsg, const Logger::LogLevel logLevel)
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
        case LogLevel::USER:
            m_logStream << "USER: ";
            break;
        default:
            ASSERT(false, "logLevel = %d", logLevel);
    }

    // Print message
    m_logStream << rMsg << "\n";

    // Flush the log
    m_logStream.flush();
}

////////////////////////////////
/// METHOD NAME: Log
////////////////////////////////
void Logger::Log(const char* fileName, const char* funcName, const int lineNumber, const Logger::LogLevel logLevel, const int numArgs, ...)
{
    // Concatenate given strings
    std::stringstream concatStream;
    concatStream << fileName << " : " << funcName << " : Line " << lineNumber << " : ";

    // Initialize valist
    va_list valist;
    va_start(valist, numArgs);

    // Concatenate given strings
    std::string message = format(numArgs, valist);
    concatStream << message;

    // Clean up memory
    va_end(valist);

    // Have to copy it because of how .str() works
    std::string concatString = concatStream.str();
    this->Log(concatString, logLevel);

    // User logs also get printed to std::cout
    if (logLevel == LogLevel::USER)
    {
        std::cout << message;
    }
}