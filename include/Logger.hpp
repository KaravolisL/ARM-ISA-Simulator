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

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
// (None)

// FORWARD DECLARATIONS
// (None)

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
    void Log(std::string& rMsg, LogLevel logLevel = INFO);

    ////////////////////////////////
    /// METHOD NAME: Log
    ////////////////////////////////
    void Log(std::string msg, LogLevel logLevel = INFO);

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