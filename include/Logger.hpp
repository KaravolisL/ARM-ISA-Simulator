/////////////////////////////////
/// @file Logger.hpp
///
/// @brief Declaration of Logger class
///
/// @details The logger class is used to
/// print debug messages while the program
/// is executing
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef LOGGER_HPP
#define LOGGER_HPP

// SYSTEM INCLUDES
#include <fstream>
#include <string>
#include <string.h>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
// (None)

// FORWARD DECLARATIONS
// (None)

// Utility Macros
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define S1(x) #x
#define S2(x) S1(x)
#define LOCATION std::string(__FILENAME__) + " : Line " + S2(__LINE__)
#define LOG_MESSAGE( msg ) std::string(LOCATION) + " : " + msg

// Log Macros
#define LOG_DEBUG( msg ) Logger::GetInstance().Log((LOG_MESSAGE(msg)), Logger::LogLevel::DEBUG)
#define LOG_INFO( msg ) Logger::GetInstance().Log((LOG_MESSAGE(msg)), Logger::LogLevel::INFO)
#define LOG_ERROR( msg ) Logger::GetInstance().Log((LOG_MESSAGE(msg)), Logger::LogLevel::ERROR)

////////////////////////////////
/// @class Logger
////////////////////////////////
class Logger
{
public:

    ////////////////////////////////
    /// METHOD NAME: GetInstance
    ////////////////////////////////
    static Logger& GetInstance()
    {
        /// Singleton instance
        static Logger* instance = new Logger();
        return *instance;
    }

    ////////////////////////////////
    /// @enum LogLevel
    ////////////////////////////////
    enum LogLevel
    {
        INFO,
        DEBUG,
        ERROR
    };

    ////////////////////////////////
    /// METHOD NAME: Log
    ///
    /// @param msg      Message to log
    /// @param logLevel Level at which to print in log
    ////////////////////////////////
    void Log(const char* msg, LogLevel logLevel = INFO);

    ////////////////////////////////
    /// METHOD NAME: Log
    ////////////////////////////////
    void Log(std::string msg, LogLevel logLevel = INFO);

    ////////////////////////////////
    /// METHOD NAME: Log
    ////////////////////////////////
    void Log(int numStrings, ...);

    ////////////////////////////////
    /// METHOD NAME: Close
    ////////////////////////////////
    void Close() { m_logStream.close(); }

protected:

private:

    /// File name to output
    const char* LOG_FILENAME = "Debug.log";

    /// Output file stream
    std::ofstream m_logStream;

    ////////////////////////////////
    /// Constructer
    ///
    /// @note Private to ensure singleton
    ////////////////////////////////
    Logger() :
        m_logStream(std::ofstream(LOG_FILENAME, std::ofstream::out))
    {}

    ////////////////////////////////
    /// Copy Constructer
    ////////////////////////////////
    Logger(Logger const&);

    ////////////////////////////////
    /// Assignment operator
    ////////////////////////////////
    Logger& operator=(Logger const&);

};

#endif