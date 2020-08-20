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
#include "DebugUtil.hpp" // For util macros

// FORWARD DECLARATIONS
// (None)

// Log Macros
#define LOG_DEBUG( ... ) Logger::GetInstance().Log(__FILENAME__, __PRETTY_FUNCTION__, __LINE__, Logger::LogLevel::DEBUG, _COUNT_VARARGS(__VA_ARGS__), ##__VA_ARGS__)
#define LOG_INFO( ... ) Logger::GetInstance().Log(__FILENAME__, __PRETTY_FUNCTION__, __LINE__, Logger::LogLevel::INFO, _COUNT_VARARGS(__VA_ARGS__), ##__VA_ARGS__)
#define LOG_ERROR( ... ) Logger::GetInstance().Log(__FILENAME__, __PRETTY_FUNCTION__, __LINE__, Logger::LogLevel::ERROR, _COUNT_VARARGS(__VA_ARGS__), ##__VA_ARGS__)
#define LOG_USER( ... ) Logger::GetInstance().Log(__FILENAME__, __PRETTY_FUNCTION__, __LINE__, Logger::LogLevel::USER, _COUNT_VARARGS(__VA_ARGS__), ##__VA_ARGS__)

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
    enum class LogLevel
    {
        INFO,
        DEBUG,
        ERROR,
        USER
    };

    ////////////////////////////////
    /// METHOD NAME: Log
    ///
    /// @brief This version is used for the
    /// log macro. It's called after finding
    /// the number of arguments
    ///
    /// @warning This method is only to be used through the macro
    /// defined above.
    ///
    /// @param fileName     Name of file where assert is placed
    /// @param funcName     Name of the function where the assert is placed
    /// @param lineNumber   Line on which assert is placed
    /// @param logLevel     Level at which to print message
    /// @param numArgs      Number of arguments passed in additionally
    /// @param ...          Format string followed by replacement variables
    ////////////////////////////////
    void Log(const char* fileName, const char* funcName, const int lineNumber, const LogLevel logLevel, const int numArgs, ...);

    ////////////////////////////////
    /// METHOD NAME: Log
    ///
    /// @brief This version is used for the
    /// assert macro. It's called after finding
    /// the number of arguments
    ///
    /// @param rMsg          Message to output
    /// @param logLevel     Level at which to print message
    ////////////////////////////////
    void Log(const std::string& rMsg, const LogLevel logLevel);

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