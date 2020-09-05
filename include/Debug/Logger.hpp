/////////////////////////////////
/// @file Logger.hpp
///
/// @brief Declaration of Logger class
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

// Internal Macros
#define LOG_INTERNAL( logLevel, printGroup, ... ) Logger::GetInstance().Log(__FILENAME__, __PRETTY_FUNCTION__, __LINE__, logLevel, printGroup, _COUNT_VARARGS(__VA_ARGS__), ##__VA_ARGS__)
#define LOG_DEBUG_INTERNAL( printGroup , ... ) LOG_INTERNAL(Logger::LogLevel::DEBUG, printGroup, ##__VA_ARGS__)

// Public Macros
// General prints
#define LOG_DEBUG( ... ) LOG_INTERNAL(Logger::LogLevel::DEBUG, Logger::PrintGroup::PRINT_GROUP_GENERAL, ##__VA_ARGS__)
#define LOG_INFO( ... ) LOG_INTERNAL(Logger::LogLevel::INFO, Logger::PrintGroup::PRINT_GROUP_GENERAL, ##__VA_ARGS__)
#define LOG_ERROR( ... ) LOG_INTERNAL(Logger::LogLevel::ERROR, Logger::PrintGroup::PRINT_GROUP_GENERAL, ##__VA_ARGS__)
#define LOG_USER( ... ) LOG_INTERNAL(Logger::LogLevel::USER, Logger::PrintGroup::PRINT_GROUP_GENERAL, ##__VA_ARGS__)

// Print groups
#define LOG_MEMORY( ... ) LOG_DEBUG_INTERNAL(Logger::PrintGroup::PRINT_GROUP_MEMORY, ##__VA_ARGS__)
#define LOG_INSTRUCTION( ... ) LOG_DEBUG_INTERNAL(Logger::PrintGroup::PRINT_GROUP_INSTRUCTION, ##__VA_ARGS__)

////////////////////////////////
/// @class Logger
///
/// @brief The logger class is used to
/// print debug messages while the program
/// is executing
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
    ///
    /// @note The values of these enums are
    /// used to index the LOG_LEVEL_NAMES array
    ////////////////////////////////
    enum class LogLevel : uint8_t
    {
        INFO = 0,
        DEBUG = 1,
        ERROR = 2,
        USER = 3
    };

    ////////////////////////////////
    /// @enum PrintGroup
    ///
    /// @note The values of these enums are
    /// used to index the PRINT_GROUP_NAMES array
    ////////////////////////////////
    enum class PrintGroup : uint8_t
    {
        PRINT_GROUP_GENERAL = 0,
        PRINT_GROUP_MEMORY = 1,
        PRINT_GROUP_INSTRUCTION = 2,
        PRINT_GROUP_ASSERT = 3
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
    /// @param printGroup   Name of group to which print belongs
    /// @param numArgs      Number of arguments passed in additionally
    /// @param ...          Format string followed by replacement variables
    ////////////////////////////////
    void Log(const char* fileName, const char* funcName, const int lineNumber, const LogLevel logLevel, const PrintGroup printGroup, const int numArgs, ...);

    ////////////////////////////////
    /// METHOD NAME: Log
    ///
    /// @brief This version is used for the
    /// assert macro. It's called after finding
    /// the number of arguments
    ///
    /// @param rMsg         Message to output
    /// @param logLevel     Level at which to print message
    /// @param printGroup   Group to which this print belongs
    ////////////////////////////////
    void Log(const std::string& rMsg, const LogLevel logLevel, const PrintGroup printGroup = PrintGroup::PRINT_GROUP_GENERAL);

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

    /// Names of log levels
    const char* LOG_LEVEL_NAMES[4] =
    {
        "INFO",
        "DEBUG",
        "ERROR",
        "USER"
    };

    /// Names of print groups
    const char* PRINT_GROUP_NAMES[4] =
    {
        "GENERAL",
        "MEMORY",
        "INSTRUCTION",
        "ASSERT"
    };

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