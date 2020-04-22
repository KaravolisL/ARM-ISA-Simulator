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